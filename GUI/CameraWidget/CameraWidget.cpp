
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
/// \param image Pointer to the new image. Same as doing camera->getLastImage()
///
void CameraWidget::cameraNewImage(camera::Camera *camera, camera::Image *image)
{
	m_image = QImage(image->getBufferAddress(), image->getWidth(), image->getHeight(), QImage::Format_RGB32);
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
	
	// TODO: Draw the commands in the command queue
	
}

///
/// \brief The camera widget was resized. Since the size of the camera image changes, we need to recalculate the correction vectors
///        used to correct the camera image here.
///
void CameraWidget::resizeEvent(QResizeEvent * event)
{
	//barrelCorrection->setOutputSize(event->size().width(), event->size().height());
}

///
/// \brief The mouse was pressed inside the camera widget.
///
void CameraWidget::mousePressEvent(QMouseEvent * event)
{
}

///
/// \brief Sets which camera source to use when displaying a picture in the camera widget.
/// TODO: Document the parameters properly here.
///
void CameraWidget::setCamera(const std::string &driverIdentifier, const std::string &cameraIdentifier)
{
	if(m_camera != NULL)
	{
		delete m_camera;
		m_camera = NULL;
	}
	
	camera::CameraManager *cameraManager = camera::CameraManager::getInstance();
	m_camera = cameraManager->createCamera(driverIdentifier, cameraIdentifier);
	m_camera->setListener(this);
}

///
/// \brief Sets the image correction parameters used to get rid of the barrel distortion.
/// TODO: Explain more how to obtain these coordinates.
///
void CameraWidget::setImageCorrectionParameters(unsigned int distortedX[8], unsigned int distortedY[8])
{
	if(m_barrelCorrection != NULL)
	{
		m_barrelCorrection->setDistortedCoordinates(distortedX, distortedY);
	}
	else
	{
		m_barrelCorrection = new camera::BarrelCorrection(distortedX, distortedY);
		m_camera->addFilter(m_barrelCorrection);
	}
}

///
/// \brief TODO: Document this properly :D
///
void CameraWidget::setCoordinateMapping(int leftOffset, float leftZDiff, 
									  int rightOffset, float rightZDiff, 					  
									  int topOffset, float topZDiff, 
									  int bottomOffset, float bottomZDiff)
{
	m_leftOffset	= leftOffset;
	m_leftZDiff		= leftZDiff;
	m_rightOffset	= rightOffset;
	m_rightZDiff	= rightZDiff;
	m_topOffset		= topOffset;
	m_topZDiff		= topZDiff;
	m_bottomOffset	= bottomOffset;
	m_bottomZDiff	= bottomZDiff;
}

///
/// \brief Set the machine coordinates the machine head currently is at.
///
void CameraWidget::setMachineCoordinates(int x, int y, int z)
{
	m_machineX = x;
	m_machineY = y;
	m_machineZ = z;
}

///
/// \brief Returns the visible region shown in the camera view of the machines work table.
///
void CameraWidget::getVisibleRegion(int &left, int &right, int &top, int &bottom)
{
	left	= m_machineX + m_leftOffset		+ (m_machineZ * m_leftZDiff);
	right	= m_machineX + m_rightOffset	+ (m_machineZ * m_rightZDiff);
	top		= m_machineY + m_topOffset		+ (m_machineZ * m_topZDiff);
	bottom	= m_machineY + m_bottomOffset	+ (m_machineZ * m_bottomZDiff);
}

///
/// \brief Start receiving images from the camera.
///
void CameraWidget::start()
{
	if(m_camera != NULL)
	{
		m_camera->start();
	}
}

///
/// \brief Stop receiving images from the camera.
///
void CameraWidget::stop()
{
	if(m_camera != NULL)
	{
		m_camera->stop();
	}
}

///
/// \brief Sets if machine commands should be drawn or not.
///
void CameraWidget::setDrawCommands(bool enabled)
{
}

///
/// \brief Sets if machine head position coordinates will be drawn when moving the mouse over the camera widget.
///
void CameraWidget::setDrawHeadPosition(bool enabled)
{
}

///
/// \brief TODO: Document this.
///
void CameraWidget::setDrawEdges(bool enabled)
{
}

///
/// \brief Returns the current camera image in CameraAPI format.
///
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

// TODO: Add a way to add points to draw... This will be used when creating new pick/place commands, so that they are drawn before the actual command has been created.

///
/// \brief Sets the interaction mode for the camera widget. Is the user picking/placing/moving/dispensing?
///
void CameraWidget::setMode(InteractionMode mode)
{
	this->m_mode = mode;
}

///
/// \brief Get the interaction mode for the camera widget.
///
CameraWidget::InteractionMode CameraWidget::getMode()
{
	return this->m_mode;
}

///
/// \brief Reset a specific mode.
///
void CameraWidget::resetMode(InteractionMode mode)
{

}

///
/// \brief Resets all the pick/place/dispense points and polygons.
///
void CameraWidget::resetModes()
{
	// TODO: Reset all pick/place/dispense points/polygons.
}


