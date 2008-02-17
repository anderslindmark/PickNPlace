#include "MachineController.h"
#include <iostream>
//struct ThreadArg {
//	bool *working;
//	MachineCommand *cmd;
//	ThreadArg(MachineCommand *_cmd, bool *_working) :working(_working), cmd(_cmd) { };
//};
using namespace std;
typedef void (MachineController::*DoCommand)(void);

struct ThreadArg {
	MachineController *mc;
	MachineCommand *cmd;
	ThreadArg(MachineController *_mc, MachineCommand *_cmd) :mc(_mc), cmd(_cmd) { };
};

MachineController::MachineController(string _comPort)
{
	comPort = _comPort;
	working = false;
	initiated = false;
	thread = NULL;
	runCmdMutex = CreateMutex( 
        NULL,   // default security attributes
        FALSE,  // initially not owned
        NULL);	// unnamed mutex
}

MachineController::~MachineController(void)
{
}

bool MachineController::runCommand(MachineCommand &_cmd) {
	bool returnVal = false;
	DWORD dwWaitResult;
	ThreadArg *threadArg;

	dwWaitResult = WaitForSingleObject( 
		runCmdMutex,    // handle to mutex
		INFINITE);  // no time-out interval
	switch (dwWaitResult) 
	{
		// The thread got ownership of the mutex
		case WAIT_OBJECT_0: 
			//__try 
			//{
				if (!working) {
					//cout << "true"<<endl;
					working = true;
					WaitForSingleObject(thread, INFINITE);
					threadArg = new ThreadArg(this, &_cmd);
					thread = CreateThread( 
						NULL,				// default security attributes
						0,					// use default stack size  
						(LPTHREAD_START_ROUTINE) this->runThread,   // thread function 
						threadArg,			// argument to thread function 
						0,					// use default creation flags 
						&threadId);			// returns the thread identifier 
					returnVal = true;
				}
				
			//} 

			//__finally
			//{ 
				// Release ownership of the mutex object
			//	if (! ReleaseMutex(runCmdMutex)) 
			//	{ 
					// Deal with error.
			//	} 
			//} 
			break;

		// The thread got ownership of an abandoned mutex
		case WAIT_ABANDONED: 
			returnVal = false;
	}
	if (! ReleaseMutex(runCmdMutex)) 
	{ 
					// Deal with error.
	} 
	return returnVal;
}

void MachineController::wait(void) {
	WaitForSingleObject(thread, INFINITE);
}

void MachineController::doCommand(MachineCommand *cmd) {
	std::cout<<"MC CMD " <<cmd->getCommand() << std::endl;
	working = false;
}

DWORD WINAPI MachineController::runThread( LPVOID lpParam ) {
	ThreadArg *threadArg = (ThreadArg*)lpParam;
	(*(threadArg->mc)).doCommand(threadArg->cmd);
	
	delete threadArg;
	return 0;
}