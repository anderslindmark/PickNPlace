
#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QtGui>

#include "ui_MainWindow.h"

namespace PicknPlaceGui
{
	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		MainWindow();

	public slots:
		void setArgumentWidget(QListWidgetItem *newCommandItem, QListWidgetItem *oldItem);

	private:
		Ui::MainWindow m_ui;
	};
}

#endif // __MAINWINDOW_H__
