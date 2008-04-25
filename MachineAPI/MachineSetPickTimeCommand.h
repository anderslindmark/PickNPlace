/**
 	\file MachineSetPickTimeCommand.h
 
 	\brief
 	Header file for the MachineSetPickTimeCommand class.

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MachineSetPickTimeCommand_H__
#define __MachineSetPickTimeCommand_H__

#include "MachineCommand.h"
#include "MachinePolygon.h"

enum PickTimeType {
	PICKTIME_AFTER_PICK,	///< Wait after pick
	PICKTIME_PRESS_PICK,	///< Press-Down time during pick
	PICKTIME_PRESS_PLACE, 	///< Press-Down time during place
	PICKTIME_AFTER_PLACE	///< Wait after place
};

/// \class MachineSetPickTimeCommand
/// \brief Set pick/place related times
class MachineSetPickTimeCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	/// \brief Constructor for MachineSetPickTimeCommand
	///
	/// \param type	Which time should be set
	/// \param time The time (*0.1s)
	MachineSetPickTimeCommand(PickTimeType type, int time);
	
	/// \brief Destructor for the MachineSetPickTimeCommand
	~MachineSetPickTimeCommand(void);

	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool HasNextState();

private:
	bool DoCommand(SerialPort &sp);
	MachineSetPickTimeCommand *Copy();

	PickTimeType m_type;
	int m_time;
};


#endif // __MachineSetPickTimeCommand_H__

