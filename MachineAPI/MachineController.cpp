#include "MachineController.h"
#include <iostream>

using namespace std;

struct ThreadArg {
	MachineController *mc;
	ThreadArg(MachineController *_mc) : mc(_mc) { };
};

MachineController::MachineController(string serialPort) : currentState(0, 0, 0, 0.0)
{
	sp = NULL;
	comPort = serialPort;
	working = false;
	serialInitialized = false;
	initialized = false;
	initiating = false;
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

bool MachineController::initializeSerial()
{
	sp = new SerialPort(comPort);
	if(sp->initialize())
	{
		serialInitialized = true;		
		return true;
	}
	else
	{
		delete sp;
		sp = NULL;
		return false;
	}
}

bool MachineController::initializeMachine()
{
	if (!serialInitialized)
	{
		if (!initializeSerial())
		{
			return false;
		}
	}
	initiating = true;
	runCommand(*(new MachineInitCommand()));
	return true;
}

bool MachineController::runCommand(MachineCommand &cmd)
{
	if (!initialized && !initiating)
	{
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


void MachineController::wait(void) 
{
	WaitForSingleObject(thread, INFINITE);
}


void MachineController::doCommand() 
{
	//std::cout<<"MC CMD " <<cmd->getCommand() << std::endl;
	MachineEvent *validateEvent;
	if(!validateCommand(*m_cmd, validateEvent))
	{
		sendEvent(*validateEvent);
		delete validateEvent;
	}
	else
	{
		m_cmd->doCommand(*sp);
		if (initiating)
		{
			initialized = true;
			initiating = false;
			sendEvent(MachineEvent(EVENT_INITIALIZED, m_cmd->toString()));
		}
		sendEvent(MachineEvent(EVENT_DONE, m_cmd->toString()));
	}
	
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

MachineState MachineController::getCurrentState()
{
	return currentState;
}

void MachineController::sendEvent(MachineEvent &e)
{
	MachineEvent *eCopy;
	//int id;
	for( unsigned int i = 0; i < m_handlers.size(); i++ )
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

bool MachineController::validateCommand(MachineCommand &cmd, MachineEvent *&validateEvent)
{
	// TODO: Move bounds to config:
	int xMin = 0;
	int xMax = 470000;	// Working area ends aroun 350000, Z need to be limited beyond that to avoid crash.
	int yMin = 0;
	int yMax = 193000;
	int zMin = 0;
	int zMax = 10000;
	float rMin = 0;
	float rMax = 2*M_PI;

	MachineState state = cmd.getAfterState(currentState);
	cout << "AfterState: x:" << state.getX() << " y:" << state.getY() << " z:" << state.getZ() << endl;
	if (state.getX() > 350000)
	{
		zMax = 0;	// TODO: Find max Z
	}

	if (!(state.getX() >= xMin && state.getX() <= xMax))
	{
		validateEvent = new MachineEvent(EVENT_CMD_OUT_OF_BOUNDS, "Out of bounds in X-axis");
		return false;
	}
	else if (!(state.getY() >= yMin && state.getY() <= yMax))
	{
		validateEvent = new MachineEvent(EVENT_CMD_OUT_OF_BOUNDS, "Out of bounds in Y-axis");
		return false;
	}
	else if (!(state.getZ() >= zMin && state.getZ() <= zMax))
	{
		validateEvent = new MachineEvent(EVENT_CMD_OUT_OF_BOUNDS, "Out of bounds in Z-axis");
		return false;
	}
	else if (!(state.getRot() >= rMin && state.getRot() <= rMax))
	{
		validateEvent = new MachineEvent(EVENT_CMD_OUT_OF_BOUNDS, "Out of bounds in rotation");
		return false;
	}
	currentState = state;
	return true;
}