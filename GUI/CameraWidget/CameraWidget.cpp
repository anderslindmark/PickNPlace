/****************************************************************************
**
** Copyright (C) 2005-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.0, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** In addition, as a special exception, Trolltech, as the sole copyright
** holder for Qt Designer, grants users of the Qt/Eclipse Integration
** plug-in the right for the Qt/Eclipse Integration to link to
** functionality provided by Qt Designer and its related libraries.
**
** Trolltech reserves all rights not expressly granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include <QtGui>
#include "CameraWidget.h"

#ifdef USE_OPENGL_WIDGET
CameraWidget::CameraWidget(QWidget *parent) : QGLWidget(QGLFormat(QGL::DirectRendering), parent)
{
	if(!format().directRendering())
	{
		qWarning("Direct rendering not supported");
	}
}
#else
CameraWidget::CameraWidget(QWidget *parent) : QWidget(parent)
{
}
#endif // USE_OPENGL_WIDGET

void CameraWidget::cameraNewImage(camera::Camera *camera)
{
	correctDistortion(camera->getLastImage());
	
	this->m_image = QImage(correctedImage->getBufferAddress(), correctedImage->getWidth(), correctedImage->getHeight(), QImage::Format_RGB32);
	update();
}

void CameraWidget::cameraError(camera::Camera *camera, int errorCode, const std::string &errorMessage)
{
	//std::cout << "Error! (#" << errorCode << ": " << errorMessage << ")" << std::endl;
}

void CameraWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawImage(0, 0, m_image);
}

void CameraWidget::resizeEvent (QResizeEvent * event)
{
	int width = event->size()->getWidth();
	int height = event->size()->getHeight();
	
	// TODO: Check if reallocateing the image takes to much time
	// Create a new Image to store the corrected image data
	if(correctedImage != NULL)
	{
		delete correctedImage;
	}
	correctedImage = new camera::Image(width, height, camera::Image::FORMAT_RGB32);
	
	// Realocate the mapping array
	if(pixelMapping != NULL)
	{
		delete pixelMapping;
	}
	pixelMapping = new int[width * height];
	int *mapping = pixelMapping;
	int dx, dy;
	
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			dx = correctionVectorA[0]*x*x*y +
				correctionVectorA[1]*x*y*y +
				correctionVectorA[2]*x*x +
				correctionVectorA[3]*y*y +
				correctionVectorA[4]*x*y +
				correctionVectorA[5]*x +
				correctionVectorA[6]*y +
				correctionVectorA[7];
			
			dy = correctionVectorB[0]*x*x*y +
				correctionVectorB[1]*x*y*y +
				correctionVectorB[2]*x*x +
				correctionVectorB[3]*y*y +
				correctionVectorB[4]*x*y +
				correctionVectorB[5]*x +
				correctionVectorB[6]*y +
				correctionVectorB[7];
			
			*mapping = dy * width + dx;
			mapping++;
		}
	}
}

void CameraWidget::correctDistortion(camera::Image *image)
{
	camera::ImageBuffer *correctedImageAddr = correctedImage->getBufferAddress();
	camera::ImageBuffer *distortedImageBaseAddr = image->getBufferAddress();
	camera::ImageBuffer *distortedImageAddr = NULL;
	int *mapping = pixelMapping;
	
	for(int y = 0; y < correctedImage->getHeight(); y++)
	{
		for(int x = 0; x < correctedImage->getWidth(); x++)
		{
			// Calculate which pixel to use from the distorted image based on the pixel mapping calculated in resizeEvent
			distortedImageAddr = distortedImageBaseAddr + (*mapping) * 4;
			mapping++;
			
			// Copy the RGBX values from the distordet image to the corrected
			*correctedImageAddr = *distortedImageAddr; // R
			
			correctedImageAddr++;
			distortedImageAddr++;
			*correctedImageAddr = *distortedImageAddr; // G
			
			correctedImageAddr++;
			distortedImageAddr++;
			*correctedImageAddr = *distortedImageAddr; // B
			
			correctedImageAddr++;
			distortedImageAddr++;
			*correctedImageAddr = *distortedImageAddr; // X
		}
	}
}