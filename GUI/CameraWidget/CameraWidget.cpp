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
	correctedImage = NULL;
	pixelMapping = NULL;
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
	
	if(correctedImage == NULL)
	{
		correctedImage = new camera::Image(camera->getLastImage()->getWidth(), camera->getLastImage()->getHeight(), camera::Image::FORMAT_RGB32);
	}

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

void CameraWidget::resizeEvent(QResizeEvent * event)
{
	int width = 768; //event->size().width();
	int height = 576; //event->size().height();
	qDebug("resizeEvent: width = %d, height = %d", width, height);

	yd[0] = 60;
	yd[1] = 30;
	yd[2] = 17;
	yd[3] = 288;
	yd[4] = 288;
	yd[5] = 513;
	yd[6] = 542;
	yd[7] = 550;
	
	xd[0] = 31;
	xd[1] = 350;
	xd[2] = 732;
	xd[3] = 30;
	xd[4] = 741;
	xd[5] = 37;
	xd[6] = 355;
	xd[7] = 731;
	
	// Calculate the correction vectors
	//float xc[8] = {0, width / 2, width - 1, 0, width - 1, 0, width / 2, width - 1};
	//float yc[8] = {0, 0, 0, height / 2, height / 2, height - 1, height - 1, height - 1};
	float xc[8] = {1, width / 2, width, 1, width, 1, width / 2, width};
	float yc[8] = {1, 1, 1, height / 2, height / 2, height, height, height};
	float A[9][8];
	for(int y = 0; y < 8; y++)
	{
		A[0][y] = yc[y]*yc[y]*xc[y];
		A[1][y] = yc[y]*xc[y]*xc[y];
		A[2][y] = yc[y]*yc[y];
		A[3][y] = xc[y]*xc[y];
		A[4][y] = yc[y]*xc[y];
		A[5][y] = yc[y];
		A[6][y] = xc[y];
		A[7][y] = 1;
		A[8][y] = xd[y];
	}
	gaussJordan(A);
	qDebug("resizeEvent: correctionVectorA = ");
	for(int y = 0; y < 8; y++)
	{
		correctionVectorA[y] = A[8][y];
		qDebug("%f", correctionVectorA[y]);
	}
	

	for(int y = 0; y < 8; y++)
	{
		A[0][y] = yc[y]*yc[y]*xc[y];
		A[1][y] = yc[y]*xc[y]*xc[y];
		A[2][y] = yc[y]*yc[y];
		A[3][y] = xc[y]*xc[y];
		A[4][y] = yc[y]*xc[y];
		A[5][y] = yc[y];
		A[6][y] = xc[y];
		A[7][y] = 1;
		A[8][y] = yd[y];
	}
	gaussJordan(A);
	qDebug("resizeEvent: correctionVectorA = ");
	for(int y = 0; y < 8; y++)
	{
		correctionVectorB[y] = A[8][y];
		qDebug("%f", correctionVectorA[y]);
	}
	
	// TODO: Check if reallocateing the image takes to much time
	// TODO: resizeEvent and cameraNewImage runs in separate threads, so the resize of correctedImage can not be done while painting it
	// Create a new Image to store the corrected image data
	if(correctedImage != NULL)
	{
		delete correctedImage;
	}
	correctedImage = new camera::Image(width, height, camera::Image::FORMAT_RGB32);

	// TODO: Check if reallocateing the pixel map takes to much time
	// Realocate the mapping array
	if(pixelMapping != NULL)
	{
		delete pixelMapping;
	}
	pixelMapping = new int[width * height];
	int *mapping = pixelMapping;
	int dx, dy;
	//
	//// Calculate the values for the new mapping array
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			//dx = correctionVectorA[0]*x*x*y +
			//	correctionVectorA[1]*x*y*y +
			//	correctionVectorA[2]*x*x +
			//	correctionVectorA[3]*y*y +
			//	correctionVectorA[4]*x*y +
			//	correctionVectorA[5]*x +
			//	correctionVectorA[6]*y +
			//	correctionVectorA[7];
			//
			//dy = correctionVectorB[0]*x*x*y +
			//	correctionVectorB[1]*x*y*y +
			//	correctionVectorB[2]*x*x +
			//	correctionVectorB[3]*y*y +
			//	correctionVectorB[4]*x*y +
			//	correctionVectorB[5]*x +
			//	correctionVectorB[6]*y +
			//	correctionVectorB[7];
			dx = x;
			dy = y;
			*mapping = dy * width + dx;
			mapping++;
		}
	}
	qDebug("resizeEvent: Done");
}

void CameraWidget::gaussJordan(float A[9][8])
{
	qDebug("gaussJordan: A = ");
	for(int y = 0; y < 8; y++)
	{
		qDebug("    %10.2f    %10.2f    %10.2f    %10.2f    %10.2f    %10.2f    %10.2f    %10.2f    %10.2f", A[0][y], A[1][y], A[2][y], A[3][y], A[4][y], A[5][y], A[6][y], A[7][y], A[8][y]);
	}

	int lead = 0;
	int rowCount = 8;
	int columnCount = 9;
	for(int r = 0; r < rowCount; r++)
	{
		if(columnCount <= lead)
		{
			return;
		}
		
		int i = r;
		while(A[lead][i] == 0.0)
		{
			i++;
			if(rowCount == i)
			{
				i = r;
				lead++;
				if(columnCount == lead)
				{
					return;
				}
			}
		}
		
		// Swap row i and r
		float tmp;
		for(int c = 0; c < columnCount; c++)
		{
			tmp = A[c][i];
			A[c][i] = A[c][r];
			A[c][r] = tmp;
		}
			
		// Divide row r by A[lead][r]
		tmp = A[lead][r];
		for(int c = 0; c < columnCount; c++)
		{
			A[c][r] /= tmp;
		}
		
		// FOR all rows i, from 0 to number of rows, every row except r
		for(i = 0; i < rowCount; i++)
		{
			if(i == r)
			{
				continue;
			}
			
			// Subtract A[lead][i] multiplied by row r from row i
			for(int c = 0; c < columnCount; c++)
			{
				A[c][i] -= A[lead][i] * A[c][r];
			}
		}
		lead++;
	}
	
//ToReducedRowEchelonForm(Matrix M)
//  Let lead = 0
//  Let rowCount be the number of rows in M
//  Let columnCount be the number of columns in M
//  FOR r = 0 to rowCount - 1
//    IF columnCount <= lead
//      STOP
//    END IF
//    Let i = r
//    WHILE M[i, lead] = 0
//      Increment i
//      IF rowCount = i
//        Let i = r
//        Increment lead
//        IF columnCount = lead
//          STOP
//        END IF
//      END IF
//    END WHILE
//    Swap rows i and r
//    Divide row r by M[r, lead]
//    FOR all rows i, from 0 to number of rows, every row except r
//      Subtract M[i, lead] multiplied by row r from row i
//    END FOR
//    Increment lead
//  END FOR
//END ToReducedRowEchelonForm

	qDebug("gaussJordan: After, A = ");
	for(int y = 0; y < 8; y++)
	{
		qDebug("    %10.2f    %10.2f    %10.2f    %10.2f    %10.2f    %10.2f    %10.2f    %10.2f    %10.2f", A[0][y], A[1][y], A[2][y], A[3][y], A[4][y], A[5][y], A[6][y], A[7][y], A[8][y]);
	}

}

void CameraWidget::correctDistortion(camera::Image *distortedImage)
{
	if(pixelMapping == NULL)
	{
		qWarning("pixelMapping == NULL");
		return;
	}
	
	camera::ImageBuffer *cBufferAddr = correctedImage->getBufferAddress();
	camera::ImageBuffer *dBufferBaseAddr = distortedImage->getBufferAddress();
	camera::ImageBuffer *dBufferAddr = NULL;
	int dBufferSize = distortedImage->getBufferSize();
	int *mapping = pixelMapping;
	int s = correctedImage->getWidth() * correctedImage->getHeight();
	
	dBufferAddr = dBufferBaseAddr;

	for(int i = 0; i < s; i++) {
		// Calculate which pixel to use from the distorted image based on the pixel mapping calculated in resizeEvent
		//if(*mapping < 0 || *mapping > dBufferSize)
		//{
			//*(cBufferAddr++) = 0; // B
			//*(cBufferAddr++) = 0; // G
			//*(cBufferAddr++) = 0; // R
			//*(cBufferAddr++) = 0; // X
		//} else {
			//dBufferAddr = dBufferBaseAddr + i * 4; //(*mapping) * 4;
			//mapping++;
			
			// Copy the RGBX values from the distordet to the corrected image
			*(cBufferAddr++) = *(dBufferAddr++); // R
			*(cBufferAddr++) = *(dBufferAddr++); // G
			*(cBufferAddr++) = *(dBufferAddr++); // B
			*(cBufferAddr++) = *(dBufferAddr++); // X
		//}
	}
}