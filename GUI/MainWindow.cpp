
#include "MainWindow.h"
#include <QString>

namespace PicknPlaceGui
{
	MainWindow::MainWindow()
	{
		m_ui.setupUi(this);
		
		// Connect the currently selected list item to what arguments are shown.
		connect(
			m_ui.m_pCommandsListWidget, 
			SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), 
			this, 
			SLOT(setArgumentWidget(QListWidgetItem *, QListWidgetItem *)));

		// Make sure something is selected in the command list.
		m_ui.m_pCommandsListWidget->setCurrentRow(0);

	}

	void MainWindow::setArgumentWidget(QListWidgetItem *newCommandItem, QListWidgetItem *oldItem)
	{
		if ((newCommandItem->text() == "Initialize") || (newCommandItem->text() == "Park"))
		{
			m_ui.m_pArgumentsStackedWidget->setCurrentWidget(m_ui.m_pNoArgsPage);
		}
		else if (newCommandItem->text().startsWith("Rotate"))
		{
			m_ui.m_pArgumentsStackedWidget->setCurrentWidget(m_ui.m_pAnglePage);
		}
		else if (newCommandItem->text().startsWith("Position"))
		{
			m_ui.m_pArgumentsStackedWidget->setCurrentWidget(m_ui.m_pPositionPage);
		}
	}
}
