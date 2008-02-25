/**
 	\file MachineController.h
 
 	\brief
 	Header file for the MachineController class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MACHINECONTROLLER_H__
#define __MACHINECONTROLLER_H__

#include <string>
#include <windows.h>
#include <vector>

#include "SerialPort.h"
#include "MachineEvent.h"
#include "MachineCommand.h"
#include "MachineMoveAbsoluteCommand.h"

using namespace std;

/// \typedef Handler
/// \brief Function definition of a event Handler function used as
/// argument to AddEventHandler
///
typedef void (*Handler)(MachineEvent*);


/// \class MachineController
/// \brief Used to communicate
///        with a Pick n Place machine.
///
/// After beeing initialized it can 
/// be feed with commands (MachineCommand) through the RunCommand function.
/// The class will only handle one command at a time, the
/// RunCommand function will return false if the object hasn't
/// been initialized correctly or if an other command is beeing
/// handeled. The handeling of the command will be runned in a 
/// own thread so that it doesent block the caller. Events are
/// sent due to failure or succsses inside the Machine Controller 
/// object to all event subscribers. To subscribe for events use
/// AddEventHandler.
class MachineController
{
public:

	/// \brief Constructor for the Machine Controller.
	///
	/// \param serialPort	Name of Serial Port to be used
	MachineController(string serialPort);

	/// \brief Destructor for the Machine Controller.
	~MachineController(void);

	
	/// \brief Handles a command
	///
	/// \param cmd	The command to be handled
	/// \return true if the MachineController is not
	///			currently working on a command and the command 
	///			will be handled, else false
	bool runCommand(MachineCommand& cmd);
	
	/// \brief Wait for the Machine Controller to finnish working on a command
	void wait(void);

	/// \brief Initialize the Machine Controller
	///
	/// The serial port communication will be opened and the pick n place
	/// machine will be configured to a initial state that depends configuration
	/// given.
	///
	/// return true if initialization succeeded else false
	bool initialize();

	/// \brief Add a event subscriber
	///
	/// \param handler the subscribers handler function that should be called
	void addEventHandler(Handler handler);

private:
	SerialPort *sp; ///< The serial communication object
	string comPort; ///< What serial port should be used
	bool working; ///< Indication wheter a command is beeing processed
	bool initiated; ///< Indication wheter the Machine Controller has been initialized
	vector<Handler> m_handlers; ///< Vector of event subscribers
	MachineCommand *m_cmd;	///< Current command beeing processed
	MachineState currentState; ///< Current state of the Pick n Place machine.

	/// \brief Send a event to all subscribers
	///
	/// \param e event to be sent
	void sendEvent(MachineEvent &e);

	/// \brief Validate if current command that is being processed is legal
	///
	/// \param state current state
	/// \param validateEvent a pointer to an event if command is not legal
	/// \return true if command is legal else false
	bool validateCommand(MachineState &state, MachineEvent *&validateEvent);

	//Thread stuff
	HANDLE thread; ///< Handler for the command Thread
	DWORD threadId;	///< Command threads ID
	HANDLE runCmdMutex; ///< Mutex for the RunCommand function
	
	/// \brief Method that is passed to the thread creator.
	///
	/// This method will be passed a private Machine Controller struct
	/// containing required referenses
	///
	/// \param lpvoid
	/// \return ...
	static DWORD WINAPI runThread( LPVOID lpvoid);

	/// \brief Called by runThread to start processing the command
	void doCommand();
};

#endif //__MACHINECONTROLLER_H__