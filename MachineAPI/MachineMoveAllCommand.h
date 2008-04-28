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


/// \class MachineMoveAllCommand
/// \brief Move the Pick n Place machine to an absolue position by moving all axis simultaneously.
/// If one axis should not be moved, use -1 as the target position.
class MachineMoveAllCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	/// \brief Create a new MachineMoveAllCommand. If one of the axis should not be moved, set the value
	/// of that axis to -1
	/// 
	/// \param x X-coordinate
	/// \param y Y-coordinate
	/// \param z Z-coordinate
	MachineMoveAllCommand(int x, int y, int z);

	~MachineMoveAllCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);

private:
	bool DoCommand(SerialPort &sp);
	MachineMoveAllCommand* Copy();

	int m_x; ///< X Coordinate
	int m_y; ///< Y Coordinate
	int m_z; ///< Z Coordinate
};

#endif //__MachineMoveAllCommand_H__
