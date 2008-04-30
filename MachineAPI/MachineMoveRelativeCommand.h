/**
 	\file MachineMoveRelativeCommand.h
 
 	\brief
 	Header file for the MachineMoveRelativeCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MACHINEMOVERELATIVECOMMAND_H__
#define __MACHINEMOVERELATIVECOMMAND_H__

#include "MachineCommand.h"
#include "MachineMoveAbsoluteCommand.h"
#include "MachineEvent.h"

/// \class MachineMoveRelativeCommand
/// \brief Move the Pick n Place machine relative to the current position
class MachineMoveRelativeCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachineMoveRelativeCommand(Axis axis, int distance);
	~MachineMoveRelativeCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);

private:
	bool DoCommand(SerialPort &sp);
	MachineMoveRelativeCommand* Copy();
	
	Axis m_axis;
	int m_dist;
	int m_newX, m_newY, m_newZ;
	bool m_stateKnown;
};

#endif // __MACHINEMOVERELATIVECOMMAND_H__
