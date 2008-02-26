
#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QtGui>

// Generated.
#include "ui_MainWindow.h"

// MachineAPI.
#include "MachineController.h"

namespace PicknPlaceGui
{
	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		MainWindow();
		~MainWindow();

	public slots:
		void setArgumentWidget(QListWidgetItem *newCommandItem, QListWidgetItem *oldItem);

	private:
		Ui::MainWindow m_ui;		///< Generated User Interface.
		MachineController *m_pMC;	///< Machine controler.
	};
}

#endif // __MAINWINDOW_H__
