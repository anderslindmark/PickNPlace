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
	PICKTIME_AFTER_PICK,	// Wait after pick (* 0.1s)
	PICKTIME_PRESS_PICK,	// Press-Down time during pick (* 0.1s)
	PICKTIME_PRESS_PLACE, // Press-Down time during place (* 0.1s)
	PICKTIME_AFTER_PLACE	// Wait after place (* 0.1s)
};

/// \class MachineSetPickTimeCommand
/// \brief Used to dispence paste along a set of points.
///
class MachineSetPickTimeCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	/// \brief Constructor for MachineSetPickTimeCommand
	///
	/// \param polygon	Initial polygon
	MachineSetPickTimeCommand(PickTimeType type, int time);
	
	/// \brief Destructor for the MachineSetPickTimeCommand
	~MachineSetPickTimeCommand(void);

	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool HasNextState();

private:
	PickTimeType m_type;
	int m_time;

	bool DoCommand(SerialPort &sp);
	MachineSetPickTimeCommand *Copy();
};


#endif // __MachineSetPickTimeCommand_H__

