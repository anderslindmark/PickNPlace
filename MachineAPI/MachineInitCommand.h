#pragma once
#include "machinecommand.h"

class MachineInitCommand :
	public MachineCommand
{
public:
	MachineInitCommand(void);
	~MachineInitCommand(void);
	MachineState getAfterState(MachineState &current);
	string toString();

private:
	MachineCommand* copy();
	bool doCommand(SerialPort &sp);
};
