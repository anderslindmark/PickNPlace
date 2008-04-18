#include "MachineSetPickTimeCommand.h"
#include "MachineCommands.h"
#include "Axis.h"

#include <iostream>
using namespace std;

#define COMMAND_STRING	"Machine Pick Time Command"

MachineSetPickTimeCommand::MachineSetPickTimeCommand(PickTimeType type, int time)
{
	m_type = type;
	m_time = time;
}

MachineSetPickTimeCommand::~MachineSetPickTimeCommand(void)
{
}

string MachineSetPickTimeCommand::ToString()
{
	return string(COMMAND_STRING);
}

MachineState MachineSetPickTimeCommand::GetAfterState(MachineState &oldms)
{
	MachineStateStruct mss = oldms.GetState();
	switch (m_type)
	{
	case (PICKTIME_AFTER_PICK):
		mss.pickAndPlaceState.afterPickTime = m_time;
		break;

	case (PICKTIME_AFTER_PLACE):
		mss.pickAndPlaceState.afterPlaceTime = m_time;
		break;

	case (PICKTIME_PRESS_PICK):
		mss.pickAndPlaceState.pickPressDownTime = m_time;
		break;

	case (PICKTIME_PRESS_PLACE):
		mss.pickAndPlaceState.placePressDownTime = m_time;
		break;
	}

	return MachineState(mss);
}

bool MachineSetPickTimeCommand::HasNextState()
{
	return false;
}


bool MachineSetPickTimeCommand::DoCommand(SerialPort &sp)
{
	char cmd[15];
	switch (m_type)
	{
	case (PICKTIME_AFTER_PICK):
		sprintf_s(cmd, sizeof(cmd),"WS T111 %d", m_time);
		break;

	case (PICKTIME_AFTER_PLACE):
		sprintf_s(cmd, sizeof(cmd),"WS T114 %d", m_time);
		break;

	case (PICKTIME_PRESS_PICK):
		sprintf_s(cmd, sizeof(cmd),"WS T112 %d", m_time);
		break;

	case (PICKTIME_PRESS_PLACE):
		sprintf_s(cmd, sizeof(cmd),"WS T113 %d", m_time);
		break;
	}
	ExecCommand(sp, cmd, M_ANS_OK);
	return true;
}

MachineSetPickTimeCommand* MachineSetPickTimeCommand::Copy()
{
	return new MachineSetPickTimeCommand(m_type, m_time);
}