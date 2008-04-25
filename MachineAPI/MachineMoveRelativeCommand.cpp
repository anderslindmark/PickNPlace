#include "MachineMoveRelativeCommand.h"

#define COMMAND_STRING "Machine move relative command"

MachineMoveRelativeCommand::MachineMoveRelativeCommand(Axis axis, int distance)
{
	m_axis = axis;
	m_dist = distance;
	m_stateKnown = false;
}

MachineMoveRelativeCommand::~MachineMoveRelativeCommand(void)
{
}

string MachineMoveRelativeCommand::ToString()
{
	return string(COMMAND_STRING);
}

MachineState MachineMoveRelativeCommand::GetAfterState(MachineState &oldms)
{
	MachineStateStruct mss = oldms.GetState();

	m_newX = mss.x;
	m_newY = mss.y;
	m_newZ = mss.z;

	switch (m_axis)
	{
		default:
		case AXIS_X:
			m_newX += m_dist;
			break;
		case AXIS_Y:
			m_newY += m_dist;
			break;
		case AXIS_Z:
			m_newZ += m_dist;
			break;
	}
	
	m_stateKnown = true;
	mss.x = m_newX;
	mss.y = m_newY;
	mss.z = m_newZ;
	return MachineState(mss);
}


bool MachineMoveRelativeCommand::DoCommand(SerialPort &sp)
{
	int pos;
	if (!m_stateKnown)
	{
		throw MachineEvent(EVENT_CMD_FAILED, "Move relative failed because the current position of the machine is unknown");
		return false;
	}

	switch (m_axis)
	{
		default:
		case AXIS_X:
			pos = m_newX;
			break;
		case AXIS_Y:
			pos = m_newY;
			break;
		case AXIS_Z:
			pos = m_newZ;
			break;
	}

	MachineMoveAbsoluteCommand(m_axis, pos).DoCommand(sp);
	return true;
}

MachineMoveRelativeCommand* MachineMoveRelativeCommand::Copy()
{
	return new MachineMoveRelativeCommand(m_axis, m_dist);
}
