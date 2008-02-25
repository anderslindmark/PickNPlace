#pragma once
#include <string>
#include <windows.h>
#include <vector>

#include "SerialPort.h"
#include "MachineEvent.h"
#include "MachineCommand.h"
#include "MachineMoveAbsoluteCommand.h"

using namespace std;

typedef void (*Handler)(MachineEvent*);

class MachineController
{
public:
	/*
	 * Constructor for the MachineController.
	 *
	 * Takes the name of the com port that should be
	 * used for communication with the machine.
	 */
	MachineController(string);

	/*
	 * Destructor.
	 */
	~MachineController(void);
	
	/*
	 * Start the MachineController (runs in a thread).
	 */
	void start(void);
	
	/*
	 * Stops the MachineController (stops the thread).
	 */
	void stop(void);

	/*
	 * Handles a MachineCommand.
	 *
	 * Returns true if the MachineController is not
	 * currently working on a command and the command 
	 * will be handled, else false.
	 */
	bool runCommand(MachineCommand&);
	
	void wait(void);

	bool initialize();

	/*
	 * Adds an event handler, using a callback function which is run when an event happens
	 *
	 */
	void addEventHandler(Handler h);

private:
	SerialPort *sp;
	string comPort;
	bool working;
	bool initiated;
	vector<Handler> m_handlers;
	MachineCommand *m_cmd;
	MachineState currentState;
	void sendEvent(MachineEvent &e);
	bool validateCommand(MachineState &state, MachineEvent *&validateEvent);

	//Thread stuff
	HANDLE thread;
	DWORD threadId;
	HANDLE runCmdMutex; 
	static DWORD WINAPI runThread( LPVOID ) ; 
	void doCommand();
};
