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
	string toString();
	MachineState getAfterState(MachineState &oldms);
private:
	bool doCommand(SerialPort &sp);
	MachineMoveAbsoluteCommand* copy();
	Axis m_axis;
	int m_pos;
};
