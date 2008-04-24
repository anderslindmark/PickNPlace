#include "MachineWrapperCommand.h"
#include "MachineCommands.h"

#define COMMAND_STRING	"Machine Wrapper Command"

MachineWrapperCommand::MachineWrapperCommand()
{
	m_current = 0;
}

MachineWrapperCommand::~MachineWrapperCommand(void)
{
	for (unsigned int i = 0; i < m_commands.size(); i++)
	{
		delete m_commands[i];
	}
}

string MachineWrapperCommand::ToString()
{
	return COMMAND_STRING;
}

MachineState MachineWrapperCommand::GetAfterState(MachineState &oldms)
{
	if (m_current == 0)
	{
		m_state = oldms.GetState();
	}
	if (m_commands.size() == 0)
	{
		return MachineState(oldms);
	}
	return m_commands[m_current]->GetAfterState(oldms);
}

bool MachineWrapperCommand::HasNextState()
{
	if (m_current == m_commands.size()-1)
	{
		return false;
	}

	m_current++;
	return true;
}

bool MachineWrapperCommand::IsValid()
{
	for (unsigned int i = 0; i < m_commands.size() ; i++)
	{
		if (!m_commands[i]->IsValid())
		{
			return false;
		}
	}
	return true;
}


bool MachineWrapperCommand::DoCommand(SerialPort &sp)
{
	for (unsigned int i = 0; i < m_commands.size(); i++)
	{
		m_commands[i]->DoCommand(sp);
	}
	MachineMoveAllCommand(m_state.x, m_state.y, m_state.z).DoCommand(sp);
	
	return true;
}

MachineWrapperCommand* MachineWrapperCommand::Copy()
{
	MachineWrapperCommand *newWC = new MachineWrapperCommand();
	for (unsigned int i = 0; i < m_commands.size(); i++)
	{
		newWC->Add(*(m_commands[i]->Copy()));
	}
	return newWC;
}

void MachineWrapperCommand::Add(MachineCommand &cmd)
{
	m_commands.push_back(cmd.Copy());
}
