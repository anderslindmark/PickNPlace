
// GUI.
#include "MainWindow.h"

// Qt.
#include <QString>

namespace PicknPlaceGui
{
	MainWindow::MainWindow()
	{
		// Runs the generated code that setups the initial UI.
		this->m_ui.setupUi(this);
		
		// Connect the currently selected list item to what arguments are shown.
		connect(
			m_ui.m_pCommandsListWidget, 
			SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), 
			this, 
			SLOT(setArgumentWidget(QListWidgetItem *, QListWidgetItem *)));

		// Make sure something is selected in the command list.
		this->m_ui.m_pCommandsListWidget->setCurrentRow(0);

		this->m_pMC = new MachineController("com1");
	}

	MainWindow::~MainWindow()
	{
		delete this->m_pMC;
	}

	///
	/// \brief	Slot for when the selected item in the command listwidget changes.
	///			Changes the current argument controls to show based on the selected command.
	///
	/// \param	newCommandItem	The new command item selected from the command list widget.
	/// \param	oldItem			The previous command item that was selected.
	///
	void MainWindow::setArgumentWidget(QListWidgetItem *newCommandItem, QListWidgetItem *oldItem)
	{
		QString txt = newCommandItem->text();

		// Check for which command we should enable the execute button for.
		if ((txt == "Initialize")) // TODO: Add check from MachineAPI here if the machine is initialized or not.
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
			}
			else
			{
				m_ui.m_pDescriptionLabel->setText("Place the picker at an absolute position.");
			}
		}

		
	}
}

