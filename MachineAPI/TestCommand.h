#pragma once
#include "MachineCommand.h"

class TestCommand :
	public MachineCommand
{
public:
	TestCommand(void);
	~TestCommand(void);
	int getCommand();
};
