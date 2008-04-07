#include "MachineDotDispenceCommand.h"
#include "MachineCommands.h"

#define COMMAND_STRING "Machine Dot Dispence Command"

MachineDotDispenceCommand::MachineDotDispenceCommand(void)
{
	m_moreStates = true;
}

MachineDotDispenceCommand::~MachineDotDispenceCommand(void)
{
}

string MachineDotDispenceCommand::ToString()
{
	return string(COMMAND_STRING);
}

MachineState MachineDotDispenceCommand::GetAfterState(MachineState &oldms)
{
	MachineStateStruct newState = oldms.GetState();
	if (m_moreStates)
	{
		newState.x =  m_state.x+m_state.dispenceState.offsetX;
		newState.y =  m_state.y+m_state.dispenceState.offsetY;
		newState.z =  m_state.z+m_state.dispenceState.offsetZ;
		m_state = oldms.GetState();
	}
	else
	{
		newState = m_state;
	}

	return MachineState(newState);
}

bool MachineDotDispenceCommand::HasNextState()
{
	if (m_moreStates)
	{
		m_moreStates = false;
		return true;
	}
	return false;
}

MachineDotDispenceCommand *MachineDotDispenceCommand::Copy()
{
	return new MachineDotDispenceCommand();
}

bool MachineDotDispenceCommand::DoCommand(SerialPort &sp)
{
	// Move solder tool above the spot:
	MachineMoveAllCommand(m_state.x+m_state.dispenceState.offsetX, m_state.y+m_state.dispenceState.offsetY, -1).DoCommand(sp);
	MachineMoveAbsoluteCommand(AXIS_Z, m_state.dispenceState.offsetZ).DoCommand(sp);
	
	
	//SOLDER:
	ExecCommand(sp, "ST 1613",	M_ANS_OK); // Set dot dispence mode
	MachineMoveNeedleCommand(NEEDLEMOVEMENT_DOWN).DoCommand(sp);
	ExecCommand(sp, "ST 1908",	M_ANS_OK);	// Execute dispence
	ExecCommand(sp, M_READY_1915,	M_ANS_1);

	// Go back to starting point:
	MachineMoveNeedleCommand(NEEDLEMOVEMENT_UP).DoCommand(sp);
	MachineMoveAbsoluteCommand(AXIS_Z, m_state.z).DoCommand(sp);
	MachineMoveAllCommand(m_state.x, m_state.y, -1).DoCommand(sp);
	
	return true;
}