/**
 	\file MachinePickCommand.h
 
 	\brief
 	Header file for the MachinePickCommand class.

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MachinePickCommand_H__
#define __MachinePickCommand_H__

#include "MachineCommand.h"
#include "MachinePolygon.h"

enum PickCommandType {
	PICKCMD_PICK,
	PICKCMD_PLACE,
	PICKCMD_DROP
};

/// \class MachinePickCommand
/// \brief Used to dispence paste along a set of points.
///
class MachinePickCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	/// \brief Constructor for MachinePickCommand
	///
	/// \param polygon	Initial polygon
	MachinePickCommand(PickCommandType cmd);
	
	/// \brief Destructor for the MachinePickCommand
	~MachinePickCommand(void);

	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool HasNextState();

private:
	PickCommandType m_cmd;
	bool DoCommand(SerialPort &sp);
	MachinePickCommand *Copy();

	int m_oldZ;
};


#endif // __MachinePickCommand_H__

