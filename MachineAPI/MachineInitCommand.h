/**
 	\file MachineInitCommand.h
 
 	\brief
 	Header file for the MachineInitCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MACHINEINITCOMMAND_H__
#define __MACHINEINITCOMMAND_H__

#include "MachineCommand.h"

/// \class MachineInitCommand
/// \brief Initialize the Pick N Place Machine
class MachineInitCommand :
	public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachineInitCommand(void);
	~MachineInitCommand(void);
	MachineState GetAfterState(MachineState &current);
	string ToString();

private:
	MachineCommand* Copy();
	bool DoCommand(SerialPort &sp);

	MachineStateStruct m_state; ///< Copy of the state the machine will be put to for usage in the DoCommand function.
};

#endif //__MACHINEINITCOMMAND_H__
