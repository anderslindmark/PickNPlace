/**
 	\file MachineParkCommand.h
 
 	\brief
 	Header file for the MachineParkCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MACHINEPARKCOMMAND_H_
#define __MACHINEPARKCOMMAND_H_

#include "MachineCommand.h"
#include "MachineMoveAbsoluteCommand.h"
#include "MachineRotateAbsoluteCommand.h"
#include "Axis.h"

/// \class MachineParkCommand
/// \brief Return the machine to origo and rotate the head to it's starting position
class MachineParkCommand :
	public MachineCommand
{
public:
	MachineParkCommand(void);
	~MachineParkCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);

private:
	bool DoCommand(SerialPort &sp);
	MachineParkCommand* Copy();
};

#endif // __MACHINEPARKCOMMAND_H_