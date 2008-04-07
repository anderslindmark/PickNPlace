#ifndef __MachineSetDispenceTimeCommand_H__
#define __MachineSetDispenceTimeCommand_H__

#include "MachineCommand.h"
#include "MachineState.h"

enum DispenceTimeType
{
	DISPENCETIME_BEFORE,
	DISPENCETIME_AFTER,
	DISPENCETIME_SUCKBACK
};

class MachineSetDispenceTimeCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachineSetDispenceTimeCommand(DispenceTimeType tt, int multiplier);
	~MachineSetDispenceTimeCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool IsValid()
	{
		return true;
	}

private:
	bool DoCommand(SerialPort &sp);
	MachineSetDispenceTimeCommand* Copy();

	DispenceTimeType m_tt;
	int m_multiplier;
};

#endif // __MachineSetDispenceTimeCommand_H__
