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
#define ABS(x) (x < 0 ? -x : x)

#ifdef USE_OPENGL_WIDGET
CameraWidget::CameraWidget(QWidget *parent) : QGLWidget(QGLFormat(QGL::DirectRendering), parent)
{
	if(!format().directRendering())
	{
		qWarning("Direct rendering not supported");
	}
	
	correctedImage = NULL;
	pixelMapping = NULL;
}
#else
CameraWidget::CameraWidget(QWidget *parent) : QWidget(parent)
{
	m_correctedImage = NULL;
	m_pixelMapping = NULL;
	
	m_yd[0] = 60;
	m_yd[1] = 30;
	m_yd[2] = 17;
	m_yd[3] = 288;
	m_yd[4] = 288;
	m_yd[5] = 513;
	m_yd[6] = 542;
	m_yd[7] = 550;
	
	m_xd[0] = 31;
	m_xd[1] = 350;
	m_xd[2] = 732;
	m_xd[3] = 30;
	m_xd[4] = 741;
	m_xd[5] = 37;
	m_xd[6] = 355;
	m_xd[7] = 731;
}
#endif // USE_OPENGL_WIDGET

void CameraWidget::cameraNewImage(camera::Camera *camera)
{
	// Check that the format is RGB32. It's the only supported format at the moment
	if(camera->getLastImage()->getFormat() != camera::Image::FORMAT_RGB32)
	{
		qWarning("Image from camera is not RGB32");
		return;
	}
	
	// TODO: Can the camera image change size?
	if(m_correctedImage == NULL)
	{
		m_correctedImage = new camera::Image(camera->getLastImage()->getWidth(), camera->getLastImage()->getHeight(), camera::Image::FORMAT_RGB32);
	}
	
	correctDistortion(camera->getLastImage());
	m_image = QImage(m_correctedImage->getBufferAddress(), m_correctedImage->getWidth(), m_correctedImage->getHeight(), QImage::Format_RGB32);
	update();
}

void CameraWidget::cameraError(camera::Camera *camera, int errorCode, const std::string &errorMessage)
{
	qWarning("cameraError: #%d: %s", errorCode, errorMessage);
}

void CameraWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawImage(0, 0, m_image);
}

void CameraWidget::resizeEvent(QResizeEvent * event)
{
	if(event->size() == event->oldSize())
		return;
	int width = 768; //event->size().width();
	int height = 576; //event->size().height();
	qDebug("resizeEvent: From %d, %d to %d, %d", event->oldSize().width(), event->oldSize().height(), event->size().width(), event->size().height());
	
	// Calculate the correction vectors
	//float xc[8] = {0, width / 2, width - 1, 0, width - 1, 0, width / 2, width - 1};
	//float yc[8] = {0, 0, 0, height / 2, height / 2, height - 1, height - 1, height - 1};
	float xc[8] = {1, width / 2, width, 1, width, 1, width / 2, width};
	float yc[8] = {1, 1, 1, height / 2, height / 2, height, height, height};
	float M[8][9];
	float correctionVectorA[8];
	float correctionVectorB[8];
	
	for(int r = 0; r < 8; r++)
	{
		M[r][0] = yc[r]*yc[r]*xc[r];
		M[r][1] = yc[r]*xc[r]*xc[r];
		M[r][2] = yc[r]*yc[r];
		M[r][3] = xc[r]*xc[r];
		M[r][4] = yc[r]*xc[r];
		M[r][5] = yc[r];
		M[r][6] = xc[r];
		M[r][7] = 1;
		M[r][8] = m_yd[r];
	}
	
	solveLinearEquation(M);
	
	qDebug("resizeEvent: correctionVectorA = ");
	for(int r = 0; r < 8; r++)
	{
		correctionVectorA[r] = M[r][8];
		qDebug("%f", correctionVectorA[r]);
	}
	
for(int r = 0; r < 8; r++)
	{
		M[r][0] = yc[r]*yc[r]*xc[r];
		M[r][1] = yc[r]*xc[r]*xc[r];
		M[r][2] = yc[r]*yc[r];
		M[r][3] = xc[r]*xc[r];
		M[r][4] = yc[r]*xc[r];
		M[r][5] = yc[r];
		M[r][6] = xc[r];
		M[r][7] = 1;
		M[r][8] = m_xd[r];
	}
	
	solveLinearEquation(M);
	
	qDebug("resizeEvent: correctionVectorB = ");
	for(int r = 0; r < 8; r++)
	{
		correctionVectorB[r] = M[r][8];
		qDebug("%f", correctionVectorB[r]);
	}
	
	// TODO: Check if reallocateing the image takes to much time
	// TODO: resizeEvent and cameraNewImage runs in separate threads, so the resize of correctedImage can not be done while a new image is being painted
	// Create a new Image to store the corrected image data
	if(m_correctedImage != NULL)
	{
		delete m_correctedImage;
	}
	m_correctedImage = new camera::Image(width, height, camera::Image::FORMAT_RGB32);

	// TODO: Check if reallocateing the pixel map takes to much time
	// Reallocate the mapping array
	if(m_pixelMapping != NULL)
	{
		delete m_pixelMapping;
	}
	m_pixelMapping = new int[width * height];
	int *mapping = m_pixelMapping;
	int dx, dy;
	
	// Calculate the values for the new mapping array
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			dy = correctionVectorA[0]*x*y*y +
				correctionVectorA[1]*x*x*y +
				correctionVectorA[2]*y*y +
				correctionVectorA[3]*x*x +
				correctionVectorA[4]*x*y +
				correctionVectorA[5]*y +
				correctionVectorA[6]*x +
				correctionVectorA[7];
			
			dx = correctionVectorB[0]*x*y*y +
				correctionVectorB[1]*x*x*y +
				correctionVectorB[2]*y*y +
				correctionVectorB[3]*x*x +
				correctionVectorB[4]*x*y +
				correctionVectorB[5]*y +
				correctionVectorB[6]*x +
				correctionVectorB[7];
			
			*mapping = dy * width + dx;
			mapping++;
		}
	}
	qDebug("resizeEvent: Done");
}

void CameraWidget::solveLinearEquation(float M[8][9])
{
	int rowCount = 8;
	int columnCount = 9;
	int r, c, r2, c2;
	float tmp;
	
	qDebug("solveLinearEquation: Before Gaussian: M = ");
	for(r = 0; r < 8; r++)
	{
		qDebug(" %15.3f %15.3f %15.3f %15.3f %15.3f %15.3f %15.3f %15.3f %15.3f", M[r][0], M[r][1], M[r][2], M[r][3], M[r][4], M[r][5], M[r][6], M[r][7], M[r][8]);
	}
	
	r = 0;
	c = 0;
	while(r < rowCount && c < columnCount)
	{
		int maxR = r;
		for(r2 = r + 1; r2 < rowCount; r2++)
		{
			if(ABS(M[r2][c]) > ABS(M[maxR][c]))
			{
				maxR = r2;
			}
		}
		
		if(M[maxR][c] != 0)
		{
			// Swap row r and maxR
			for(c2 = 0; c2 < columnCount; c2++)
			{
				tmp = M[r][c2];
				M[r][c2] = M[maxR][c2];
				M[maxR][c2] = tmp;
			}
			
			// Devide row r with the value in M[r][c]
			tmp = M[r][c];
			for(c2 = 0; c2 < columnCount; c2++)
			{
				M[r][c2] /= tmp;
			}
			
			// Subtract A[r2][c] * row r from row r2
			for(r2 = r + 1; r2 < rowCount; r2++)
			{
				tmp = M[r2][c];
				for(c2 = 0; c2 < columnCount; c2++)
				{
					M[r2][c2] -= M[r][c2] * tmp;
				}
			}
			// Next row
			r++;
		}
		
		// Next column
		c++;
	}
	
	qDebug("solveLinearEquation: After Gaussian: M = ");
	for(r = 0; r < 8; r++)
	{
		qDebug(" %15.3f %15.3f %15.3f %15.3f %15.3f %15.3f %15.3f %15.3f %15.3f", M[r][0], M[r][1], M[r][2], M[r][3], M[r][4], M[r][5], M[r][6], M[r][7], M[r][8]);
	}

	// Do back-substitution
	for(r = rowCount - 1; r >= 0; r--)
	{
		for(r2 = 0; r2 < r; r2++)
		{
			tmp = M[r2][r];
			for(c = r; c < columnCount; c++)
			{
				M[r2][c] -= M[r][c] * tmp;
			}
		}
	}

	qDebug("solveLinearEquation: After back-substitution: M = ");
	for(r = 0; r < 8; r++)
	{
		qDebug(" %15.3f %15.3f %15.3f %15.3f %15.3f %15.3f %15.3f %15.3f %15.3f", M[r][0], M[r][1], M[r][2], M[r][3], M[r][4], M[r][5], M[r][6], M[r][7], M[r][8]);
	}

}

void CameraWidget::correctDistortion(camera::Image *distortedImage)
{
	if(m_pixelMapping == NULL)
	{
		qWarning("pixelMapping == NULL");
		return;
	}
	
	camera::ImageBuffer *cBufferAddr = m_correctedImage->getBufferAddress();
	camera::ImageBuffer *dBufferBaseAddr = distortedImage->getBufferAddress();
	camera::ImageBuffer *dBufferAddr = NULL;
	int dBufferSize = distortedImage->getBufferSize();
	int *mapping = m_pixelMapping;
	int s = m_correctedImage->getWidth() * m_correctedImage->getHeight();
	int offset;
	dBufferAddr = dBufferBaseAddr;

	for(int i = 0; i < s; i++) {
		offset = (*mapping) * 4;
		mapping++;
		// Calculate which pixel to use from the distorted image based on the pixel mapping calculated in resizeEvent
		if(offset < 0 || offset > dBufferSize)
		{
			*(cBufferAddr++) = 255; // B
			*(cBufferAddr++) = 0; // G
			*(cBufferAddr++) = 255; // R
			*(cBufferAddr++) = 0; // X
		} else {
			dBufferAddr = dBufferBaseAddr + offset;
			
			// Copy the RGBX values from the distordet to the corrected image
			*(cBufferAddr++) = *(dBufferAddr++); // R
			*(cBufferAddr++) = *(dBufferAddr++); // G
			*(cBufferAddr++) = *(dBufferAddr++); // B
			*(cBufferAddr++) = *(dBufferAddr++); // X
		}
	}
}