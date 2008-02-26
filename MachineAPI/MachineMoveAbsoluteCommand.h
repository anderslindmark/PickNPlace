/**
 	\file MachineMoveAbsoluteCommand.h
 
 	\brief
 	Header file for the MachineMoveAbsoluteCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MACHINEMOVEABSOLUTECOMMAND_H__
#define __MACHINEMOVEABSOLUTECOMMAND_H__

#include "MachineCommand.h"
#include "Axis.h"
#define STEP_PRECISION_X	10.0
#define STEP_PRECISION_Y	5.0
#define STEP_PRECISION_Z	1.0

/// \class MachineMoveAbsoluteCommand
/// \brief Move the Pick n Place machine to an absolue position
class MachineMoveAbsoluteCommand :
	public MachineCommand
{
public:
	MachineMoveAbsoluteCommand(Axis axis, int position);
	~MachineMoveAbsoluteCommand(void);
	string toString();
	MachineState getAfterState(MachineState &oldms);
private:
	bool doCommand(SerialPort &sp);
	MachineMoveAbsoluteCommand* copy();
	Axis m_axis;
	int m_pos;
};

#endif //__MACHINEMOVEABSOLUTECOMMAND_H__