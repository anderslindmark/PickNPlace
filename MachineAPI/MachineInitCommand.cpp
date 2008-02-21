#include "MachineInitCommand.h"

#define INIT_COMMAND_STRING "Machine init command"

MachineInitCommand::MachineInitCommand(void)
{
}

MachineInitCommand::~MachineInitCommand(void)
{
}

MachineState MachineInitCommand::getAfterState(MachineState ms)
{
	return MachineState(0,0,0,0);
}

string MachineInitCommand::toString()
{
	return INIT_COMMAND_STRING; 
}

bool MachineInitCommand::doCommand(SerialPort &sp)
{
	bool stop;

	stop = false;
	//sp.writeLine("RD 1915\n");

	return TRUE;
	
}