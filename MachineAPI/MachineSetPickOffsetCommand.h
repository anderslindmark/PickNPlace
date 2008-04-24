#ifndef __MachineSetPickOffsetCommand_H__
#define __MachineSetPickOffsetCommand_H__

#include "MachineCommand.h"
#include "MachineState.h"

enum PickOffset
{
	PICKOFFSET_X,
	PICKOFFSET_Y,
	PICKOFFSET_TOOLHEIGHT,
	PICKOFFSET_PICKHEIGHT,
	PICKOFFSET_PLACEHEIGHT
};

class MachineSetPickOffsetCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachineSetPickOffsetCommand(PickOffset pickOffset, int offset);
	~MachineSetPickOffsetCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool IsValid()
	{
		return true;
	}

private:
	bool DoCommand(SerialPort &sp);
	MachineSetPickOffsetCommand* Copy();
	
	PickOffset m_pickOffset;
	int m_offset;
};

#endif // __MachineSetPickOffsetCommand_H__