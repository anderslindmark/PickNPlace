

#include "MainWindow.h"	// GUI.
#include <QString>		// Qt.

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
	
		this->ConnectSlots();

		// Make sure something is selected in the command list.
		//this->m_ui.m_pCommandsListWidget->setCurrentRow(0);
		
		this->InitCameraManager();
		this->CreateToolbarButtons();
	}

	void MainWindow::InitCameraManager()
	{
		/*
		// Create the machine controller and associate a callback function with it.
		this->m_pMC = new MachineController("com1"); // TODO: Let the user choose com port.
		this->m_pMC->AddEventHandler(&on_machine_event);
		
		
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

	void MainWindow::CreateToolbarButtons()
	{
		//
		// Mode toolbar.
		//
		this->m_pPickNPlaceTool = new QAction(QIcon("images/pnp_icon.png"), tr("&Pick and Place"), this);
		this->m_pPickNPlaceTool->setCheckable(true);
		this->m_pPickNPlaceTool->setShortcut(tr("Ctrl+P"));
		this->m_pPickNPlaceTool->setStatusTip(tr("Enter Pick and Place mode"));
		// TODO : Connect action to a slot.

		this->m_pDispenceTool = new QAction(QIcon("images/dispence_icon.png"), tr("&Dispence"), this);
		this->m_pDispenceTool->setCheckable(true);
		this->m_pDispenceTool->setShortcut(tr("Ctrl+D"));
		this->m_pDispenceTool->setStatusTip(tr("Enter Dispence mode"));
		// TODO : Connect action to a slot.

		this->m_ui.m_pModeToolBar->addAction(this->m_pPickNPlaceTool);
		this->m_ui.m_pModeToolBar->addAction(this->m_pDispenceTool);

		//
		// Tools toolbar.
		//
		this->m_pZoomTool = new QAction(QIcon("images/zoom_icon.png"), tr("&Zoom"), this);
		this->m_pZoomTool->setCheckable(true);
		this->m_pZoomTool->setShortcut(tr("Ctrl+Z"));
		this->m_pZoomTool->setStatusTip(tr("Show the zoomed in camera view for fine positioning"));
		// TODO : Connect action to a slot.

		this->m_pShowPolygonTool = new QAction(QIcon("images/showpoly_icon.png"), tr("&Show polygons"), this);
		this->m_pShowPolygonTool->setCheckable(true);
		this->m_pShowPolygonTool->setShortcut(tr("Ctrl+S"));
		this->m_pShowPolygonTool->setStatusTip(tr("Shows polygons on the camera image"));
		// TODO : Connect action to a slot.

		this->m_ui.m_pToolsToolBar->addAction(this->m_pZoomTool);
		this->m_ui.m_pToolsToolBar->addAction(this->m_pShowPolygonTool);
	}

	///
	/// \brief Connects all slots for the GUI.
	///
	void MainWindow::ConnectSlots()
	{
		/*
		// Connect the currently selected list item to what arguments are shown.
		QMainWindow::connect(
				this->m_ui.m_pCommandsListWidget, 
				SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), 
				this, 
				SLOT(SetArgumentWidget(QListWidgetItem *, QListWidgetItem *)));

		// Angle spin box changed.
		QMainWindow::connect(
				this->m_ui.m_pAngleSpinBox,
				SIGNAL(valueChanged(int)),
				this,
				SLOT(CheckIfExecutable(int)));

		// Position spin box changed.
		QMainWindow::connect(
				this->m_ui.m_pPositionSpinBox,
				SIGNAL(valueChanged(int)),
				this,
				SLOT(CheckIfExecutable(int)));

		QMainWindow::connect(
				this->m_ui.m_pExecuteButton,
				SIGNAL(clicked()),
				this,
				SLOT(ExecuteCommand()));
		*/
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

	/*
	///
	/// \brief	Slot for when the selected item in the command listwidget changes.
	///			Changes the current argument controls to show based on the selected command.
	///
	/// \param	newCommandItem	The new command item selected from the command list widget.
	/// \param	oldItem			The previous command item that was selected.
	///
	void MainWindow::SetArgumentWidget(QListWidgetItem *newCommandItem, QListWidgetItem *oldItem)
	{
		QString txt = newCommandItem->text();

		// Check for which command we should enable the execute button.
		if (!this->m_pMC->IsBusy() && ((txt == "Initialize") || this->m_pMC->IsInitialized()))
		{
			m_ui.m_pExecuteButton->setEnabled(true);
		}
		else
		{
			m_ui.m_pExecuteButton->setEnabled(false);
		}

		// Find out which item in the list is selected and activate the associated
		// argument controls and set the description for the command.
		if ((txt == "Initialize") || (txt == "Park"))
		{
			m_ui.m_pArgumentsStackedWidget->setCurrentWidget(m_ui.m_pNoArgsPage);
			
			if (txt == "Initialize")
			{
				m_ui.m_pDescriptionLabel->setText("Initializes the Pick n Place machine and makes sure the picker is in the correct starting position.");
			}
			else
			{
				m_ui.m_pDescriptionLabel->setText("Parks the picker head.");
			}
		}
		else if (txt.startsWith("Rotate"))
		{
			m_ui.m_pArgumentsStackedWidget->setCurrentWidget(m_ui.m_pAnglePage);

			if (txt.endsWith("relative", Qt::CaseInsensitive))
			{
				m_ui.m_pDescriptionLabel->setText("Rotate the picker relative to its current state.");
			}
			else
			{
				m_ui.m_pDescriptionLabel->setText("Rotate the picker to an absolute angle.");
			}
		}
		else if (txt.startsWith("Position"))
		{
			m_ui.m_pArgumentsStackedWidget->setCurrentWidget(m_ui.m_pPositionPage);

			if (txt.endsWith("relative", Qt::CaseInsensitive))
			{
				m_ui.m_pDescriptionLabel->setText("Position the picker relative to its current state.");
				m_ui.m_pPositionSpinBox->setMinimum(-400000);
			}
			else
			{
				m_ui.m_pDescriptionLabel->setText("Place the picker at an absolute position.");
				m_ui.m_pPositionSpinBox->setMinimum(0);
			}
		}
	}

	///
	/// \brief Decides if the execute button should be enabled or not based on the current command and arguments.
	///
	void MainWindow::CheckIfExecutable(int notused)
	{
		QListWidgetItem *currentItem = this->m_ui.m_pCommandsListWidget->currentItem();
		QString txt = currentItem->text();
		bool executable = false;

		if (txt.startsWith("Rotate"))
		{
			// Only enable the execute button if an angle has been specified.
			executable = (this->m_ui.m_pAngleSpinBox->value() > 0);
		}
		else if (txt.startsWith("Position"))
		{
			executable = (this->m_ui.m_pPositionSpinBox->value() > 0);
		}

		// Only enable the execute button if the machine controller is initialized.
		executable = executable && this->m_pMC->IsInitialized() && !this->m_pMC->IsBusy();

		this->m_ui.m_pExecuteButton->setEnabled(executable);
	}

	///
	/// \brief Slot that connects to the signal for clicking the Execute command button.
	///
	void MainWindow::ExecuteCommand(void)
	{
		QListWidgetItem *currentItem = this->m_ui.m_pCommandsListWidget->currentItem();
		QString txt = currentItem->text();

		if (txt == "Initialize")
		{
			this->m_pMC->InitializeMachine();
		}
		else if (txt == "Park")
		{
			// TODO: Run park command.
		}
		else if (txt.startsWith("Position"))

		{
			Axis axis = AXIS_X;

			if (this->m_ui.m_pAxisComboBox->currentText() == "X")
			{
				axis = AXIS_X;
			}
			else if (this->m_ui.m_pAxisComboBox->currentText() == "Y")
			{
				axis = AXIS_Y;
			}
			else if (this->m_ui.m_pAxisComboBox->currentText() == "Z")
			{
				axis = AXIS_Z;
			}

			if (txt.endsWith("absolute"))
			{
				MachineMoveAbsoluteCommand mc(axis, this->m_ui.m_pPositionSpinBox->value());
				this->m_pMC->RunCommand(mc);
			}
			else
			{
				// TODO: Run relative position command.
			}
		}
		else if (txt == "Rotate absolute")
		{
			int degrees = this->m_ui.m_pAngleSpinBox->value() * (this->m_ui.m_pLeftRotateRadioButton->isChecked() ? -1 : 1);
			float radians = (float)(degrees * (M_PI / 180.0f));

			MachineRotateAbsoluteCommand mc(radians);
			this->m_pMC->RunCommand(mc);
		}
	}
	*/

	///
	/// \brief Callback function for any MachineController events.
	///
	void MainWindow::OnMachineEvent(MachineEvent *e)
	{
		MachineEventType type = e->GetEventType();
		/*
		if ((type == EVENT_CMD_DONE) || (type == EVENT_MACHINE_INITIALIZED))
		{
			this->m_ui.m_pExecuteButton->setEnabled(true);
		}
		
		// TODO: Handle all event types and show error dialogs and such.
		*/
		delete e;
	}
}






