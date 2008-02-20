#pragma once
#include "machinecommand.h"

class MachineInitCommand :
	public MachineCommand
{
public:
	MachineInitCommand(void);
	~MachineInitCommand(void);
	MachineState getAfterState(MachineState ms);
	string toString();

private:
	bool doCommand(SerialPort &sp);
};
