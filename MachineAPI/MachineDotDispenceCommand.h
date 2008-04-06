#pragma once
#include "machinecommand.h"

class MachineDotDispenceCommand :
	public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachineDotDispenceCommand();
	~MachineDotDispenceCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool HasNextState()
	{
		return false;
	}

	bool IsValid()
	{
		return true;
	}

private:
	MachineDotDispenceCommand *Copy();
	bool DoCommand(SerialPort &sp);

	MachineStateStruct m_state;

};