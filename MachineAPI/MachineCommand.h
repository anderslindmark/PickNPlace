#pragma once
#include <string>
using namespace std;

class MachineCommand {
public:
	//MachineCommand();
	//virtual ~MachineCommand();
//	virtual void getAfterState(MachineState) = 0;
	virtual int getCommand() = 0;
	//virtual string getReadyRegister() = 0;
	//virtual string getReadyValue() = 0;
	//virtual string toString() = 0;
};