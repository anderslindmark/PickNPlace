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

CameraWidget::CameraWidget(QWidget *parent) : QWidget(parent)
{
	//this->m_painter.begin(this);
}

void CameraWidget::cameraNewImage(camera::Camera *camera)
{
	camera::Image *newImage = camera->getLastImage();
	this->m_image = QImage(newImage->getBufferAddress(), newImage->getWidth(), newImage->getHeight(), QImage::Format_RGB32);
	update();
}

void CameraWidget::cameraError(camera::Camera *camera, int errorCode, const std::string &errorMessage)
{
	//std::cout << "Error! (#" << errorCode << ": " << errorMessage << ")" << std::endl;
}

void CameraWidget::paintEvent(QPaintEvent *event)
{
	
	QRect updateRect = event->rect();
	this->m_painter.begin(this);
	this->m_painter.drawImage(updateRect, this->m_image, updateRect);
	this->m_painter.end();
}