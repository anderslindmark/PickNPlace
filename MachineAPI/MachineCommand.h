#pragma once
#include <string>
//#include "MachineController.h"
#include "MachineState.h"
#include "SerialPort.h"
#include "MachineCommandMacros.h"
#include <cmath>
using namespace std;

class MachineCommand
{
	friend class MachineController;
public:
	virtual ~MachineCommand() = 0 {};
	//virtual MachineState getAfterState(MachineState) = 0;
	//virtual string toString() = 0;

protected:
	virtual bool doCommand(SerialPort &sp) = 0;
	bool execCommand(SerialPort &sp, const char *cmd, const char *ret);
};