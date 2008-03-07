/**
 	\file MachineRotateAbsoluteCommand.h
 
 	\brief
 	Header file for the MachineInitCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MACHINEROTATEABSOLUTECOMMAND_H__
#define __MACHINEROTATEABSOLUTECOMMAND_H__

#include "machinecommand.h"

/// \class MachineRotateAbsoluteCommand
/// \brief Rotate the head on the Pick N Place machine to a specific angle
class MachineRotateAbsoluteCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachineRotateAbsoluteCommand(float angle);
	~MachineRotateAbsoluteCommand(void);
	MachineState GetAfterState(MachineState &oldms); 
	string ToString();

private:
	float m_angle; ///< The angle the head should be rotated to
	MachineRotateAbsoluteCommand* Copy();
	bool DoCommand(SerialPort &sp);
};

#endif //__MACHINEROTATEABSOLUTECOMMAND_H__