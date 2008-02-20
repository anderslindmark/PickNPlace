#pragma once
#include <string>
#include "MachineController.h"
#include "MachineState.h"
#include "SerialPort.h"
using namespace std;

class MachineCommand
{
	friend class MachineController;
public:
	virtual ~MachineCommand() = 0 {};
	virtual MachineState getAfterState(MachineState) = 0;
	virtual string toString() = 0;

private:
	virtual bool doCommand(SerialPort &sp) = 0;
};