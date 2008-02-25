/**
 	\file MachineCommand.h
 
 	\brief
 	Header file for the abstract MachineCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MACHINECOMMAND_H__
#define __MACHINECOMMAND_H__

#include <string>
#include "MachineState.h"
#include "SerialPort.h"
#include "MachineCommandMacros.h"
#include <cmath>

using namespace std;

/// \class MachineCommand
/// \brief Interface for a Pick n Place machine command
class MachineCommand
{
	friend class MachineController;
public:
	/// \brief Destructor
	virtual ~MachineCommand() = 0 {};

	/// \brief Get the state after that this command would have been executed
	///
	/// \param current the current state that the Pick n Place machine is in
	/// \return the state after that this command would have been executed
	virtual MachineState getAfterState(MachineState &current) = 0;

	/// \brief String representation of the command
	///
	/// \return string representation of the command
	virtual string toString() = 0;

protected:
	/// \brief Do the command
	///
	/// \param sp the serial port that the Pick n Place machine is connected to
	/// \return true if the execution succseeded else false
	virtual bool doCommand(SerialPort &sp) = 0;

	/// \brief Get a copy of this object
	///
	/// \return a pointer to a copy of this object
	virtual MachineCommand* copy() = 0;

	/// \brief A helper function to send a command to the Pick n Place 
	/// machine and wait for a correct answer
	///
	/// \param sp the serial port to be used
	/// \param cmd the cmd to be sent to the Pick n Place machine
	/// \param ret the return value that is expected from the Pick n Place machine
	bool execCommand(SerialPort &sp, const char *cmd, const char *ret);
	
};

#endif //__MACHINECOMMAND_H__