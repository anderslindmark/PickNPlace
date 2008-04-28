/**
 	\file MachineGotoStateCommand.h
 
 	\brief
 	Header file for the MachineGotoStateCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MachineGotoStateCommand_H__
#define __MachineGotoStateCommand_H__

#include "MachineCommand.h"
#include "MachineCommands.h"
#include "MachineState.h"

/// \class MachineGotoStateCommand
/// \brief Move the machine and set the machine settings according to a MachineState
class MachineGotoStateCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	/// \brief Constructor, used if the machine should not run a initialize command first.
	///
	/// \param state The state the machine should be set to.
	MachineGotoStateCommand(MachineState state);

	/// \brief Constructor.
	///
	/// \param state The state the machine should be set to.
	/// \param initialize Indicates whether the machine should be initialized first.
	MachineGotoStateCommand(MachineState state, bool initialize);

	/// \brief Destructor.
	~MachineGotoStateCommand(void);

	string ToString();
	MachineState GetAfterState(MachineState &oldms);

private:
	bool DoCommand(SerialPort &sp);
	MachineGotoStateCommand* Copy();
	
	MachineState m_state;  ///< The state the machine should move to
	bool m_initialize;	///< Indicates whether the machine should initialize first
};

#endif // __MachineGotoStateCommand_H__
