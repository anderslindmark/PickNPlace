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
/// \brief A wrapper that takes a series of commands, executes them in sequence, 
/// and then optionally returns to where it was before this execution began.
class MachineWrapperCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachineWrapperCommand();

	/// \brief Constructor with the option to tell the wrapper if it 
	///			should return to the starting point.
	///
	/// \param returnToOrigin If true return to position before exectution else dont.
	MachineWrapperCommand(bool returnToOrigin);
	~MachineWrapperCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool IsValid();
	bool HasNextState();

	/// \brief Add a copy of a command to the wrapper
	///
	/// \param cmd The command that should be added to the wrapper
	void Add(MachineCommand &cmd);

private:
	bool DoCommand(SerialPort &sp);
	MachineWrapperCommand* Copy();
	
	bool m_returnToOrigin; ///< Return to the position that the machine was in before the wrapper started executing.
	int m_current;			///< Counter for internal state.
	MachineStateStruct m_state;
	vector<MachineCommand*> m_commands;
};

#endif //__MachineWrapperCommand_H__
