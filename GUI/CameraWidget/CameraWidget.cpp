
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
	
	this->m_camera				= NULL;
	this->m_barrelCorrection	= NULL;
	this->m_pDispensePolygon	= NULL;

	this->m_image = QImage(500, 500, QImage::Format_RGB32);
	QPainter painter(&this->m_image);
	painter.setBrush(Qt::BrushStyle::DiagCrossPattern);
	painter.fillRect(0, 0, 800, 500, painter.brush());

	this->m_currentPickCount	= 0;
	this->m_currentPlaceCount	= 0;
	this->m_machineX			= 0;
	this->m_machineY			= 0;
	this->m_machineZ			= 0;
	this->m_dispenseDotRadius	= 10;
	this->m_commands			= NULL;
	this->m_mode = Pick;
}

CameraWidget::~CameraWidget()
{
	if (this->m_camera != NULL)
	{
		delete this->m_camera;
	}

	if (this->m_barrelCorrection != NULL)
	{
		delete this->m_barrelCorrection;
	}

	if (this->m_pDispensePolygon != NULL)
	{
		delete this->m_pDispensePolygon;
		this->m_pDispensePolygon = NULL;
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

void CameraWidget::mouseMoveEvent(QMouseEvent * event)
{
	this->m_mouseX = event->x();
	this->m_mouseY = event->y();
	this->update();
}

void CameraWidget::leaveEvent(QEvent * event)
{
	// Don't draw the helper line when moving outside the control.
	this->m_mouseX = this->size().width() + 1;
	this->m_mouseY = this->size().height() + 1;
	this->update();
}

void CameraWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	QSize s = this->size();
	QSize imgs = this->m_image.size();
	
	// Scale the image to fit the camera widget while keeping aspect ratio.
	QImage scaledImage = m_image.scaled(s); //, Qt::IgnoreAspectRatio, Qt::TransformationMode::FastTransformation); // TODO: Change this to FastTransform if performance sucks :)

	// Draw the image in the center of the control.
	int x = (s.width() - scaledImage.width()) / 2;
	int y = (s.height() - scaledImage.height()) / 2;

	painter.drawImage(x, y, scaledImage);
	
	//
	// Draw the commands in the command queue.
	//
	if (this->m_commands && this->m_drawCommands)
	{
		painter.setBrush(QBrush(QColor(155, 185, 120, 150)));
		QPen hp = QPen(QColor(255, 100, 100, 150));
		hp.setWidth(4);
		QPen p = QPen(QColor(100, 255, 100, 150));
		p.setWidth(2);
		painter.setPen(p);

		for (int i = 0; i < this->m_commands->size(); i++)
		{
			if (i == this->m_higlightedCommand)
			{
				painter.setPen(hp);
			}
			else
			{
				painter.setPen(p);
			}

			PicknPlaceGui::GuiMachineCommand *c = this->m_commands->at(i);
			PicknPlaceGui::DispencePolygonCommand *dpc = dynamic_cast<PicknPlaceGui::DispencePolygonCommand *>(c);
			PicknPlaceGui::DispenceDotCommand *ddc = dynamic_cast<PicknPlaceGui::DispenceDotCommand *>(c);
			PicknPlaceGui::PickAndPlaceCommand *pnp = dynamic_cast<PicknPlaceGui::PickAndPlaceCommand *>(c);

			if (dpc)
			{
				// Dispense polygon.
				std::vector<MachinePolygonPoint> points = dpc->GetPoints();
				MachinePolygonPoint pp = points.front();
				MachinePolygonPoint prev = pp;

				for (unsigned int j = 0; j < points.size(); j++)
				{
					pp = points.at(j);
					this->machineToWidgetCoordinates(pp.x, pp.y, pp.x, pp.y);
					
					if (j != 0)
					{
						painter.drawLine(prev.x, prev.y, pp.x, pp.y);
					}
					
					prev = pp;
				}
			}
			else if (ddc)
			{
				// Dispense dot.
				PicknPlaceGui::Coordinate2D coord = ddc->GetCoordinate();
				this->machineToWidgetCoordinates(coord.x, coord.y, coord.x, coord.y);
				painter.drawEllipse(coord.x - 5, coord.y - 5, 10, 10);
			}
			else if (pnp)
			{
				PicknPlaceGui::Coordinate2D coord;

				// Pick and place.
				// TODO: Drawn some icon making it obvious what this is, and also show the angle of the pick/place somehow. And an arrow from the pick to the place point.
				coord = pnp->GetPickCoordinate();
				this->machineToWidgetCoordinates(coord.x, coord.y, coord.x, coord.y);
				painter.drawEllipse(coord.x, coord.y, 5, 5);

				coord = pnp->GetPlaceCoordinate();
				this->machineToWidgetCoordinates(coord.x, coord.y, coord.x, coord.y);
				painter.drawEllipse(coord.x, coord.y, 5, 5);
			}
		}
	}
	
	//
	// Draw the current command being created by the user.
	//
	int widgetX = 0;
	int widgetY = 0;	
	int nodeSize = 5;

	switch (this->m_mode)
	{
		default:
		case Move:
		{
			break;
		}
		case Calibration:
		{
			break;
		}
		case DispenseDot:
		{
			// TODO: How do we draw this properly???
			nodeSize = (int)this->m_dispenseDotRadius;

			QBrush b = QBrush(QColor(0, 255, 0, 200));
			painter.setBrush(b);
			painter.setPen(Qt::darkGreen);

			QPoint p = this->m_dispenseDotPoint;

			this->machineToWidgetCoordinates(p.x(), p.y(), widgetX, widgetY);
			painter.drawEllipse(widgetX - (nodeSize / 2), widgetY - (nodeSize / 2), nodeSize, nodeSize);
			
			break;
		}
		case DispensePolygon:
		{	
			if (this->m_pDispensePolygon)
			{
				nodeSize = 10;

				QBrush b = QBrush(QColor(0, 255, 0, 200));
				painter.setBrush(b);
				painter.setPen(Qt::darkGreen);
				
				QPen p = painter.pen();
				QPen fatPen = painter.pen();
				fatPen.setWidth(4);
				fatPen.setColor(QColor(0, 255, 0, 200));

				std::vector<MachinePolygonPoint> points = this->m_pDispensePolygon->GetPoints();
								
				//
				// Draw polygon lines.
				//
				int prevX = 0;
				int prevY = 0;
				painter.setPen(fatPen);

				for (unsigned int i = 0; i < points.size(); i++)
				{
					this->machineToWidgetCoordinates(points[i].x, points[i].y, widgetX, widgetY);
					
					if (i != 0)
					{					
						painter.drawLine(prevX, prevY, widgetX, widgetY);
					}
					
					prevX = widgetX;
					prevY = widgetY;
				}

				//
				// Draw corner points.
				//
				painter.setPen(p);

				for (unsigned int i = 0; i < points.size(); i++)
				{
					this->machineToWidgetCoordinates(points[i].x, points[i].y, widgetX, widgetY);
					painter.drawEllipse(widgetX - (nodeSize / 2), widgetY - (nodeSize / 2), nodeSize, nodeSize);
				}

				//
				// Draw a helper line.
				//
				if (this->m_mouseX < this->size().width() && this->m_mouseY < this->size().height() && (points.size() > 0))
				{
					painter.setPen(QPen(QBrush(QColor(255, 150, 0, 200)), 2, Qt::DotLine));

					MachinePolygonPoint prev = points.back();

					int adjustedX = 0;
					int adjustedY = 0;
					this->machineToWidgetCoordinates(prev.x, prev.y, widgetX, widgetY);
					// TODO: Put the stuff below in a separate function (used in 2 places).
					int deltaX = this->m_mouseX - widgetX;
					int deltaY = this->m_mouseY - widgetY;
					
					// Dispense polygons only allow points that are at 90 degree angels to each other
					// so we snap the actual point to one of the axis here.
					if (abs(deltaX) >= abs(deltaY))
					{
						// Snap to X-axis.
						adjustedX = this->m_mouseX;
						adjustedY = widgetY;
					}
					else
					{
						// Snap to Y-axis.
						adjustedX = widgetX;
						adjustedY = this->m_mouseY;
					}

					painter.drawLine(widgetX, widgetY, adjustedX, adjustedY);
				}
			}
			break;
		}
		case Pick:
		{	
			painter.setBrush(Qt::white);
			painter.setPen(Qt::darkRed);

			for (int i = 0; i < 3; i++)
			{
				this->machineToWidgetCoordinates(this->m_pickPoints[i].x(), this->m_pickPoints[i].y(), widgetX, widgetY);
				painter.drawEllipse(widgetX, widgetY, 5, 5);
			}
			break;
		}
		case Place:
		{
			painter.setBrush(Qt::blue);
			painter.setPen(Qt::darkBlue);

			for (int i = 0; i < 3; i++)
			{
				this->machineToWidgetCoordinates(this->m_placePoints[i].x(), this->m_placePoints[i].y(), widgetX, widgetY);
				painter.drawEllipse(widgetX, widgetY, 5, 5);
			}
			break;
		}
	}
}

// TODO: Hmmm, is this really needed when we have proper aspect ratio ??
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
	Qt::MouseButton button = event->button();
	int mouseMachineX = 0; 
	int mouseMachineY = 0;

	this->widgetToMachineCoordinates(event->x(), event->y(), mouseMachineX, mouseMachineY);

	switch (this->m_mode)
	{
		default:
		case Move:
		{		
			// Signal that we want to move the head to new machine coordinates.
			emit newMachineCoordinates(mouseMachineX, mouseMachineY);
			emit newMachineX(mouseMachineX);
			emit newMachineY(mouseMachineY);			
			break;
		}
		case Calibration:
		{		
			// TODO: Do magic here!
			break;
		}
		case DispenseDot:
		{
			if (button == Qt::LeftButton)
			{
				this->m_dispenseDotPoint.setX(mouseMachineX);
				this->m_dispenseDotPoint.setY(mouseMachineY);
				emit this->commandReady(this->m_mode, this->m_dispenseDotPoint);
			}
			break;
		}
		case DispensePolygon:
		{
			if (button == Qt::LeftButton)
			{
				int adjustedX = 0;
				int adjustedY = 0;

				if (this->m_pDispensePolygon == NULL)
				{
					this->m_pDispensePolygon = new PicknPlaceGui::DispencePolygonCommand();
					
					adjustedX = mouseMachineX;
					adjustedY = mouseMachineY;
				}
				else
				{
					// Get the previous point.
					MachinePolygonPoint prev = this->m_pDispensePolygon->GetPoints().back();

					int deltaX = mouseMachineX - prev.x;
					int deltaY = mouseMachineY - prev.y;
					
					// Dispense polygons only allow points that are at 90 degree angels to each other
					// so we snap the actual point to one of the axis here.
					if (abs(deltaX) >= abs(deltaY))
					{
						// Snap to X-axis.
						adjustedX = mouseMachineX;
						adjustedY = prev.y;
					}
					else
					{
						// Snap to Y-axis.
						adjustedX = prev.x;
						adjustedY = mouseMachineY;
					}
				}

				MachinePolygonPoint pp(adjustedX, adjustedY);
				this->m_pDispensePolygon->AddPoint(pp);
			}

			break;
		}
		case Pick:
		{	
			this->m_currentPickCount = min(this->m_currentPickCount, 2);
			this->m_pickPoints[this->m_currentPickCount].setX(mouseMachineX);
			this->m_pickPoints[this->m_currentPickCount].setY(mouseMachineY);
			this->m_currentPickCount++;

			break;
		}
		case Place:
		{
			this->m_currentPlaceCount = min(this->m_currentPlaceCount, 2);
			this->m_placePoints[this->m_currentPlaceCount].setX(mouseMachineX);
			this->m_placePoints[this->m_currentPlaceCount].setY(mouseMachineY);
			this->m_currentPlaceCount++;

			break;
		}
	}
	
	// Force a redraw so any new graphics will become visible.
	this->update();

	if ((this->m_mode == Pick || this->m_mode == Place) && isPickPlaceReady())
	{
		emit this->commandReady(this->m_mode, this->m_pickPoints, this->m_placePoints);
	}
}

///
/// \returns If both the Pick and Place coordinates have been placed.
///
bool CameraWidget::isPickPlaceReady()
{
	bool ready = true;

	for (int i = 0; i < 3; i++)
	{
		ready = ready && !this->m_placePoints[i].isNull() && !this->m_pickPoints[i].isNull();
	}

	return ready;
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
	if(m_barrelCorrection != NULL)
	{
		m_camera->addFilter(m_barrelCorrection);
	}
}

///
/// \brief Sets the image correction parameters used to get rid of the barrel distortion.
/// TODO: Explain more how to obtain these coordinates.
///
void CameraWidget::setImageCorrectionParameters(int distortedRectangle[8][2])
{
	if(m_barrelCorrection != NULL)
	{
		m_barrelCorrection->setDistortedRectangle(distortedRectangle);
	}
	else
	{
		m_barrelCorrection = new camera::BarrelCorrection(distortedRectangle);
		m_barrelCorrection->setEnabled(true);
		if(m_camera != NULL)
		{
			m_camera->addFilter(m_barrelCorrection);
		}
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
	this->m_drawCommands = enabled;
	this->update();
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

///
/// \brief Sets the interaction mode for the camera widget. Is the user picking/placing/moving/dispensing?
///
void CameraWidget::setMode(InteractionMode mode)
{
	this->m_mode = mode;
	this->setMouseTracking(this->m_mode == DispensePolygon);
	this->update();
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
	switch (mode)
	{
		default:
		case Move:
		{		
			// TODO: Reset something here? :D
			break;
		}
		case Calibration:
		{		
			// TODO: Reset something here? :D
			break;
		}
		case DispenseDot:
		{
			this->m_dispenseDotPoint.setX(0);
			this->m_dispenseDotPoint.setY(0);
			this->m_dispenseDotRadius = 0;
			break;
		}
		case DispensePolygon:
		{		
			if (this->m_pDispensePolygon)
			{
				delete this->m_pDispensePolygon;
				this->m_pDispensePolygon = NULL;
			}

			this->m_currentPlaceCount = 0;

			break;
		}
		case Pick:
		{	
			for (int i = 0; i < 3; i++)
			{
				this->m_pickPoints[i].setX(0);
				this->m_pickPoints[i].setY(0);
			}

			this->m_currentPickCount = 0;

			break;
		}
		case Place:
		{
			for (int i = 0; i < 3; i++)
			{
				this->m_placePoints[i].setX(0);
				this->m_placePoints[i].setY(0);
			}
			
			this->m_currentPlaceCount = 0;

			break;
		}
	}

	// Make sure we redraw.
	this->update();

	emit this->commandInvalid();
}

///
/// \brief Resets the current GUI mode.
///
void CameraWidget::resetCurrentMode()
{
	this->resetMode(this->m_mode);
}

///
/// \brief Resets all the pick/place/dispense points and polygons.
///
void CameraWidget::resetModes()
{
	this->resetMode(InteractionMode::Move);
	this->resetMode(InteractionMode::Calibration);
	this->resetMode(InteractionMode::DispenseDot);
	this->resetMode(InteractionMode::DispensePolygon);
	this->resetMode(InteractionMode::Pick);
	this->resetMode(InteractionMode::Place);
}

///
/// \brief Returns the current dispense polygon being created on the camera widget.
///
PicknPlaceGui::DispencePolygonCommand *CameraWidget::getDispensePolygon()
{
	return this->m_pDispensePolygon;
}

///
/// \brief Returns the current dispense dot being created on the camera widget.
///
QPoint CameraWidget::getDotDispensePoint()
{
	return this->m_dispenseDotPoint;
}

///
/// \brief Returns the current pick points being created on the camera widget.
///
QPoint *CameraWidget::getPickPoints()
{
	return this->m_pickPoints;
}

///
/// \brief Returns the current place points being created on the camera widget.
///
QPoint *CameraWidget::getPlacePoints()
{
	return this->m_placePoints;
}

///
/// \brief Gets the current size of the camera widget in machine coordinates. 
/// This is dependent on which zoom level and so on.
///
void CameraWidget::getMachineCoordinateSize(int &width, int &height)
{
	int machineLeft, machineRight, machineTop, machineBottom;
	getVisibleRegion(machineLeft, machineRight, machineTop, machineBottom);
	
	// Machine coordinates have 0,0 in the bottom left corner
	width = abs(machineRight - machineLeft);
	height = abs(machineTop - machineBottom);
}

///
/// \brief Converts from machine coordinates to widget coordinates.
///
void CameraWidget::machineToWidgetCoordinates(int machineX, int machineY, int &widgetX, int &widgetY)
{
	int machineLeft, machineRight, machineTop, machineBottom;
	getVisibleRegion(machineLeft, machineRight, machineTop, machineBottom);
	
	// Machine coordinates have 0,0 in the bottom left corner, widget coordinates has it in the upper left.
	int w = size().width();
	int h = size().height();
	widgetX = w * (machineX - machineLeft) / (float)(machineRight - machineLeft);
	widgetY = h * (machineY - machineTop) / (float)(machineBottom - machineTop);
}

///
/// \brief Converts from widget coordinates to widget coordinates.
///
void CameraWidget::widgetToMachineCoordinates(int widgetX, int widgetY, int &machineX, int &machineY)
{
	int machineLeft, machineRight, machineTop, machineBottom;
	getVisibleRegion(machineLeft, machineRight, machineTop, machineBottom);
	
	// Machine coordinates have 0,0 in the bottom left corner, widget coordinates has it in the upper left.
	int w = size().width();
	int h = size().height();
	machineX = machineLeft + (machineRight - machineLeft) * (widgetX / (float)w);
	machineY = machineTop  + (machineBottom - machineTop) * (widgetY / (float)h);
}

///
/// \brief Sets the radius of the dispense dot.
///
void CameraWidget::setDispenseDotRadius(int radius)
{
	this->m_dispenseDotRadius = radius;
	this->update();
}

///
/// \brief Sets which command to highlight in the camera widget.
///
void CameraWidget::setHighlightedCommandIndex(int index)
{
	this->m_higlightedCommand = index;
	this->update();
}

///
/// \brief Sets the reference to the command list.
///
void CameraWidget::setMachineCommandList(const QList<PicknPlaceGui::GuiMachineCommand *> *commands)
{
	this->m_commands = commands;
}

