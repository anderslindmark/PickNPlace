/**
 	\file MachineMoveNeedleCommand.h
 
 	\brief
 	Header file for the MachineMoveAbsoluteCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MACHINEMOVENEEDLECOMMAND_H__
#define __MACHINEMOVENEEDLECOMMAND_H__
#include "MachineCommand.h"

enum MachineNeedleMovement
{
	NEEDLEMOVEMENT_DOWN,
	NEEDLEMOVEMENT_UP
};

/// \class MachineMoveNeedleCommand
/// \brief Command to raise and lower the needle
class MachineMoveNeedleCommand :
	public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachineMoveNeedleCommand(MachineNeedleMovement move);
	~MachineMoveNeedleCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool HasNextState()
	{
		return false;
	}

	bool IsValid()	// TODO: Remove: Implemented in parent?
	{
		return true;
	}

private:
	MachineNeedleMovement m_move;
	MachineMoveNeedleCommand *Copy();
	bool DoCommand(SerialPort &sp);
};

#endif // __MACHINEMOVENEEDLECOMMAND_H__
