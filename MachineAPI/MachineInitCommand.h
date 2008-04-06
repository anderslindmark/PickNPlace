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
public:
	MachineInitCommand(void);
	~MachineInitCommand(void);
	MachineState GetAfterState(MachineState &current);
	string ToString();
	bool IsValid()
	{
		return true;
	}

private:
	MachineCommand* Copy();
	bool DoCommand(SerialPort &sp);
};

#endif //__MACHINEINITCOMMAND_H__