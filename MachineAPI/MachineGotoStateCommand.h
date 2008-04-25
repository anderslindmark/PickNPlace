/**
 	\file MachineGotoStateCommand.h
 
 	\brief
 	Header file for the MachineGotoStateCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MachineGotoStateCommand_H__
#define __MachineGotoStateCommand_H__

#include "MachineCommand.h"
#include "MachineCommands.h"
#include "MachineState.h"

/// \class MachineGotoStateCommand
/// \brief Move the machine and set the machine settings according to a MachineState
class MachineGotoStateCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachineGotoStateCommand(MachineState state);
	MachineGotoStateCommand(MachineState state, bool initialize);
	~MachineGotoStateCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool IsValid()	// TODO: Remove: Implemented in parent?
	{
		return true;
	}

private:
	bool DoCommand(SerialPort &sp);
	MachineGotoStateCommand* Copy();
	
	MachineState m_state;
	bool m_initialize;
};

#endif // __MachineGotoStateCommand_H__
