#pragma once
#include "MachineCommand.h"

class DiagonalTest :
	public MachineCommand
{
public:
	DiagonalTest(void);
	~DiagonalTest(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);

private:
	bool DoCommand(SerialPort &sp);
	DiagonalTest* Copy();
};
