/**
 	\file MachineParkCommand.cpp
 
 	\brief
 	Source file for the MachineParkCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#include "MachineParkCommand.h"

#define COMMAND_STRING "Machine park command"

MachineParkCommand::MachineParkCommand(void)
{
}

MachineParkCommand::~MachineParkCommand(void)
{
}

string MachineParkCommand::ToString(void)
{
	return string(COMMAND_STRING);
}

MachineState MachineParkCommand::GetAfterState(MachineState &oldms)
{
	MachineStateStruct mss = oldms.GetState();
	mss.x = 0;
	mss.y = 0;
	mss.z = 0;
	mss.rot = 0.0;
	return MachineState(mss);
}

bool MachineParkCommand::DoCommand(SerialPort &sp)
{
	MachineMoveAbsoluteCommand(AXIS_Z, 0).DoCommand(sp);
	MachineMoveAbsoluteCommand(AXIS_Y, 0).DoCommand(sp);
	MachineMoveAbsoluteCommand(AXIS_X, 0).DoCommand(sp);
	MachineRotateAbsoluteCommand(0.0).DoCommand(sp);

	return TRUE;
}


MachineParkCommand* MachineParkCommand::Copy()
{
	return new MachineParkCommand();
}
