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

/// \class MachineMoveAbsoluteCommand
/// \brief Move the machine to an absolue position
class MachineMoveAbsoluteCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	/// \brief Create a new MachineMoveAbsoluteCommand
	///
	/// \param axis Which axis to move along
	/// \param position The absolute position in the specified axis to move to
	MachineMoveAbsoluteCommand(Axis axis, int position);
	~MachineMoveAbsoluteCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool IsValid()
	{
		return true;
	}

private:
	MachineMoveAbsoluteCommand(Axis axis, int position, bool raiseZ);
	bool DoCommand(SerialPort &sp);
	MachineMoveAbsoluteCommand* Copy();
	Axis m_axis;
	int m_pos;
	bool m_raiseZ;
};

#endif //__MACHINEMOVEABSOLUTECOMMAND_H__
