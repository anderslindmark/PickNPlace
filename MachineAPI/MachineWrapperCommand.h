/**
 	\file MachineWrapperCommand.h
 
 	\brief
 	Header file for the MachineWrapperCommand class
 

 	\author	Henrik M�kitaavola & Anders Lindmark
**/

#ifndef __MachineWrapperCommand_H__
#define __MachineWrapperCommand_H__

#include "MachineCommand.h"
#include <vector>

/// \class MachineWrapperCommand
/// \brief A wrapper that takes a series of commands, executes them in sequence, and then returns to where it was before this execution began.
class MachineWrapperCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachineWrapperCommand();
	~MachineWrapperCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool IsValid();
	bool HasNextState();
	void Add(MachineCommand &cmd);

private:
	bool DoCommand(SerialPort &sp);
	MachineWrapperCommand* Copy();
	
	int m_current;
	MachineStateStruct m_state;
	vector<MachineCommand*> m_commands;
};

#endif //__MachineWrapperCommand_H__
