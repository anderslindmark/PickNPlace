
#ifndef __CAMERAWIDGET_H__
#define __CAMERAWIDGET_H__

#include <QWidget>
#include <QtDesigner/QDesignerExportWidget>
#include <QtGui/QPainter>
#include <QtGui/QImage>
#include <QPoint>

// CameraAPI.
#include "CameraManager.h"
#include "Camera.h"
#include "CameraListener.h"
#include "CameraException.h"
#include "Image.h"
#include "BarrelCorrection.h"

// PickNPlaceGui.
#include "GuiMachineCommand.h"
#include "DispencePolygonCommand.h"

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

	void cameraNewImage(camera::Camera *camera, camera::Image *image);
	void cameraError(camera::Camera *camera, int errorCode, const std::string &errorMessage);

	void setCamera(const std::string &driverIdentifier, const std::string &cameraIdentifier);
	void setImageCorrectionParameters(int distortedRectangle[8][2]);
	void setCoordinateMapping(int leftOffset, float leftZDiff, 
							  int rightOffset, float rightZDiff, 					  
							  int topOffset, float topZDiff, 
							  int bottomOffset, float bottomZDiff);
	void getVisibleRegion(int &left, int &right, int &top, int &bottom);
	void start();
	void stop();
	void setDrawHeadPosition(bool enabled);
	void setDrawEdges(bool enabled);
	camera::Image *getImage();
	QImage *getQImage();
	void setMachineCommandList(QList<PicknPlaceGui::GuiMachineCommand> *commands);

	///
	/// \enum InteractionMode
	/// \brief The mode that the camera widget is. How the user interacts with the control.
	///
	enum InteractionMode
	{
		Move,				///< The machine head moves where the user clicks on the camera widget.
		Pick,				///< The user selects a component to pick.
		Place,				///< The user selects a position where the picked component should be placed.
		DispenseDot,		///< The user selects a point where to dispense a dot.
		DispensePolygon,	///< The user draws a dispense polygon.
		Calibration			///< The user calibrates the camera image for barrel correction.
	};

	void setMode(CameraWidget::InteractionMode mode);
	InteractionMode getMode(); 

	PicknPlaceGui::DispencePolygonCommand *getDispensePolygon();
	QPoint getDotDispensePoint();
	QPoint *getPickPoints();
	QPoint *getPlacePoints();

	void setDispenseDotRadius(float radius);

	void resetCurrentMode();
	void resetMode(CameraWidget::InteractionMode mode);
	void resetModes();

	void machineToWidgetCoordinates(int machineX, int machineY, int &widgetX, int &widgetY);
	void widgetToMachineCoordinates(int widgetX, int widgetY, int &machineX, int &machineY);
	void getMachineCoordinateSize(int &width, int &height);

public slots:
	void setDrawCommands(bool enabled);
	void setMachineCoordinates(int x, int y, int z);

signals:

	///
	/// \brief Signal for when the user clicks somewhere on the camera image while in "Move" mode.
	/// \param machineX The new X coordinate the user wants to move to.
	/// \param machineY The new Y coordinate the user wants to move to.
	///
	void newMachineCoordinates(int machineX, int machineY);

	///
	/// \brief Signal for when a command that the user is creating on the camera widget is ready/valid to be created.
	/// For instance, if in Pick mode, and a Place has already been created, when the Pick points have been set we have
	/// enough information to create a Pick and Place command, so this signal will then be raised so that the program
	/// knows it can fetch the required information to create a new command.
	///
	void commandReady(CameraWidget::InteractionMode mode, PicknPlaceGui::DispencePolygonCommand *polygon);
	void commandReady(CameraWidget::InteractionMode mode, QPoint *pickPoints, QPoint *placePoints);
	void commandReady(CameraWidget::InteractionMode mode, QPoint dot);

	///
	/// \brief Signal for when the current command being created on the camera widget has been made invalid.
	///
	void commandInvalid();

protected:
    void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent * event);
	void mousePressEvent(QMouseEvent * event);
	void mouseMoveEvent(QMouseEvent * event);
    
private:

	bool isPickPlaceReady();

	camera::Camera 				*m_camera;				///< The camera associated with the camera widget.
	camera::BarrelCorrection	*m_barrelCorrection;	///< The barrel correction filter for the camera.
	QImage m_image;

	CameraWidget::InteractionMode				m_mode;	///< The current mode the camera widget is in (how the user interacts with it).

	QList<PicknPlaceGui::GuiMachineCommand>	*commands;	///< A reference to the list of commands that should be drawn on the camera widget.
	
	int		m_machineX;			///< The current machine x position.
	int		m_machineY;			///< The current machine y position.
	int		m_machineZ;			///< The current machine z position.

	// TODO: Document what these are for.
	int		m_leftOffset;
	float	m_leftZDiff;
	int		m_rightOffset;
	float	m_rightZDiff; 					  
	int		m_topOffset;
	float	m_topZDiff;
	int		m_bottomOffset;
	float	m_bottomZDiff;

	int		m_currentPlaceCount;				///< The current point we're placing in place mode.
	int		m_currentPickCount;					///< The current point we're placing in pick mode.

	// Pick and place.
	QPoint	m_pickPoints[3];					///< The 3 points that the user adds when picking a component.
	QPoint	m_placePoints[3];					///< The 3 points the user adds when placing a component.

	// Dispense dot.
	QPoint	m_dispenseDotPoint;					///< The location of the dispense dot.
	float	m_dispenseDotRadius;				///< The radius of the dispense dot.

	// Dispense polygon.
	PicknPlaceGui::DispencePolygonCommand *m_pDispensePolygon;	///< The dispense polygon when the user is creating a new one.

	int m_mouseX;
	int m_mouseY;
};

#endif // __CAMERAWIDGET_H__

