
#ifndef __CAMERAWIDGET_H__
#define __CAMERAWIDGET_H__

#include <QWidget>
#include <QtDesigner/QDesignerExportWidget>
#include <QtGui/QPainter>
#include <QtGui/QImage>

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
	void setImageCorrectionParameters(unsigned int distortedX[8], unsigned int distortedY[8]);
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

signals:
	///
	/// \brief Signal for when a command that the user is creating on the camera widget is ready/valid to be created.
	/// For instance, if in Pick mode, and a Place has already been created, when the Pick points have been set we have
	/// enough information to create a Pick and Place command, so this signal will then be raised so that the program
	/// knows it can fetch the required information to create a new command.
	///
	void commandReady();

protected:
    void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent * event);
	void mousePressEvent(QMouseEvent * event);
    
private:

	void resetMode(CameraWidget::InteractionMode mode);
	void resetModes();

	camera::Camera 				*m_camera;				///< The camera associated with the camera widget.
	camera::BarrelCorrection	*m_barrelCorrection;	///< The barrel correction filter for the camera.
	QImage m_image;

	CameraWidget::InteractionMode				m_mode;	///< The current mode the camera widget is in (how the user interacts with it).

	QList<PicknPlaceGui::GuiMachineCommand>	*commands;	///< A reference to the list of commands that should be drawn on the camera widget.
	
	int		m_machineX;		///< The current machine x position.
	int		m_machineY;		///< The current machine y position.
	int		m_machineZ;		///< The current machine z position.
	
	// TODO: Document what these are for.
	int		m_leftOffset;
	float	m_leftZDiff;
	int		m_rightOffset;
	float	m_rightZDiff; 					  
	int		m_topOffset;
	float	m_topZDiff;
	int		m_bottomOffset;
	float	m_bottomZDiff;

	// Pick and place.
	QPoint	m_pickPoints[3];					///< The 3 points that the user adds when picking a component.
	QPoint	m_placePoints[3];					///< The 3 points the user adds when placing a component.

	// Dispense dot.
	QPoint	m_dispenseDotPoint;					///< The location of the dispense dot.
	float	m_dispenseDotRadius;				///< The radius of the dispense dot.

	// Dispense polygon.
	PicknPlaceGui::DispencePolygonCommand m_dispensePolygon;	///< The dispense polygon when the user is creating a new one.
};

#endif // __CAMERAWIDGET_H__

