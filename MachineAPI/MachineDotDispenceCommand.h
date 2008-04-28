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
	/// \brief Constructor.
	///
	/// \param dotX	X position where the dot should be placed
	/// \param dotY	Y position where the dot should be placed
	MachineDotDispenceCommand(int dotX, int dotY);

	/// \brief Destructor.
	~MachineDotDispenceCommand(void);


	string ToString();
	MachineState GetAfterState(MachineState &oldms);

private:
	int m_x; ///< The x position of the dot
	int m_y; ///< The y position of the dot
	MachineStateStruct m_state; ///< Stores a copy of the machine state

	MachineDotDispenceCommand *Copy();
	bool DoCommand(SerialPort &sp);
};

#endif // __MACHINEDOTDISPENCECOMMAND_H__
