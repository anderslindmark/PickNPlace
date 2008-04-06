#include "MachineDotDispenceCommand.h"
#include "MachineMoveRelativeCommand.h"

#define COMMAND_STRING "Machine Dot Dispence Command"

MachineDotDispenceCommand::MachineDotDispenceCommand(void)
{
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
	m_state = oldms.GetState();
	return oldms;
}

MachineDotDispenceCommand *MachineDotDispenceCommand::Copy()
{
	return new MachineDotDispenceCommand();
}

bool MachineDotDispenceCommand::DoCommand(SerialPort &sp)
{
	MachineMoveRelativeCommand(AXIS_X, m_state.dispenceState.offsetX);
	MachineMoveRelativeCommand(AXIS_Y, m_state.dispenceState.offsetY);
	MachineMoveRelativeCommand(AXIS_Z, m_state.dispenceState.offsetZ);
	return true;
}