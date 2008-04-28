/**
 	\file MachineSetDispenceOffsetCommand.h
 
 	\brief
 	Header file for the MachineSetDispenceOffsetCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MachineSetDispenceOffsetCommand_H__
#define __MachineSetDispenceOffsetCommand_H__

#include "MachineCommand.h"
#include "MachineState.h"

/// \enum OffsetAxis
/// \brief The type of offset that should be set.
///
/// The offsets are documented in MachineState.h
enum OffsetAxis
{
	OFFSET_X,
	OFFSET_Y,
	OFFSET_Z,
	OFFSET_ZS,
	OFFSET_TURN
};

/// \class MachineSetDispenceOffsetCommand
/// \brief Settings for the different offsets needed when dispencing
class MachineSetDispenceOffsetCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	/// \brief Constructor.
	///
	/// \param axis The axis the offset should be applied to
	/// \param offset The offset length
	MachineSetDispenceOffsetCommand(OffsetAxis axis, int offset);
	~MachineSetDispenceOffsetCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);

private:
	bool DoCommand(SerialPort &sp);
	MachineSetDispenceOffsetCommand* Copy();
	
	OffsetAxis m_axis; ///< The axis
	int m_offset; ///< The offset length
};

#endif // __MachineSetDispenceOffsetCommand_H__
