#pragma once
#include "MachineCommand.h"
#include <string>
#include <windows.h>
using namespace std;

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

private:
	string comPort;
	bool working;
	bool initiated;
//	MachineCommand cmd;

	//Thread stuff
	HANDLE thread;
	DWORD threadId;
	HANDLE runCmdMutex; 
	static DWORD WINAPI runThread( LPVOID ) ; 
	void doCommand(MachineCommand*);
};
