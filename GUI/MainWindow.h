
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
	///
	/// \enum GuiMode
	/// \brief The different modes the GUI can be in.
	///
	enum GuiMode
	{
		PickNPlaceMode,	///< Pick and place mode.
		DispenceMode	///< Dispence mode.
	};

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

	private:
		void ConnectSlots();
		void InitCameraManager();
		void InitMachineController();
		void CreateToolbarButtons();
		void ToggleInteractionTools();
		void ShowInformation(QString message, QMessageBox::Icon icon);

		Ui::MainWindow m_ui;					    ///< Generated User Interface.
		MachineController *m_pMC;				    ///< Machine controler.

		GuiMode m_guimode;							///< The current GUI mode, PnP or Dispense.

		QList<GuiMachineCommand> m_commands;		///< The list of machine commands that are to be run.

		// Modes toolbar actions.
		QActionGroup *m_pModesActionGroup;			///< The Action Group for the different GUI modes, making only one selectable at a time.
		QAction *m_pPickNPlaceToolAction;			///< Toolbar button for activating Pick and Place mode.
		QAction *m_pDispenceToolAction;				///< Toolbar button for activating Dispence mode.

		// Tools toolbar actions.
		QAction *m_pZoomToolAction;					///< Toolbar button for toggling the zoom camera on the camera widget.
		QAction *m_pShowPolygonToolAction;			///< Toolbar button for toggling polygon drawing on the camera widget.

		QActionGroup *m_pInteractionActionGroup;	///< Action Group for the different interactions that can be done with the camera widget.
		QAction *m_pMoveToolAction;					///< Toolbar button for moving around the work area by clicking on the camera widget.
		
		QAction *m_pPickToolAction;					///< Toolbar button for chosing where to pick a component.
		QAction *m_pPlaceToolAction;				///< Toolbar button for chosing where to place a component.

		QAction *m_pDispensePolygonToolAction;		///< Toolbar button for drawing a dispense polygon.
		QAction *m_pDispenseDotToolAction;			///< Toolbar button for dispensing a dot.
	};
}

#endif // __MAINWINDOW_H__
