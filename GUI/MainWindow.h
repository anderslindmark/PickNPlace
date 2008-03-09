
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

namespace PicknPlaceGui
{
	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		MainWindow();
		~MainWindow();

		void OnMachineEvent(MachineEvent *e);

	private slots:
		void SetArgumentWidget(QListWidgetItem *newCommandItem, QListWidgetItem *oldItem);
		void CheckIfExecutable(int notused);
		void ExecuteCommand(void);

	private:
		void ConnectSlots();

		Ui::MainWindow m_ui;					///< Generated User Interface.
		MachineController *m_pMC;				///< Machine controler.
		camera::CameraManager m_cameraManager;	///< Camera Manager.
		std::vector<camera::Camera *> m_cams;	///< A list of cameras.
	};
}

#endif // __MAINWINDOW_H__
