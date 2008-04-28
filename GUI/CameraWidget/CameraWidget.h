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

#ifndef __CAMERAWIDGET_H__
#define __CAMERAWIDGET_H__

#include <QWidget>
#include <QtDesigner/QDesignerExportWidget>
#include <QtGui/QPainter>
#include <QtGui/QImage>
#include "CameraManager.h"
#include "Camera.h"
#include "CameraListener.h"
#include "CameraException.h"
#include "Image.h"
#include "BarrelCorrection.h"

#ifdef USE_OPENGL_WIDGET
class QDESIGNER_WIDGET_EXPORT CameraWidget : public QGLWidget, public camera::CameraListener
#else
class QDESIGNER_WIDGET_EXPORT CameraWidget : public QWidget, public camera::CameraListener
#endif // USE_OPENGL_WIDGET
{
    Q_OBJECT
	//Q_PROPERTY(Priority priority READ priority WRITE setPriority)

public:
    CameraWidget(QWidget *parent = 0);
    ~CameraWidget();
	
	void cameraNewImage(camera::Camera *camera);
	void cameraError(camera::Camera *camera, int errorCode, const std::string &errorMessage);

	void setCamera(const camera::CameraIdentifier &cameraid);
	void setImageCorrectionParameters(float distortedX[8], float distortedY[8]);
	void setCoordinateMapping(int leftOffset, float leftZDiff, 
							  int rightOffset, float rightZDiff, 					  
							  int topOffset, float topZDiff, 
							  int bottomOffset, float bottomZDiff);
	void setMachineCoordinates(int x, int y, int z);
	void getVisibleRegion(int &left, int &right, int &top, int &bottom);
	void start();
	void stop();
	void setDrawCommands(bool enabled);
	void setDrawHeadPosition(bool enabled);
	void setDrawEdges(bool enabled);
	camera::Image *getImage();
	QImage *getQImage();

protected:
    void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent * event);
    
private:
	camera::Camera *m_camera;
	camera::BarrelCorrection barrelCorrection;
	QImage m_image;
	
	int m_machineX;
	int m_machineY;
	int m_machineZ;
	
	int m_leftOffset;
	float m_leftZDiff;
	int m_rightOffset;
	float m_rightZDiff; 					  
	int m_topOffset;
	float m_topZDiff;
	int m_bottomOffset;
	float m_bottomZDiff;
};

#endif // __CAMERAWIDGET_H__
