/**
 	\file MachineWrapperCommand.h
 
 	\brief
 	Header file for the MachineWrapperCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MachineWrapperCommand_H__
#define __MachineWrapperCommand_H__

#include "MachineCommand.h"
#include <vector>

/// \class MachineWrapperCommand
/// \brief Move the Pick n Place machine to an absolue position
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
	int m_current;
	MachineStateStruct m_state;
	vector<MachineCommand*> m_commands;

	bool DoCommand(SerialPort &sp);
	MachineWrapperCommand* Copy();
	
	
};

#endif //__MachineWrapperCommand_H__