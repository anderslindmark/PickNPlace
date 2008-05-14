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
#else
CameraWidget::CameraWidget(QWidget *parent) : QWidget(parent)
{
#endif // USE_OPENGL_WIDGET
	
	m_camera = NULL;
	m_barrelCorrection = NULL;
}

CameraWidget::~CameraWidget()
{
	if(m_camera != NULL)
	{
		delete m_camera;
	}

	if(m_barrelCorrection != NULL)
	{
		delete m_barrelCorrection;
	}
}

///
/// \brief Event handler for when a new image arrives from the camera. 
/// \param camera Pointer to the camera that produced the new image.
///
void CameraWidget::cameraNewImage(camera::Camera *camera, camera::Image *image)
{
	m_image = QImage(camera->getLastImage()->getBufferAddress(), camera->getLastImage()->getWidth(), camera->getLastImage()->getHeight(), QImage::Format_RGB32);
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

///
/// \brief The camera widget was resized. Since the size of the camera image changes, we need to recalculate the correction vectors
///        used to correct the camera image here.
///
void CameraWidget::resizeEvent(QResizeEvent * event)
{
	//barrelCorrection.setOutputSize(event->size().width(), event->size().height());
}

void CameraWidget::setCamera() //const camera::CameraIdentifier &cameraid)
{
	/*
	if(m_camera != NULL)
	{
		delete m_camera;
		m_camera = NULL;
	}
	
	camera::CameraManager *cameraManager = camera::CameraManager::getInstance();
	m_camera = cameraManager->createCamera(cameraid);
	m_camera->setListener(this);
	*/
}

void CameraWidget::setImageCorrectionParameters(unsigned int distortedX[8], unsigned int distortedY[8])
{
	if(m_barrelCorrection != NULL) {
		m_barrelCorrection->setDistortedCoordinates(distortedX, distortedY);
	}
	else
	{
		m_barrelCorrection = new camera::BarrelCorrection(distortedX, distortedY);
		m_camera->addFilter(m_barrelCorrection);
	}
}

void CameraWidget::setCoordinateMapping(int leftOffset, float leftZDiff, 
						  int rightOffset, float rightZDiff, 					  
						  int topOffset, float topZDiff, 
						  int bottomOffset, float bottomZDiff)
{
	m_leftOffset = leftOffset;
	m_leftZDiff = leftZDiff;
	m_rightOffset = rightOffset;
	m_rightZDiff = rightZDiff;
	m_topOffset = topOffset;
	m_topZDiff = topZDiff;
	m_bottomOffset = bottomOffset;
	m_bottomZDiff = bottomZDiff;
}

void CameraWidget::setMachineCoordinates(int x, int y, int z)
{
	m_machineX = x;
	m_machineY = y;
	m_machineZ = z;
}

void CameraWidget::getVisibleRegion(int &left, int &right, int &top, int &bottom)
{
	left = m_machineX + m_leftOffset + (m_machineZ * m_leftZDiff);
	right = m_machineX + m_rightOffset + (m_machineZ * m_rightZDiff);
	top = m_machineY + m_topOffset + (m_machineZ * m_topZDiff);
	bottom = m_machineY + m_bottomOffset + (m_machineZ * m_bottomZDiff);
}

void CameraWidget::start()
{
	if(m_camera != NULL)
	{
		m_camera->start();
	}
}

void CameraWidget::stop()
{
	if(m_camera != NULL)
	{
		m_camera->stop();
	}
}

void CameraWidget::setDrawCommands(bool enabled)
{
}

void CameraWidget::setDrawHeadPosition(bool enabled)
{
}

void CameraWidget::setDrawEdges(bool enabled)
{
}

camera::Image *CameraWidget::getImage()
{
	if(m_camera != NULL)
	{
		return m_camera->getLastImage();
	}
	
	return NULL;
}

QImage *CameraWidget::getQImage()
{
	return &m_image;
}

