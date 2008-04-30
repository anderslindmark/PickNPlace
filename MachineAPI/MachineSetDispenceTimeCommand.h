/**
 	\file MachineSetDispenceTimeCommand.h
 
 	\brief
 	Header file for the MachineSetDispenceTimeCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/
#ifndef __MachineSetDispenceTimeCommand_H__
#define __MachineSetDispenceTimeCommand_H__

#include "MachineCommand.h"
#include "MachineState.h"

/// \enum DispenceTimeType
/// \brief The different dispence times that can be set.
enum DispenceTimeType
{
	DISPENCETIME_BEFORE, ///< The time the solder should be applied before the first movment
	DISPENCETIME_AFTER, ///< The time the solder should be applied after the last movment
	DISPENCETIME_SUCKBACK ///< The time the solder should be sucked back after the last movment
};

/// \class MachineSetDispenceTimeCommand
/// \brief Sets the different times related to dispencing (Before/after/suckback)
class MachineSetDispenceTimeCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	/// \brief Create a new MachinePickCommand
	///
	/// \param tt The time that should be set
	/// \param multiplier What the time should be set to, multiple of 0.1s
	MachineSetDispenceTimeCommand(DispenceTimeType tt, unsigned int multiplier);
	~MachineSetDispenceTimeCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);

private:
	bool DoCommand(SerialPort &sp);
	MachineSetDispenceTimeCommand* Copy();

	DispenceTimeType m_tt; ///< The time that should be set
	unsigned int m_multiplier;	 ///< What the time should be set to, multiple of 0.1s
};

#endif // __MachineSetDispenceTimeCommand_H__
