/**
 	\file MachineMoveNeedleCommand.h
 
 	\brief
 	Header file for the MachineMoveNeedleCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MACHINEMOVENEEDLECOMMAND_H__
#define __MACHINEMOVENEEDLECOMMAND_H__
#include "MachineCommand.h"

/// \enum MachineNeedleMovement
/// \brief Move needle up or down
enum MachineNeedleMovement
{
	NEEDLEMOVEMENT_DOWN, ///< Move needle down
	NEEDLEMOVEMENT_UP ///< Move needle up
};

/// \class MachineMoveNeedleCommand
/// \brief Command to raise and lower the needle
class MachineMoveNeedleCommand :
	public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	/// \brief Constructor.
	///
	/// \param move What type of movment
	MachineMoveNeedleCommand(MachineNeedleMovement move);

	~MachineMoveNeedleCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);

private:
	MachineNeedleMovement m_move; ///< The type of movement

	MachineMoveNeedleCommand *Copy();
	bool DoCommand(SerialPort &sp);
};

#endif // __MACHINEMOVENEEDLECOMMAND_H__
