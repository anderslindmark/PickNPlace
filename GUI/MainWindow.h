
#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QtGui>

#include "ui_MainWindow.h"		// Generated.
#include "MachineController.h"	// MachineAPI.
#include "CameraManager.h"
#include "DummyDriver.h"
#include "EuresysDriver.h"
#include "Camera.h"
#include "CameraListener.h"
#include "CameraException.h"
#include "GuiMachineCommand.h"

namespace PicknPlaceGui
{
	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	protected:
		void closeEvent(QCloseEvent *event);

	public:
		MainWindow();
		~MainWindow();

		void OnMachineEvent(MachineEvent *e);

	private slots:

		// Modes toolbar action triggers.
		void PickNPlaceActionTriggered();
		void DispenceActionTriggered();

		// Tools toolbar action triggers.
		void ShowPolygonActionTriggered();
		void ZoomActionTriggered();

		void BrightnessSliderChanged(int value);
		void ZLockButtonToggled(bool toggled);

		void XValueChanged(int value);
		void YValueChanged(int value);
		void ZValueChanged(int value);
		
		void CommandListItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

		void CloseInformationBar();
		void AbortButtonPressed();

		void MoveToolTriggered();
		void PickToolTriggered();
		void PlaceToolTriggered();
		void DispenseDotToolTriggered();
		void DispensePolygonToolTriggered();

		void ClearPickPlaceButtonPressed();
		void ClearPolygonButtonPressed();
		void RemoveDotButtonPressed();
		void DispenseDotSpinBoxValueChanged(int value);

		void EnqueueCommandButtonPressed();

		void RunCommandsButtonPressed();
		void RemoveCommandButtonPressedPressed();

	private:

		///
		/// \enum GuiMode
		/// \brief The different modes the GUI can be in.
		///
		enum GuiMode
		{
			PickNPlaceMode,							///< Pick and place mode.
			DispenceMode							///< Dispence mode.
		};

		GuiMode m_guimode;							///< The current GUI mode, PnP or Dispense.

		///
		/// \brief The different sub modes the GUI can be in.
		///
		enum GuiSubMode
		{
			Move,
			Pick,
			Place,
			DispenseDot,
			DispensePolygon
		};

		void ConnectSlots();
		void InitCameraManager();
		void InitMachineController();
		void CreateToolbarActionGroups();
		void ToggleInteractionTools();
		void ShowInformation(QString message, QMessageBox::Icon icon);
		void SetGuiSubMode(MainWindow::GuiSubMode mode);
		void UpdateGuiBasedOnGuiSubMode();

		Ui::MainWindow m_ui;					    ///< Generated User Interface.
		MachineController *m_pMC;				    ///< Machine controler.

		GuiSubMode m_subguimode;					///< The current sub GUI mode.

		QList<GuiMachineCommand> m_commands;		///< The list of machine commands that are to be run.

		QActionGroup *m_pModesActionGroup;			///< The Action Group for the different GUI modes, making only one selectable at a time.
		QActionGroup *m_pInteractionActionGroup;	///< Action Group for the different interactions that can be done with the camera widget.
	};
}

#endif // __MAINWINDOW_H__
