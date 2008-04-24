#include "MachineSetPickOffsetCommand.h"
#include <iostream>

#define COMMAND_STRING "Machine Set Pick Offset Command"

MachineSetPickOffsetCommand::MachineSetPickOffsetCommand(PickOffset pickOffset, int offset)
{
	m_offset = offset;
	m_pickOffset = pickOffset;
}

MachineSetPickOffsetCommand::~MachineSetPickOffsetCommand(void)
{
}

string MachineSetPickOffsetCommand::ToString()
{
	return string(COMMAND_STRING);
}

MachineState MachineSetPickOffsetCommand::GetAfterState(MachineState &oldms)
{
	MachineStateStruct mss = oldms.GetState();
	
	switch (m_pickOffset)
	{
		case (PICKOFFSET_X):
			mss.pickState.offsetX = m_offset;
			break;
		case (PICKOFFSET_Y):
			mss.pickState.offsetY = m_offset;
			break;
		case (PICKOFFSET_TOOLHEIGHT):
			mss.pickState.headHeight = m_offset;
			break;
		case (PICKOFFSET_PICKHEIGHT):
			mss.pickState.pickHeight = m_offset;
			break;
		case (PICKOFFSET_PLACEHEIGHT):
			mss.pickState.placeHeight = m_offset;
			break;
	}

	return MachineState(mss);
}


bool MachineSetPickOffsetCommand::DoCommand(SerialPort &sp)
{
	return true;
}

MachineSetPickOffsetCommand* MachineSetPickOffsetCommand::Copy()
{
	return new MachineSetPickOffsetCommand(m_pickOffset, m_offset);
}