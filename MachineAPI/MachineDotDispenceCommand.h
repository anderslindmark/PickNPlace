/**
 	\file MachineDotDispenceCommand.h
 
 	\brief
 	Header file for the MachineDotDispenceCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MACHINEDOTDISPENCECOMMAND_H__
#define __MACHINEDOTDISPENCECOMMAND_H__
#include "machinecommand.h"

/// \class MachineDotDispenceCommand
/// \brief Dispence a dot of paste at the specified coordinates
class MachineDotDispenceCommand :
	public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachineDotDispenceCommand();	// TODO: Change the command so it takes coordinates instead?
	~MachineDotDispenceCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool HasNextState();

	bool IsValid()		// TODO: Remove: Är inte den här redan implementerad i MachineCommand.h ?
	{
		return true;
	}

private:
	MachineDotDispenceCommand *Copy();
	bool DoCommand(SerialPort &sp);

	MachineStateStruct m_state;
	bool m_moreStates;

};

#endif // __MACHINEDOTDISPENCECOMMAND_H__
