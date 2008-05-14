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
/// \brief Command to pick/place/drop a component at a specified coordinate
///
class MachinePickCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	/// \brief Create a new MachinePickCommand
	///
	/// \param cmd What action to do; pick, place or drop
	/// \param componentX X-coordinate of the component
	/// \param componentY Y-coordinate of the component
	/// \param angle angle of the component
	MachinePickCommand(PickCommandType cmd, int componentX, int componentY, float angle);
	~MachinePickCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool HasNextState();

private:
	PickCommandType m_cmd;
	bool DoCommand(SerialPort &sp);
	MachinePickCommand *Copy();
	
	MachineStateStruct m_state;
	bool m_firstState;
	int m_x;
	int m_y;
	float m_angle;
};


#endif // __MachinePickCommand_H__

