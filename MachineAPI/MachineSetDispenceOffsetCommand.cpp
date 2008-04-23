#include "MachineSetDispenceOffsetCommand.h"
#include <iostream>

#define COMMAND_STRING "Machine Set Dispence Offset Command"

MachineSetDispenceOffsetCommand::MachineSetDispenceOffsetCommand(OffsetAxis axis, int offset)
{
	m_axis = axis;
	m_offset = offset;
}

MachineSetDispenceOffsetCommand::~MachineSetDispenceOffsetCommand(void)
{
}

string MachineSetDispenceOffsetCommand::ToString()
{
	return string(COMMAND_STRING);
}

MachineState MachineSetDispenceOffsetCommand::GetAfterState(MachineState &oldms)
{
	MachineStateStruct mss = oldms.GetState();
	switch (m_axis)
	{
		case (OFFSET_X):
			mss.dispenceState.offsetX = m_offset;
			break;
		case (OFFSET_Y):
			mss.dispenceState.offsetY = m_offset;
			break;
		case (OFFSET_Z):
			mss.dispenceState.offsetZ = m_offset;
			break;
		case (OFFSET_ZS):
			mss.dispenceState.offsetZs = m_offset;
			break;
		case (OFFSET_TURN):
			mss.dispenceState.offsetTurn = m_offset;
			break;
	}
	
	return MachineState(mss);
}


bool MachineSetDispenceOffsetCommand::DoCommand(SerialPort &sp)
{
	char cmdStr[15];
	switch (m_axis)
	{
		case (OFFSET_Z):
			ExecCommand(sp, "WR DM320 36096", M_ANS_OK); // Large offset
			break;
		case (OFFSET_ZS):
			ExecCommand(sp, "WR DM320 36352", M_ANS_OK); // After "Before time" offset
			break;
		default:
			return true;
	}
	int length = floor(m_offset/STEP_PRECISION_Z + 0.5);
	sprintf_s(cmdStr, sizeof(cmdStr), "WR DM321 %d", length); // Set offset
	cout << "Setting Z-offset: " << cmdStr << endl;
	ExecCommand(sp, cmdStr, M_ANS_OK);
	ExecCommand(sp, "WR DM71 2", M_ANS_OK);
	ExecCommand(sp, "WR DM70 320", M_ANS_OK);
	ExecCommand(sp, M_READY_1515, M_ANS_1);
	return true;
}

MachineSetDispenceOffsetCommand* MachineSetDispenceOffsetCommand::Copy()
{
	return new MachineSetDispenceOffsetCommand(m_axis, m_offset);
}