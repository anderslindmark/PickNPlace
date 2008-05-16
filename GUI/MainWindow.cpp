

#include "MainWindow.h"	// GUI.
#include <QString>		// Qt.
#include <QMessageBox>

PicknPlaceGui::MainWindow *mainwindow;

///
/// \brief Callback wrapper function for Machine events.
///        calls the corresponding member method on the mainwindow object.
///
void on_machine_event(MachineEvent *e)
{
	mainwindow->OnMachineEvent(e);
}

namespace PicknPlaceGui
{
	///
	/// \brief Constructor.
	///
	MainWindow::MainWindow()
	{
		mainwindow = this;

		// Runs the generated code that setups the initial UI.
		this->m_ui.setupUi(this);

		this->m_ui.m_pInformationFrame->setVisible(false);
	
		this->ConnectSlots();

		this->InitCameraManager();
		this->CreateToolbarButtons();
		this->InitMachineController();
	}

	///
	/// \brief Initializes the Machine Controller and runs the machines init sequence.
	///
	void MainWindow::InitMachineController()
	{
		// TODO: Add a checkbox "don't show this warning again" and save the state in the config file.
		int ret = QMessageBox::warning(this, tr("Pick and Place"),
                           tr("The Pick and Place machine is about to run its initialization sequence"
								"\nplease make sure nothing is in its way."),
							  QMessageBox::Ok | QMessageBox::Cancel,
							  QMessageBox::Ok);

		if (ret == QMessageBox::Cancel)
		{
			// TODO: Abort and shutdown.
			return;
		}

		// Create the machine controller and associate a callback function with it.
		this->m_pMC = new MachineController("com1"); // TODO: Let the user choose com port.
		this->m_pMC->AddEventHandler(&on_machine_event);
		
		// Init the machine controller.
		if (!this->m_pMC->InitializeMachine())
		{
			// TODO: Fail and exit if the machine controler cannot be initialized?
		}
	}

	void MainWindow::InitCameraManager()
	{
		/*		
		camera::CameraManager *cameraManager = camera::CameraManager::getInstance();
		camera::DummyDriver *dd = new camera::DummyDriver();
		dd->setImageSize(400, 400);
		cameraManager->addDriver(dd);

		//camera::EuresysDriver *euresysDriver = new camera::EuresysDriver();
		//cameraManager->addDriver(euresysDriver);

		camera::CameraIdentifierList identifiers = cameraManager->getCameraIdentifiers();

		m_pMainCameraWidget->setCamera(identifiers.at(1));
		m_pMainCameraWidget->start();
		
		int distortedX[8] = {31, 350, 732, 30, 741, 37, 355, 731};
		int distortedY[8] = {60, 30, 17, 288, 288, 513, 542, 550};
		m_pMainCameraWidget.setImageCorrectionParameters(distortedX, distortedY);
		*/
	}

	///
	/// \brief Creates the buttons for the toolbars and connects them to their slots. 
	/// (This is only done here because the QT Designer doesn't allow you to do this in the GUI).
	/// ATTENTION! - The ":/Images" directory here refers to the QT resoures file, the name of the directory
	/// is case sensitive so it needs to have the exact same name on your filesystem!!
	///
	void MainWindow::CreateToolbarButtons()
	{
		//
		// Mode toolbar.
		//
		this->m_pPickNPlaceToolAction = new QAction(QIcon(":/Images/pnp_icon.png"), tr("&Pick and Place"), this);
		this->m_pPickNPlaceToolAction->setCheckable(true);
		this->m_pPickNPlaceToolAction->setShortcut(tr("Ctrl+P"));
		this->m_pPickNPlaceToolAction->setStatusTip(tr("Enter Pick and Place mode"));
		QMainWindow::connect(m_pPickNPlaceToolAction, SIGNAL(triggered()), this, SLOT(PickNPlaceActionTriggered()));

		this->m_pDispenceToolAction = new QAction(QIcon(":/Images/dispence_icon.png"), tr("&Dispence"), this);
		this->m_pDispenceToolAction->setCheckable(true);
		this->m_pDispenceToolAction->setShortcut(tr("Ctrl+D"));
		this->m_pDispenceToolAction->setStatusTip(tr("Enter Dispence mode"));
		QMainWindow::connect(m_pDispenceToolAction, SIGNAL(triggered()), this, SLOT(DispenceActionTriggered()));

		// Create an action group so that only one mode can be active at any given time.
		this->m_pModesActionGroup = new QActionGroup(this);
		this->m_pModesActionGroup->addAction(this->m_pPickNPlaceToolAction);
		this->m_pModesActionGroup->addAction(this->m_pDispenceToolAction);
		this->m_pPickNPlaceToolAction->setChecked(true);

		this->m_ui.m_pModeToolBar->addAction(this->m_pPickNPlaceToolAction);
		this->m_ui.m_pModeToolBar->addAction(this->m_pDispenceToolAction);

		//
		// Tools toolbar.
		//
		this->m_pZoomToolAction = new QAction(QIcon(":/Images/zoom_icon.png"), tr("&Zoom"), this);
		this->m_pZoomToolAction->setCheckable(true);
		this->m_pZoomToolAction->setShortcut(tr("Ctrl+Z"));
		this->m_pZoomToolAction->setStatusTip(tr("Show the zoomed in camera view for fine positioning"));
		QMainWindow::connect(m_pZoomToolAction, SIGNAL(triggered()), this, SLOT(ZoomActionTriggered()));

		this->m_pShowPolygonToolAction = new QAction(QIcon(":/Images/showpoly_icon.png"), tr("Show &Polygons"), this);
		this->m_pShowPolygonToolAction->setCheckable(true);
		this->m_pShowPolygonToolAction->setShortcut(tr("Ctrl+P"));
		this->m_pShowPolygonToolAction->setStatusTip(tr("Shows polygons on the camera image"));
		QMainWindow::connect(m_pShowPolygonToolAction, SIGNAL(triggered()), this, SLOT(ShowPolygonActionTriggered()));

		this->m_ui.m_pToolsToolBar->addAction(this->m_pZoomToolAction);
		this->m_ui.m_pToolsToolBar->addAction(this->m_pShowPolygonToolAction);
		this->m_ui.m_pToolsToolBar->addSeparator();

		// Interaction tools.
		this->m_pMoveToolAction = new QAction(QIcon(":/Images/move_icon.png"), tr("Move"), this);
		this->m_pMoveToolAction->setCheckable(true);
		
		this->m_pDispenseDotToolAction = new QAction(QIcon(":/Images/dispensedot_icon.png"), tr("Dispense dot"), this);
		this->m_pDispenseDotToolAction->setCheckable(true);
		this->m_pDispenseDotToolAction->setVisible(false);
		this->m_pDispensePolygonToolAction = new QAction(QIcon(":/Images/dispensepoly_icon.png"), tr("Dispense polygon"), this);
		this->m_pDispensePolygonToolAction->setCheckable(true);
		this->m_pDispensePolygonToolAction->setVisible(false);
		
		this->m_pPickToolAction = new QAction(QIcon(":/Images/pick_icon.png"), tr("Pick"), this);
		this->m_pPickToolAction->setCheckable(true);
		this->m_pPlaceToolAction = new QAction(QIcon(":/Images/place_icon.png"), tr("Place"), this);
		this->m_pPlaceToolAction->setCheckable(true);

		this->m_pInteractionActionGroup = new QActionGroup(this);
		this->m_pInteractionActionGroup->addAction(this->m_pMoveToolAction);
		this->m_pInteractionActionGroup->addAction(this->m_pDispenseDotToolAction);
		this->m_pInteractionActionGroup->addAction(this->m_pDispensePolygonToolAction);
		this->m_pInteractionActionGroup->addAction(this->m_pPickToolAction);
		this->m_pInteractionActionGroup->addAction(this->m_pPlaceToolAction);

		this->m_ui.m_pToolsToolBar->addAction(this->m_pMoveToolAction);
		this->m_ui.m_pToolsToolBar->addAction(this->m_pDispenseDotToolAction);
		this->m_ui.m_pToolsToolBar->addAction(this->m_pDispensePolygonToolAction);
		this->m_ui.m_pToolsToolBar->addAction(this->m_pPickToolAction);
		this->m_ui.m_pToolsToolBar->addAction(this->m_pPlaceToolAction);

	}

	void MainWindow::ToggleInteractionTools()
	{
		bool pnp = (this->m_guimode == PickNPlaceMode);
	
		this->m_pPickToolAction->setVisible(pnp);
		this->m_pPlaceToolAction->setVisible(pnp);

		this->m_pDispensePolygonToolAction->setVisible(!pnp);
		this->m_pDispenseDotToolAction->setVisible(!pnp);
	}

	void MainWindow::ShowInformation(QString message, QMessageBox::Icon icon)
	{
		this->m_ui.m_pInformationFrame->setVisible(true);

		//int iconSize = QApplication::style()->pixelMetric(QStyle::PM_MessageBoxIconSize);
		
		// Get the icon pixmap.
		QIcon tmpIcon;
		switch (icon) 
		{
			case QMessageBox::Icon::Information:
				tmpIcon = QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation);
				break;
			case QMessageBox::Icon::Warning:
				tmpIcon = QApplication::style()->standardIcon(QStyle::SP_MessageBoxWarning);
				break;
			case QMessageBox::Icon::Critical:
				tmpIcon = QApplication::style()->standardIcon(QStyle::SP_MessageBoxCritical);
				break;
			case QMessageBox::Icon::Question:
				tmpIcon = QApplication::style()->standardIcon(QStyle::SP_MessageBoxQuestion);
			default:
				break;
		}
		
		if (!tmpIcon.isNull())
		{
			this->m_ui.m_pInformationIconLabel->setPixmap(tmpIcon.pixmap(16, 16));
		}
		else
		{
			this->m_ui.m_pInformationIconLabel->setPixmap(NULL);
		}

		// Set the information message.
		this->m_ui.m_pInformationLabel->setText(message);
	}

	///
	/// \brief Connects all slots for the GUI.
	///
	void MainWindow::ConnectSlots()
	{
		QMainWindow::connect(this->m_ui.m_pCloseInformationButton, SIGNAL(pressed()), this, SLOT(CloseInformationBar()));

		QMainWindow::connect(this->m_ui.m_pBrightnessVerticalSlider, SIGNAL(valueChanged(int)), this, SLOT(BrightnessSliderChanged(int)));

		QMainWindow::connect(this->m_ui.m_pLockZPushButton, SIGNAL(toggled(bool)), this, SLOT(ZLockButtonToggled(bool)));

		QMainWindow::connect(this->m_ui.m_pXSpinBox, SIGNAL(valueChanged(int)), this, SLOT(XValueChanged(int)));
		QMainWindow::connect(this->m_ui.m_pYSpinBox, SIGNAL(valueChanged(int)), this, SLOT(YValueChanged(int)));
		QMainWindow::connect(this->m_ui.m_pZSpinBox, SIGNAL(valueChanged(int)), this, SLOT(ZValueChanged(int)));
		
		QMainWindow::connect(this->m_ui.m_pCommandsListWidget, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), 
			this, SLOT(CommandListItemChanged(QListWidgetItem *, QListWidgetItem *)));

	}

	///
	/// \brief Destructor, cleanup of the Machine controller.
	///
	MainWindow::~MainWindow()
	{
		if (this->m_pMC)
		{
			delete this->m_pMC;
		}
	}

	///
	/// \brief Callback function for any MachineController events.
	///
	void MainWindow::OnMachineEvent(MachineEvent *e) // TODO: This should not be passed as a pointer, but by value, so that we don't have to care about deleting this here!
	{
		MachineEventType type = e->GetEventType();

		if (type == EVENT_MACHINE_INITIALIZED)
		{
			// TODO: Do something here?
			mainwindow->statusBar()->showMessage("Machine initialized successfully");
		}
		else if (type == EVENT_CMD_DONE)
		{
		}
		else if (type == EVENT_CMD_FAILED)
		{
			this->statusBar()->showMessage(e->GetEventMsg().c_str());
		}
		else if (type == EVENT_CMD_ILLEGAL)
		{
			this->statusBar()->showMessage(e->GetEventMsg().c_str());
		}
		else if (type == EVENT_CMD_OUT_OF_BOUNDS)
		{
			this->statusBar()->showMessage(e->GetEventMsg().c_str());
		}
		
		// TODO: Handle all event types and show error dialogs and such.

		delete e;
	}

	///
	/// ======================================== SLOTS ==================================================
	///

	///
	/// \brief Slot for when the "Pick and Place" toolbar button (QAction) has been triggered, this should change the GUI mode.
	///
	void MainWindow::PickNPlaceActionTriggered()
	{
		if (this->m_pPickNPlaceToolAction->isChecked())
		{
			// TODO: Change to Pick and place mode.
			this->m_guimode = PickNPlaceMode;
			this->ToggleInteractionTools();
		}
	}

	///
	/// \brief Slot for when the "Dispence" toolbar button (QAction) has been triggered, this should change the GUI mode.
	///
	void MainWindow::DispenceActionTriggered()
	{
		if (this->m_pDispenceToolAction->isChecked())
		{
			// TODO: Change to Dispence mode.
			this->m_guimode = DispenceMode;
			this->ToggleInteractionTools();
		}
	}

	///
	/// \brief Slot for when the "Zoom" action is triggered.
	///
	void MainWindow::ZoomActionTriggered()
	{
		if (this->m_pZoomToolAction->isChecked())
		{
			// TODO: Turn on the zoom camera on the camera widget.
		}
		else
		{
		}
	}
	
	///
	/// \brief Slot for when the "Show polygon" action is triggered.
	///
	void MainWindow::ShowPolygonActionTriggered()
	{
		if (this->m_pShowPolygonToolAction->isChecked())
		{
			// TODO: Toggle drawing polygons on the camera widget.

		}
		else
		{
		}
	}

	///
	/// \brief Slot for when the brightness slider changes.
	///
	void MainWindow::BrightnessSliderChanged(int value)
	{
		// TODO: Set the brightness for the machine.
		this->m_ui.m_pYSpinBox->setValue(value);
	}

	///
	/// \brief The Z lock button was toggled.
	///
	void MainWindow::ZLockButtonToggled(bool toggled)
	{
		// Toggle the Z spinbox and slider (If the button is pressed they should be locked).
		this->m_ui.m_pZSpinBox->setEnabled(!toggled);
		this->m_ui.m_pZVerticalSlider->setEnabled(!toggled);
	}

	///
	/// \brief The Z value changed in the GUI.
	///
	void MainWindow::ZValueChanged(int value)
	{
		// TODO: Change the Z-Level for the machine head.
	}

	///
	/// \brief The Y value changed in the GUI.
	///
	void MainWindow::YValueChanged(int value)
	{
		// TODO: Change the Y-value for the machine head.
		this->ShowInformation(tr("Hello!"), QMessageBox::Icon::Warning);
	}

	///
	/// \brief The X value changed in the GUI.
	///
	void MainWindow::XValueChanged(int value)
	{
		// TODO: Change the X-value for the machine head.
	}

	///
	/// \brief Slot for when a new item in the command list is selected.
	///
	void MainWindow::CommandListItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
	{
		this->m_ui.m_pRemoveCommandButton->setEnabled(current != NULL);
	}

	// TODO: Add an event for when the camera widget has been clicked.

	///
	/// \brief Slot for when the close button on the information bar is pressed. Closes the information bar.
	///
	void MainWindow::CloseInformationBar()
	{
		this->m_ui.m_pInformationFrame->setVisible(false);
	}
}






