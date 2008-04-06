/**
 	\file MachineMoveAllCommand.h
 
 	\brief
 	Header file for the MachineMoveAllCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MachineMoveAllCommand_H__
#define __MachineMoveAllCommand_H__

#include "MachineCommand.h"
#include "Axis.h"
#define STEP_PRECISION_X	10.0
#define STEP_PRECISION_Y	5.0
#define STEP_PRECISION_Z	1.0

/// \class MachineMoveAllCommand
/// \brief Move the Pick n Place machine to an absolue position by moving all axis simultaneously.
/// If one axis should not be moved, use -1 as the target position.
class MachineMoveAllCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachineMoveAllCommand(int x, int y, int z);
	~MachineMoveAllCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool IsValid()
	{
		return true;
	}

private:
	bool DoCommand(SerialPort &sp);
	MachineMoveAllCommand* Copy();
	int m_x;
	int m_y;
	int m_z;
};

#endif //__MachineMoveAllCommand_H__