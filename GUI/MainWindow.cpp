

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
	int type = (MachineEventType)e->GetEventType();
	QString message = QString(e->GetEventMsg().c_str());

	QMetaObject::invokeMethod(mainwindow, "MachineEventOccured", Qt::QueuedConnection, 
		Q_ARG(int, type), Q_ARG(QString, message));

	delete e;
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

		this->CloseInformationBar();

		this->ConnectSlots();

		this->InitCameraManager();
		this->CreateToolbarActionGroups();
		this->SetGuiSubMode(Move);
		this->InitMachineController();

		this->m_pProgressDialog = NULL;
		this->m_currentCommandIndex = 0;
		this->m_runningCommandList = false;
	}

	
	///
	/// \brief Destructor.
	///
	MainWindow::~MainWindow()
	{		
		if (this->m_pMC)
		{
			// Make sure the machine controller has done its business.
			this->m_pMC->Wait();
			delete this->m_pMC;
		}
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
			// TODO: Abort and shutdown. Or maybe disable all controls and show a "init button" only in the gui.
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
		this->m_pMC->Wait();
	}

	///
	/// \brief Initializes the Camera Manager.
	///
	void MainWindow::InitCameraManager()
	{
		camera::CameraManager *cameraManager = camera::CameraManager::getInstance();
		
		// Add the dummy driver to the camera manager. This driver is used for testing 
		// the camera API on a computer without any frame grabber card
		/*camera::DummyDriver *dummyDriver = new camera::DummyDriver();
		dummyDriver->setImageSize(768, 576);
		cameraManager->addDriver(dummyDriver);
		*/
		// Add the Euresys driver to the camera manager.
		camera::EuresysDriver *euresysDriver = new camera::EuresysDriver();
		cameraManager->addDriver(euresysDriver);
		
		// TODO: Get the driverIdentifier and cameraIdentifier from the settings
		std::string driverIdentifier = cameraManager->getDriver(0)->getIdentifier();
		std::string cameraIdentifier = cameraManager->getDriver(0)->getCameraIdentifier(2);
		// Set which camera the widget shoud use and start the acquiring
		this->m_ui.m_pMainCameraWidget->setCamera(driverIdentifier, cameraIdentifier);
		
		// TODO: Get the correction parameters from the settings
		int distortedRectangle[8][2] = {
			{31, 60},
			{350, 30},
			{732, 17},
			{30, 288},
			{741, 288},
			{37, 513},
			{355, 542},
			{731, 550}
		};
		// Set the parameters for the barrel correction filter
		this->m_ui.m_pMainCameraWidget->setImageCorrectionParameters(distortedRectangle);
		
		// TODO: Get the coordinate conversion parameters from the settings
		// Set the coordinate conversion parameters
		this->m_ui.m_pMainCameraWidget->setCoordinateMapping(-47500, 0, 47500, 0, 32500, 0, -32500, 0);

		this->m_ui.m_pMainCameraWidget->start();

		this->m_ui.m_pMainCameraWidget->setMachineCommandList(&this->m_commands);
	}

	///
	/// \brief Creates the action groups for the toolbars (so that only one item is selected at once).
	///
	void MainWindow::CreateToolbarActionGroups()
	{
		// Create an action group so that only one mode can be active at any given time.
		this->m_pModesActionGroup = new QActionGroup(this);
		this->m_pModesActionGroup->addAction(this->m_ui.m_pPickNPlaceToolAction);
		this->m_pModesActionGroup->addAction(this->m_ui.m_pDispenceToolAction);
	
		this->m_pInteractionActionGroup = new QActionGroup(this);
		this->m_pInteractionActionGroup->addAction(this->m_ui.m_pMoveToolAction);
		this->m_pInteractionActionGroup->addAction(this->m_ui.m_pDispenseDotToolAction);
		this->m_pInteractionActionGroup->addAction(this->m_ui.m_pDispensePolygonToolAction);
		this->m_pInteractionActionGroup->addAction(this->m_ui.m_pPickToolAction);
		this->m_pInteractionActionGroup->addAction(this->m_ui.m_pPlaceToolAction);
	}

	///
	/// \brief Toggles between the tools that are shown in the Tools toolbar depending on what gui mode the window is in.
	///
	void MainWindow::ToggleInteractionTools()
	{
		bool pnp = (this->m_guimode == PickNPlaceMode);

		this->m_ui.m_pPickToolAction->setVisible(pnp);
		this->m_ui.m_pPlaceToolAction->setVisible(pnp);

		this->m_ui.m_pDispensePolygonToolAction->setVisible(!pnp);
		this->m_ui.m_pDispenseDotToolAction->setVisible(!pnp);
	}

	///
	/// \brief Changes the GUI sub mode.
	/// \param mode The new GUI sub mode to change to.
	///
	void MainWindow::SetGuiSubMode(MainWindow::GuiSubMode mode)
	{
		this->m_subguimode = mode;
		this->UpdateGuiBasedOnGuiSubMode();
	}

	///
	/// \brief Changes the GUI to be consistent with the current GUI Sub mode.
	///
	void MainWindow::UpdateGuiBasedOnGuiSubMode()
	{
		QStackedWidget *msw = this->m_ui.m_pModeStackedWidget;
		CameraWidget *cw = this->m_ui.m_pMainCameraWidget;

		switch (this->m_subguimode)
		{
			default:
			case Move:
			{
				msw->setCurrentWidget(this->m_ui.m_pEmptyModePage);
				cw->setMode(CameraWidget::InteractionMode::Move);
				break;
			}
			case Pick:
			{
				msw->setCurrentWidget(this->m_ui.m_pPickPlaceModePage);
				cw->setMode(CameraWidget::InteractionMode::Pick);
				break;
			}
			case Place:
			{
				msw->setCurrentWidget(this->m_ui.m_pPickPlaceModePage);
				cw->setMode(CameraWidget::InteractionMode::Place);
				break;
			}
			case DispenseDot:
			{
				msw->setCurrentWidget(this->m_ui.m_pDispenseDotModePage);
				cw->setMode(CameraWidget::InteractionMode::DispenseDot);
				break;
			}
			case DispensePolygon:
			{
				msw->setCurrentWidget(this->m_ui.m_pDispensePolyModePage);
				cw->setMode(CameraWidget::InteractionMode::DispensePolygon);
				break;
			}
		}
	}

	///
	/// \brief Shows a information message in the information bar at the top of the window.
	/// \param message The message that should be shown.
	/// \param icon The icon to use when displaying the message, warning/information and so on. Check the QMessageBox::Icon enum for all icon types.
	///
	void MainWindow::ShowInformation(QString message, QMessageBox::Icon icon)
	{
		this->m_ui.m_pInformationFrame->setVisible(true);

		QPalette pal = QApplication::palette();
		
		// Get the icon pixmap.
		QIcon tmpIcon;
		switch (icon) 
		{
			case QMessageBox::Icon::Information:
				tmpIcon = QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation);
				pal.setColor(QPalette::Window, QColor::fromRgb(0, 230, 255));
				break;
			case QMessageBox::Icon::Warning:
				tmpIcon = QApplication::style()->standardIcon(QStyle::SP_MessageBoxWarning);
				pal.setColor(QPalette::ColorRole::Window, QColor::fromRgb(255, 255, 127));
				break;
			case QMessageBox::Icon::Critical:
				tmpIcon = QApplication::style()->standardIcon(QStyle::SP_MessageBoxCritical);
				pal.setColor(QPalette::ColorRole::Window, QColor::fromRgb(255, 190, 0));
				break;
			case QMessageBox::Icon::Question:
				tmpIcon = QApplication::style()->standardIcon(QStyle::SP_MessageBoxQuestion);
				pal.setColor(QPalette::ColorRole::Window, QColor::fromRgb(0, 230, 255));
			default:
				break;
		}

		// TODO: Fix setting palette for the information bar depending on message type, it's not working :(
		this->m_ui.m_pInformationIconLabel->setPalette(pal);
		
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
		//
		// Mode toolbar.
		//
		QMainWindow::connect(this->m_ui.m_pPickNPlaceToolAction, SIGNAL(triggered()), this, SLOT(PickNPlaceActionTriggered()));
		QMainWindow::connect(this->m_ui.m_pDispenceToolAction, SIGNAL(triggered()), this, SLOT(DispenceActionTriggered()));

		//
		// Tools toolbar.
		//
		QMainWindow::connect(this->m_ui.m_pZoomToolAction, SIGNAL(triggered()), this, SLOT(ZoomActionTriggered()));

		// Interaction tools.
		QMainWindow::connect(this->m_ui.m_pMoveToolAction, SIGNAL(triggered()), this, SLOT(MoveToolTriggered()));
		QMainWindow::connect(this->m_ui.m_pDispenseDotToolAction, SIGNAL(triggered()), this, SLOT(DispenseDotToolTriggered()));
		QMainWindow::connect(this->m_ui.m_pDispensePolygonToolAction, SIGNAL(triggered()), this, SLOT(DispensePolygonToolTriggered()));
		QMainWindow::connect(this->m_ui.m_pPickToolAction, SIGNAL(triggered()), this, SLOT(PickToolTriggered()));
		QMainWindow::connect(this->m_ui.m_pPlaceToolAction, SIGNAL(triggered()), this, SLOT(PlaceToolTriggered()));

		//
		// Information bar.
		//
		QMainWindow::connect(this->m_ui.m_pCloseInformationButton, SIGNAL(pressed()), this, SLOT(CloseInformationBar()));

		//
		// Other controls.
		//
		QMainWindow::connect(this->m_ui.m_pBrightnessVerticalSlider, SIGNAL(valueChanged(int)), this, SLOT(BrightnessSliderChanged(int)));
		QMainWindow::connect(this->m_ui.m_pLockZPushButton, SIGNAL(toggled(bool)), this, SLOT(ZLockButtonToggled(bool)));
		QMainWindow::connect(this->m_ui.m_pXSpinBox, SIGNAL(valueChanged(int)), this, SLOT(XValueChanged(int)));
		QMainWindow::connect(this->m_ui.m_pYSpinBox, SIGNAL(valueChanged(int)), this, SLOT(YValueChanged(int)));
		QMainWindow::connect(this->m_ui.m_pZSpinBox, SIGNAL(valueChanged(int)), this, SLOT(ZValueChanged(int)));
		QMainWindow::connect(this->m_ui.m_pCommandsListWidget, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), 
			this, SLOT(CommandListItemChanged(QListWidgetItem *, QListWidgetItem *)));
		QMainWindow::connect(this->m_ui.m_pClearPickPlacePointsButton, SIGNAL(pressed()), this, SLOT(ClearPickPlaceButtonPressed()));
		QMainWindow::connect(this->m_ui.m_pClearPolygonButton, SIGNAL(pressed()), this, SLOT(ClearPolygonButtonPressed()));
		QMainWindow::connect(this->m_ui.m_pRemoveDotButton, SIGNAL(pressed()), this, SLOT(RemoveDotButtonPressed()));
		QMainWindow::connect(this->m_ui.m_pDispenseDotSpinBox, SIGNAL(valueChanged(int)), this, SLOT(DispenseDotSpinBoxValueChanged(int)));
		QMainWindow::connect(this->m_ui.m_pEnqueueCommandButton, SIGNAL(pressed()), this, SLOT(EnqueueCommandButtonPressed()));
		QMainWindow::connect(this->m_ui.m_pRunCommandsButton, SIGNAL(pressed()), this, SLOT(RunCommandsButtonPressed()));
		QMainWindow::connect(this->m_ui.m_pRemoveCommandButton, SIGNAL(pressed()), this, SLOT(RemoveCommandButtonPressed()));
		QMainWindow::connect(this->m_ui.m_pMainCameraWidget, SIGNAL(newMachineCoordinates(int, int)), 
			this, SLOT(CameraWidgetNewMachineCoordinates(int, int)));
		QMainWindow::connect(this->m_ui.m_pMainCameraWidget, SIGNAL(commandReady(CameraWidget::InteractionMode, PicknPlaceGui::DispencePolygonCommand)),
			this, SLOT(CameraWidgetCommandReady(CameraWidget::InteractionMode, PicknPlaceGui::DispencePolygonCommand)));
		QMainWindow::connect(this->m_ui.m_pMainCameraWidget, SIGNAL(commandReady(CameraWidget::InteractionMode, QPoint *, QPoint *)),
			this, SLOT(CameraWidgetCommandReady(CameraWidget::InteractionMode, QPoint *, QPoint *)));
		QMainWindow::connect(this->m_ui.m_pMainCameraWidget, SIGNAL(commandReady(CameraWidget::InteractionMode, QPoint)),
			this, SLOT(CameraWidgetCommandReady(CameraWidget::InteractionMode, QPoint)));
		QMainWindow::connect(this->m_ui.m_pMainCameraWidget, SIGNAL(commandInvalid()), this, SLOT(CameraWidgetCommandInvalid()));
		QMainWindow::connect(this->m_ui.m_pCommandsListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(CommandSelectionChanged()));
		QMainWindow::connect(this->m_ui.m_pRemoveLastPointButton, SIGNAL(pressed()), this, SLOT(RemoveLastPointButtonPressed()));
	}

	void MainWindow::closeEvent(QCloseEvent *event)
	{
		// TODO: Check if the user really wants to quit before closing.
		/*
		if () 
		{
			event->accept();
		} 
		else 
		{
			event->ignore();
		}
		*/
	}

	///
	/// \brief Slot for when a machine event has occured.
	///
	void MainWindow::MachineEventOccured(int type, QString message)
	{
		this->UpdateCameraWidgetMachineCoordinates();

		if (type == EVENT_MACHINE_INITIALIZED)
		{
			//mainwindow->statusBar()->showMessage("Machine initialized successfully");
		}
		else if (type == EVENT_CMD_DONE)
		{
			// Check if there's any more commands to run in the command list.
			if (this->m_runningCommandList)
			{
				this->RunCommands();
			}
		}
		else if (type == EVENT_CMD_FAILED)
		{
			this->ShowInformation(message, QMessageBox::Icon::Critical);
		}
		else if (type == EVENT_CMD_ILLEGAL)
		{
			this->ShowInformation(message, QMessageBox::Icon::Critical);
		}
		else if (type == EVENT_CMD_OUT_OF_BOUNDS)
		{
			this->ShowInformation(message, QMessageBox::Icon::Warning);
		}
	}

	///
	/// \brief Runs the list of commands.
	///
	void MainWindow::RunCommands()
	{
		this->setEnabled(false);
		this->m_runningCommandList = true;

		this->m_ui.m_pMainCameraWidget->setDrawCommands(false);

		if (!this->m_pProgressDialog)
		{
			this->m_pProgressDialog = new QProgressDialog(this);
			this->m_pProgressDialog->setCancelButtonText(tr("Stop"));
			this->m_pProgressDialog->setMaximum(this->m_commands.size());
			QMainWindow::connect(this->m_pProgressDialog, SIGNAL(canceled()), this, SLOT(CommandsCanceled()));		
		}
		else
		{
			this->m_pProgressDialog->setValue(this->m_currentCommandIndex + 1);
		}

		// Run the next command.
		while (this->m_currentCommandIndex < this->m_commands.size())
		{
			PicknPlaceGui::GuiMachineCommand *c = this->m_commands.at(this->m_currentCommandIndex);
			this->m_pMC->RunCommand(c->GetMachineCommand());
			
			// Show progress.
			this->m_pProgressDialog->setLabelText(QString(tr("Running command: %1 (%2 of %3)"))
				.arg(c->toString()).arg(this->m_currentCommandIndex + 1).arg(this->m_commands.size()));
			this->m_pProgressDialog->show();

			this->m_currentCommandIndex++;
			return;
			//this->m_pMC->Wait();
		}

		CommandsCanceled();
		this->m_ui.m_pMainCameraWidget->setDrawCommands(this->m_ui.m_pShowPolygonToolAction->isChecked());
		this->UpdateCameraWidgetMachineCoordinates();
	}

	///
	/// ======================================== SLOTS ==================================================
	///

	///
	/// \brief Slot for when the "Stop" button is clicked on the command progress bar.
	///
	void MainWindow::CommandsCanceled()
	{
		if (this->m_pProgressDialog)
		{
			delete this->m_pProgressDialog;
		}

		this->m_currentCommandIndex = 0;
		this->m_runningCommandList = false;

		this->setEnabled(true);
	}

	///
	/// \brief Slot for when the "Pick and Place" toolbar button (QAction) has been triggered, this should change the GUI mode.
	///
	void MainWindow::PickNPlaceActionTriggered()
	{
		if (this->m_ui.m_pPickNPlaceToolAction->isChecked())
		{
			// Change to Pick and place mode.
			this->m_guimode = PickNPlaceMode;
			this->ToggleInteractionTools();
		}
	}

	///
	/// \brief Slot for when the "Dispense" toolbar button (QAction) has been triggered, this should change the GUI mode.
	///
	void MainWindow::DispenceActionTriggered()
	{
		if (this->m_ui.m_pDispenceToolAction->isChecked())
		{
			// Change to Dispence mode.
			this->m_guimode = DispenceMode;
			this->ToggleInteractionTools();
		}
	}

	///
	/// \brief Slot for when the "Zoom" action is triggered.
	///
	void MainWindow::ZoomActionTriggered()
	{
		if (this->m_ui.m_pZoomToolAction->isChecked())
		{
			// TODO: Turn on the zoom camera on the camera widget.
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
		// Set the brightness for the machine.
		MachineLightBrightnessCommand brightness = MachineLightBrightnessCommand(Lamp::LAMP_CAMERA, value);
		this->m_pMC->RunCommand(brightness);
	}

	///
	/// \brief Updates the machine coordinates for the camera widget.
	///
	void MainWindow::UpdateCameraWidgetMachineCoordinates()
	{
		int x = this->m_pMC->GetCurrentState().GetState().x;
		int y = this->m_pMC->GetCurrentState().GetState().y;
		int z = this->m_pMC->GetCurrentState().GetState().z;
		this->m_ui.m_pMainCameraWidget->setMachineCoordinates(x, y, z);
	}

	///
	/// \brief The Z lock button was toggled.
	///
	void MainWindow::ZLockButtonToggled(bool toggled)
	{
		// Toggle the Z spinbox and slider (If the button is pressed they should be locked).
		this->m_ui.m_pZSpinBox->setEnabled(!toggled);
		this->m_ui.m_pZVerticalSlider->setEnabled(!toggled);
		this->UpdateCameraWidgetMachineCoordinates();
	}

	///
	/// \brief The Z value changed in the GUI.
	///
	void MainWindow::ZValueChanged(int value)
	{
		// Change the Z-Level for the machine head.
		MachineMoveAbsoluteCommand move = MachineMoveAbsoluteCommand(AXIS_Z, value);
		this->m_pMC->RunCommand(move);
		this->m_pMC->Wait();
		this->UpdateCameraWidgetMachineCoordinates();
	}

	///
	/// \brief The Y value changed in the GUI.
	///
	void MainWindow::YValueChanged(int value)
	{
		// Change the Y-value for the machine head.
		MachineMoveAbsoluteCommand move = MachineMoveAbsoluteCommand(AXIS_Y, value);
		this->m_pMC->RunCommand(move);
		this->m_pMC->Wait();
		this->UpdateCameraWidgetMachineCoordinates();
	}

	///
	/// \brief The X value changed in the GUI.
	///
	void MainWindow::XValueChanged(int value)
	{
		// Change the X-value for the machine head.
		MachineMoveAbsoluteCommand move = MachineMoveAbsoluteCommand(AXIS_X, value);
		this->m_pMC->RunCommand(move);
		this->m_pMC->Wait();
		this->UpdateCameraWidgetMachineCoordinates();
	}

	///
	/// \brief Slot for when a new item in the command list is selected.
	///
	void MainWindow::CommandListItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
	{
		this->m_ui.m_pRemoveCommandButton->setEnabled(current != NULL);
	}

	///
	/// \brief Slot for when the close button on the information bar is pressed. Closes the information bar.
	///
	void MainWindow::CloseInformationBar()
	{
		this->m_ui.m_pInformationFrame->setVisible(false);
	}

	///
	/// \brief Slot for when the move tool button is triggered.
	///
	void MainWindow::MoveToolTriggered()
	{
		SetGuiSubMode(GuiSubMode::Move);
	}

	///
	/// \brief Slot for when the pick tool button is triggered.
	///
	void MainWindow::PickToolTriggered()
	{
		SetGuiSubMode(GuiSubMode::Pick);
	}

	///
	/// \brief Slot for when the Place tool button is triggered.
	///
	void MainWindow::PlaceToolTriggered()
	{
		SetGuiSubMode(GuiSubMode::Place);
	}

	///
	/// \brief Slot for when the Dispense Dot tool button is triggered.
	///
	void MainWindow::DispenseDotToolTriggered()
	{
		SetGuiSubMode(GuiSubMode::DispenseDot);
	}

	///
	/// \brief Slot for when the Dispense Polygon tool button is triggered.
	///
	void MainWindow::DispensePolygonToolTriggered()
	{
		SetGuiSubMode(GuiSubMode::DispensePolygon);
	}

	///
	/// \brief Slot for when the clear pick and place points button has been clicked.
	///
	void MainWindow::ClearPickPlaceButtonPressed()
	{
		if (this->m_subguimode == Pick)
		{
			this->m_ui.m_pMainCameraWidget->resetMode(CameraWidget::InteractionMode::Pick);
		}

		if (this->m_subguimode == Place)
		{
			this->m_ui.m_pMainCameraWidget->resetMode(CameraWidget::InteractionMode::Place);
		}
	}

	///
	/// \brief Slot for when the clear polygon button has been clicked.
	///
	void MainWindow::ClearPolygonButtonPressed()
	{
		this->m_ui.m_pMainCameraWidget->resetMode(CameraWidget::InteractionMode::DispensePolygon);
	}

	///
	/// \brief Slot for when the remove dot button has been clicked.
	///
	void MainWindow::RemoveDotButtonPressed()
	{
		this->m_ui.m_pMainCameraWidget->resetMode(CameraWidget::InteractionMode::DispenseDot);
	}

	///
	/// \brief Slot for when the dispense dot spin box changes value.
	///
	void MainWindow::DispenseDotSpinBoxValueChanged(int value)
	{
		this->m_ui.m_pMainCameraWidget->setDispenseDotRadius(value);
	}

	///
	/// \brief Slot for when the enqueue command button has been clicked.
	///
	void MainWindow::EnqueueCommandButtonPressed()
	{
		CameraWidget *cw = this->m_ui.m_pMainCameraWidget;
		CameraWidget::InteractionMode cmode = cw->getMode();

		if (cmode == CameraWidget::InteractionMode::DispensePolygon)
		{
			DispencePolygonCommand *dpc = new DispencePolygonCommand(*cw->getDispensePolygon());
			if (dpc)
			{
				this->m_commands.append(dpc);
			}
		}
		else if (cmode == CameraWidget::InteractionMode::DispenseDot)
		{
			QPoint p = cw->getDotDispensePoint();
			DispenceStateStruct dss = DispenceStateStruct();

			DispenceDotCommand *ddp = new DispenceDotCommand(p.x(), p.y(), dss);

			if (ddp)
			{
				this->m_commands.append(ddp);
			}
		}
		else if ((cmode == CameraWidget::InteractionMode::Pick) || (cmode == CameraWidget::InteractionMode::Place))
		{
			QPoint *pickSrc = cw->getPickPoints();
			QPoint *placeSrc = cw->getPlacePoints();
			Coordinate2D pickPoints[3];
			Coordinate2D placePoints[3];
			
			for (int i = 0; i < 3; i++)
			{
				pickPoints[i].x = pickSrc[i].x();
				pickPoints[i].y = pickSrc[i].y();

				placePoints[i].x = placeSrc[i].x();
				placePoints[i].y = placeSrc[i].y();
			}

			PickStateStruct pss = PickStateStruct();

			PickAndPlaceCommand *ppc = new PickAndPlaceCommand(pickPoints[0], pickPoints[1], pickPoints[2], 
															placePoints[0], placePoints[1], placePoints[2], pss);

			if (ppc)
			{
				this->m_commands.append(ppc);
			}

			cw->resetMode(CameraWidget::InteractionMode::Pick);
			cw->resetMode(CameraWidget::InteractionMode::Place);
		}

		// Don't let the user mistakingly enqueue the same command twice by removing the command from the camera widget.
		cw->resetCurrentMode();

		this->RefreshCommandList();
	}

	///
	/// \brief Refreshes the contents of the command list.
	///
	void MainWindow::RefreshCommandList()
	{
		QListWidget *clw = this->m_ui.m_pCommandsListWidget;

		this->m_ui.m_pCommandsListWidget->clear();

		for (int i = 0; i < this->m_commands.size(); i++)
		{
			QString str = QString("%1 - %2").arg(i + 1).arg(this->m_commands.at(i)->toString());
			clw->addItem(str);
		}

		this->m_ui.m_pRunCommandsButton->setEnabled(this->m_commands.size() > 0);
	}

	///
	/// \brief Slot for when the run commands button has been clicked.
	///
	void MainWindow::RunCommandsButtonPressed()
	{
		this->RunCommands();
	}

	///
	/// \brief Slot for when the remove command button has been clicked.
	///
	void MainWindow::RemoveCommandButtonPressed()
	{
		QListWidget *clw = this->m_ui.m_pCommandsListWidget;

		QModelIndex index = clw->currentIndex();
		int i = index.row();

		this->m_commands.removeAt(i);

		this->RefreshCommandList();
	}

	///
	/// \brief Slot for when the camera widget wants the machine to move.
	///
	void MainWindow::CameraWidgetNewMachineCoordinates(int newMachineX, int newMachineY)
	{
		// Move the machine!
		int z = this->m_pMC->GetCurrentState().GetState().z;
		MachineMoveAllCommand move = MachineMoveAllCommand(newMachineX, newMachineY, z);
		this->m_pMC->RunCommand(move);
	}

	///
	/// \brief Slot for when the camera widget has enough information to create a new command.
	///
	void MainWindow::CameraWidgetCommandReady(CameraWidget::InteractionMode mode, PicknPlaceGui::DispencePolygonCommand *polygon)
	{
		this->m_ui.m_pEnqueueCommandButton->setEnabled(true);
	}

	///
	/// \brief Slot for when the camera widget has enough information to create a new command.
	///
	void MainWindow::CameraWidgetCommandReady(CameraWidget::InteractionMode mode, QPoint *pickPoints, QPoint *placePoints)
	{
		this->m_ui.m_pEnqueueCommandButton->setEnabled(true);
	}

	///
	/// \brief Slot for when the camera widget has enough information to create a new command.
	///
	void MainWindow::CameraWidgetCommandReady(CameraWidget::InteractionMode mode, QPoint dot)
	{
		this->m_ui.m_pRemoveDotButton->setEnabled(true);
		this->m_ui.m_pEnqueueCommandButton->setEnabled(true);
	}

	///
	/// \brief Slot for when the camera widget doesn't have enough information to create a new command anymore.
	///
	void MainWindow::CameraWidgetCommandInvalid()
	{
		this->m_ui.m_pRemoveDotButton->setEnabled(false);
		this->m_ui.m_pEnqueueCommandButton->setEnabled(false);
	}

	///
	/// \brief Slot for when the selected command in the command list widget has changed.
	///
	void MainWindow::CommandSelectionChanged()
	{
		QListWidget *clw = this->m_ui.m_pCommandsListWidget;		
		this->m_ui.m_pRemoveCommandButton->setEnabled(clw->selectedItems().count() > 0);

		// Set the highlight index for the camera widget.
		QModelIndex index = clw->currentIndex();
		int i = index.row();
		this->m_ui.m_pMainCameraWidget->setHighlightedCommandIndex(i);
	}

	///
	/// \brief Slot for when the remove last point button has been clicked.
	///
	void MainWindow::RemoveLastPointButtonPressed()
	{
		CameraWidget *cw = this->m_ui.m_pMainCameraWidget;
		DispencePolygonCommand *dpc = cw->getDispensePolygon();

		if (dpc && (dpc->Size() > 0))
		{
			dpc->DelPoint(dpc->Size() - 1);
			
			// Make sure we remove the polygon if there are no points left.
			if (dpc->Size() == 0)
			{
				cw->resetCurrentMode();
			}

			cw->update();
		}	
	}
}






