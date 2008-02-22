#include "MachineController.h"
#include <iostream>

//struct ThreadArg {
//	bool *working;
//	MachineCommand *cmd;
//	ThreadArg(MachineCommand *_cmd, bool *_working) :working(_working), cmd(_cmd) { };
//};
using namespace std;
//typedef void (MachineController::*DoCommand)(void);

struct ThreadArg {
	MachineController *mc;
	ThreadArg(MachineController *_mc) : mc(_mc) { };
};

MachineController::MachineController(string _comPort)
{
	sp = NULL;
	comPort = _comPort;
	working = false;
	initiated = false;
	thread = NULL;
	m_cmd = NULL;
	runCmdMutex = CreateMutex( 
        NULL,   // default security attributes
        FALSE,  // initially not owned
        NULL);	// unnamed mutex
}

MachineController::~MachineController(void)
{
	delete sp;
	delete m_cmd;
}

bool MachineController::initialize() {
	sp = new SerialPort(comPort);
	if(sp->initialize())
	{
		initiated = true;
		return true;
	}
	else
	{
		delete sp;
		return false;
	}
}


bool MachineController::runCommand(MachineCommand &cmd) {
	if (!initiated) {
		return false;
	}
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
			if (!working) {
				//cout << "true"<<endl;
				working = true;
				delete m_cmd;
				m_cmd = cmd.copy();
				WaitForSingleObject(thread, INFINITE);
				threadArg = new ThreadArg(this);
				thread = CreateThread( 
					NULL,				// default security attributes
					0,					// use default stack size  
					(LPTHREAD_START_ROUTINE) this->runThread,   // thread function 
					threadArg,			// argument to thread function 
					0,					// use default creation flags 
					&threadId);			// returns the thread identifier 
				returnVal = true;
			}
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


void MachineController::doCommand() {
	//std::cout<<"MC CMD " <<cmd->getCommand() << std::endl;
	m_cmd->doCommand(*sp);
	sendEvent(MachineEvent(EVENT_DONE, m_cmd->toString() + "GRYMT"));
	working = false;
}


DWORD WINAPI MachineController::runThread( LPVOID lpParam ) {
	ThreadArg *threadArg = (ThreadArg*)lpParam;
	(*(threadArg->mc)).doCommand();
	
	delete threadArg;
	return 0;
}

void MachineController::addEventHandler(Handler h)
{
	m_handlers.push_back( h );
}

void MachineController::sendEvent(MachineEvent &e)
{
	MachineEvent *eCopy;
	//int id;
	for( int i = 0; i < m_handlers.size(); i++ )
	{
		eCopy = new MachineEvent(e);
		CreateThread( 
					NULL,				// default security attributes
					0,					// use default stack size  
					(LPTHREAD_START_ROUTINE) m_handlers[i],   // thread function 
					eCopy,				// argument to thread function 
					0,					// use default creation flags 
					NULL);			// returns the thread identifier 
		
		//(*m_handlers[i])(*this, e);
	}
}
