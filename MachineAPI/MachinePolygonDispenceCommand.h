/**
 	\file MachinePolygonDispenceCommand.h
 
 	\brief
 	Header file for the MachinePolygonDispenceCommand class.

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MachinePolygonDispenceCommand_H__
#define __MachinePolygonDispenceCommand_H__

#include "MachineCommand.h"
#include "MachinePolygon.h"

/// \class MachinePolygonDispenceCommand
/// \brief Used to dispence paste along a set of points.
///
class MachinePolygonDispenceCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	/// \brief Constructor for MachinePolygonDispenceCommand
	///
	/// \param polygon	Initial polygon
	MachinePolygonDispenceCommand(MachinePolygon polygon);
	
	/// \brief Constructor for MachinePolygonDispenceCommand
	MachinePolygonDispenceCommand();
	
	/// \brief Destructor for the MachinePolygonDispenceCommand
	~MachinePolygonDispenceCommand(void);

	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool HasNextState();

	/// \brief Returns the polygon
	MachinePolygon GetPolygon();

	/// \brief Set the polygon
	bool SetPolygon(MachinePolygon polygon);
	bool IsValid();

private:
	bool DoCommand(SerialPort &sp);
	MachinePolygonDispenceCommand *Copy();
	/// \brief Check if this is a valid polygon. I.e if there are only right-angles
	bool ValidatePolygon();
	/// \brief Dispence a line from a point to the next
	void dispenceLine(SerialPort &sp, MachinePolygonPoint from, MachinePolygonPoint to);
	/// \brief Moves the needle to an offset, used to avoid "blobs" of paste at corners in the polygon
	void moveOffset(SerialPort &sp, MachinePolygonPoint oldPp, MachinePolygonPoint pp);

	MachinePolygon m_polygon;
	int m_vectorIndex;
	bool m_valid;
	MachineStateStruct m_state;
	MachineStateStruct m_tempState;
};


#endif // __MachinePolygonDispenceCommand_H__

