/**
 	\file MachineCommand.h
 
 	\brief
 	Header file for the abstract MachineCommand class.
	The MachineCommand class is the class on which all commands are built.
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MACHINECOMMAND_H__
#define __MACHINECOMMAND_H__

#define M_PI	3.141592653589793238462643383279502884197169399375f

// Since a command should be able to directly run other commands, make sure they are friend classes.
#define MACHINE_COMMAND_FRIENDS		friend class MachineMoveAbsoluteCommand; \
									friend class MachineMovePolygonCommand; \
									friend class MachineMoveRelativeCommand; \
									friend class MachineParkCommand; \
									friend class MachineRotateAbsoluteCommand; \
									friend class MachineSetDispenceSpeedCommand; \
									friend class MachineSetDispenceOffsetCommand; \
									friend class MachineMoveAllCommand; \
									friend class MachineDotDispenceCommand; \
									friend class MachineSetSpeedCommand; \
									friend class MachineSetDispenceTimeCommand; \
									friend class MachineMoveNeedleCommand; \
									friend class MachineLightBrightnessCommand; \
									friend class MachinePolygonDispenceCommand; \
									friend class MachineInitCommand; \
									friend class MachineWrapperCommand; \
									friend class MachinePickCommand; \
									friend class MachineSetPickTimeCommand; \
									friend class MachineSetPickOffsetCommand; \
									friend class MachineGotoStateCommand

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
	friend class MachineWrapperCommand;
public:
	/// \brief Destructor
	virtual ~MachineCommand() = 0 {};

	/// \brief Get the state after (a step of) this command has been executed
	///
	/// \param current the current state that the Pick n Place machine is in
	/// \return the state after this command has been executed
	virtual MachineState GetAfterState(MachineState &current) = 0;

	/// \brief Checks whether the command has more states
	///
	/// A command can be composed of many steps, for example 2 distinct movements.
	/// Both movements have to be validated by the MachineController.
	/// \return true if the command has more states
	virtual bool HasNextState() { return false; };

	/// \brief String representation of the command
	///
	/// \return string representation of the command
	virtual string ToString() = 0;

	/// \brief If the command has specific internal errors that MachineController::ValidateCommand() doesn't check, it is reported here
	///
	/// \return true if the command is valid else false
	virtual bool IsValid() { return true; };

protected:
	/// \brief Execute the command
	///
	/// \param sp the serial port that the Pick n Place machine is connected to
	/// \return true if the execution succseeded, else false
	virtual bool DoCommand(SerialPort &sp) = 0;

	/// \brief Make a Copy of this object
	///
	/// \return a pointer to a Copy of this object
	virtual MachineCommand* Copy() = 0;

	/// \brief A helper function to send a command to the Pick n Place 
	/// machine and Wait for a correct answer
	///
	/// \param sp the serial port to be used
	/// \param cmd the cmd to be sent to the Pick n Place machine
	/// \param ret the return value that is expected from the Pick n Place machine
	bool ExecCommand(SerialPort &sp, const char *cmd, const char *ret);
	
	/// \brief A helper function to send a command to the Pick n Place 
	/// machine and wait for an integer return value
	///
	/// \param sp the serial port to be used
	/// \param cmd the cmd to be sent to the Pick n Place machine
	/// \return an integer value
	int ExecCommandInt(SerialPort &sp, const char *cmd);
};

#endif //__MACHINECOMMAND_H__
