#pragma once
#include "MachineCommand.h"
#include "Axis.h"
#define STEP_PRECISION	10.0

class MachineMoveAbsoluteCommand :
	public MachineCommand
{
public:
	MachineMoveAbsoluteCommand(Axis axis, int position);
	~MachineMoveAbsoluteCommand(void);

private:
	bool doCommand(SerialPort &sp);
	Axis m_axis;
	int m_pos;
};
