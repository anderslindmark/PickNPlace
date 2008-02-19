#pragma once
#include "MachineCommand.h"

class TestCommand :
	public MachineCommand
{
public:
	TestCommand(string in);
	~TestCommand(void);
	string getCommand();
	string my;
};
