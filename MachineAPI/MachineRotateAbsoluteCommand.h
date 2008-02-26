#pragma once
#include "machinecommand.h"
#include <cmath>

class MachineRotateAbsoluteCommand :
	public MachineCommand
{
public:
	MachineRotateAbsoluteCommand(float angle);
	~MachineRotateAbsoluteCommand(void);
	MachineState getAfterState(MachineState &current); 
	string toString();

private:
	MachineRotateAbsoluteCommand* copy();
	bool doCommand(SerialPort &sp);
	float m_angle;
	
};
