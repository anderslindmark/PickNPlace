/**
 	\file MachineController.cpp
 
 	\brief
 	Source file for the MachineController class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#include "MachineController.h"
#include <iostream>

using namespace std;

/// \struct ThreadArg
/// \brief Argument to the thread function
struct ThreadArg
{
	MachineController *mc;
	ThreadArg(MachineController *_mc) : mc(_mc) { };
};

MachineController::MachineController(string serialPort)
{
	m_sp = NULL;
	m_comPort = serialPort;
	m_working = false;
	m_serialInitialized = false;
	m_initialized = false;
	m_initiating = false;
	m_thread = NULL;
	m_cmd = NULL;
	m_settings = MachineSettings();
	m_currentState = MachineState();
	m_runCmdMutex = CreateMutex( 
        NULL,   // default security attributes
        FALSE,  // initially not owned
        NULL);	// unnamed mutex
}

MachineController::~MachineController(void)
{
	if (this->m_sp != NULL)
	{
		m_sp->ClosePort();
	}

	if (this->m_sp)
	{
		delete m_sp;
	}

	if (this->m_cmd)
	{
		delete m_cmd;
	}
}

bool MachineController::InitializeSerial()
{
	m_sp = new SerialPort(m_comPort);
	if(m_sp->Initialize())
	{
		m_sp->ConfigurePort();
		m_serialInitialized = true;
		//m_sp->SetCommunicationTimeouts(0, 2, 5000, 2, 5000);
		m_sp->SetCommunicationTimeouts(0, 0, 5000, 0, 5000);
		return true;
	}
	else
	{
		delete m_sp;
		m_sp = NULL;
		return false;
	}
}

bool MachineController::InitializeMachine()
{
	if (!m_serialInitialized)
	{
		if (!InitializeSerial())
		{
			return false;
		}
	}
	m_initiating = true;
	RunCommand(*(new MachineInitCommand()));
	return true;
}

bool MachineController::RunCommand(MachineCommand &cmd)
{
	if (!m_initialized && !m_initiating)
	{
		return false;
	}
	bool returnVal = false;
	DWORD dwWaitResult;
	ThreadArg *threadArg;

	//Grab mutex
	dwWaitResult = WaitForSingleObject( 
		m_runCmdMutex,		// Handle to mutex
		INFINITE);			// No time-out interval

	// Check result from mutex grab
	switch (dwWaitResult) 
	{
		// The thread got ownership of the mutex
		case WAIT_OBJECT_0: 
			if (!m_working) 
			{
				m_working = true;
				delete m_cmd;
				m_cmd = cmd.Copy();
				WaitForSingleObject(m_thread, INFINITE);
				threadArg = new ThreadArg(this); // Thread argument.

				// Create a new thread to handle the command.
				m_thread = CreateThread( 
					NULL,										// Default security attributes.
					0,											// Use default stack size.  
					(LPTHREAD_START_ROUTINE) this->RunThread,	// Thread function.
					threadArg,									// Argument to thread function. 
					0,											// Use default creation flags.
					&m_threadId);								// Returns the thread identifier.
				returnVal = true;
			}
			break;

		// The thread got ownership of an abandoned mutex.
		case WAIT_ABANDONED: 
			returnVal = false;
	}

	// Release mutex.
	if (! ReleaseMutex(m_runCmdMutex)) 
	{ 
		// TODO: Deal with error.
	} 
	return returnVal;
}


void MachineController::Wait(void) 
{
	WaitForSingleObject(m_thread, INFINITE);
}


void MachineController::DoCommand() 
{
	MachineEvent *validateEvent;

	// Validate command.
	if (!ValidateCommand(*m_cmd, m_currentState, validateEvent))
	{
		SendEvent(*validateEvent);
		delete validateEvent;
	}
	else
	{
		try
		{
			m_cmd->DoCommand(*m_sp);
		}
		catch (MachineEvent e)
		{
			SendEvent(MachineEvent(e.GetEventType(), "(" + m_cmd->ToString() + ") " + e.GetEventMsg()));
			m_initialized = false;
			m_initiating = false;
			m_working = false;
			return;
		}

		if (m_initiating)
		{
			m_initialized = true;
			m_initiating = false;
			SendEvent(MachineEvent(EVENT_MACHINE_INITIALIZED, m_cmd->ToString()));
		}
		
		SendEvent(MachineEvent(EVENT_CMD_DONE, m_cmd->ToString()));
	}
	m_working = false;
}

DWORD WINAPI MachineController::RunThread( LPVOID lpParam )
{
	ThreadArg *threadArg = (ThreadArg*)lpParam;
	(*(threadArg->mc)).DoCommand();
	
	delete threadArg;
	return 0;
}

void MachineController::AddEventHandler(Handler h)
{
	m_handlers.push_back( h );
}

void MachineController::SendEvent(MachineEvent &e)
{
	MachineEvent *eCopy;

	for (unsigned int i = 0; i < m_handlers.size(); i++)
	{
		eCopy = new MachineEvent(e);
		CreateThread( 
					NULL,									// Default security attributes.
					0,										// Use default stack size.
					(LPTHREAD_START_ROUTINE) m_handlers[i],	// Thread function.
					eCopy,									// Argument to thread function.
					0,										// Use default creation flags.
					NULL);									// Returns the thread identifier.
	}
}


MachineState MachineController::GetCurrentState()
{
	return m_currentState;
}

bool MachineController::IsInitialized()
{
	return m_initialized;
}

bool MachineController::IsBusy()
{
	return m_working;
}

// TODO: Check MachineSetDispenceOffset so that Z isn't out of bounds.....
bool MachineController::ValidateCommand(MachineCommand &cmd, MachineState &ms, MachineEvent *&validateEvent)
{
	MachineState currentState = ms;
	if (!cmd.IsValid())
	{
		validateEvent = new MachineEvent(EVENT_CMD_INVALID, "Invalid command");
		return false;
	}

	do
	{
		MachineState state = cmd.GetAfterState(currentState);
		MachineStateStruct mss = state.GetState();

		// DEBUG:
		// cout << endl << state.ToString() << endl;

		if (!(mss.x >= m_settings.xMin && mss.x <= m_settings.xMax))
		{
			validateEvent = new MachineEvent(EVENT_CMD_OUT_OF_BOUNDS, "Out of bounds in X-axis");
			return false;
		}
		else if (!(mss.y >= m_settings.yMin && mss.y <= m_settings.yMax))
		{
			validateEvent = new MachineEvent(EVENT_CMD_OUT_OF_BOUNDS, "Out of bounds in Y-axis");
			return false;
		}
		else if ( !(mss.z >= m_settings.zMin && mss.z <= m_settings.zMax) )
		{
			validateEvent = new MachineEvent(EVENT_CMD_OUT_OF_BOUNDS, "Out of bounds in Z-axis");
			return false;
		}
		else if (!(mss.rot >= m_settings.rotMin && mss.rot <= m_settings.rotMax))
		{
			validateEvent = new MachineEvent(EVENT_CMD_OUT_OF_BOUNDS, "Out of bounds in rotation");
			return false;
		}
		currentState = state;
	}
	while (cmd.HasNextState());
	ms = currentState;
	return true;
}

bool MachineController::ValidateCommand(MachineCommand &cmd, MachineState &ms, string &errorMsg)
{
	MachineCommand *tmpCmd = cmd.Copy();
	MachineEvent *tmp = NULL;
	bool commandValid = ValidateCommand(*tmpCmd, ms, tmp);
	if (tmp != NULL)
	{
		errorMsg = tmp->GetEventMsg();
	}
	delete tmp;
	delete tmpCmd;
	return commandValid;
}

MachineSettings MachineController::GetSettings()
{
	return m_settings;
}

void MachineController::SetSettings(MachineSettings settings)
{
	m_settings = settings;
}

