#pragma once
#include <string>
using namespace std;

class MachineCommand {
public:
	MachineCommand();
	~MachineCommand();
//	virtual void getAfterState(MachineState) = 0;
	int getCommand();
	//virtual string getReadyRegister() = 0;
	//virtual string getReadyValue() = 0;
	//virtual string toString() = 0;
};