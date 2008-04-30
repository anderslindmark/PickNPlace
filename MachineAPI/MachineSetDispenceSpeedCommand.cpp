/**
 	\file MachineSetDispenceSpeedCommand.cpp
 
 	\brief
 	Source file for the MachineSetDispenceSpeedCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#include "MachineSetDispenceSpeedCommand.h"
#include <iostream>

#define COMMAND_STRING "Machine Set Speed Command"
#define CONVERT_TO_MACHINE_SPEED(x)	256*x+1

MachineSetDispenceSpeedCommand::MachineSetDispenceSpeedCommand(int speed)
{
	m_speed = speed;
}

MachineSetDispenceSpeedCommand::~MachineSetDispenceSpeedCommand(void)
{
}

string MachineSetDispenceSpeedCommand::ToString()
{
	return string(COMMAND_STRING);
}

MachineState MachineSetDispenceSpeedCommand::GetAfterState(MachineState &oldms)
{
	MachineStateStruct mss = oldms.GetState();
	mss.dispenceState.speed = m_speed;
	return MachineState(mss);
}


bool MachineSetDispenceSpeedCommand::DoCommand(SerialPort &sp)
{
	char speedStr[20];
	sprintf_s(speedStr, sizeof(speedStr), "WR DM211 %d", CONVERT_TO_MACHINE_SPEED(m_speed));
	// Set speed: x=256*val+1 WR DM210 57346 WR DM211 (x)
	ExecCommand(sp, "WR DM210 57346", M_ANS_OK);
	ExecCommand(sp, M_READY_1515, M_ANS_1);
	ExecCommand(sp, speedStr, M_ANS_OK);
	ExecCommand(sp, M_READY_1515, M_ANS_1);
	return true;
}

MachineSetDispenceSpeedCommand* MachineSetDispenceSpeedCommand::Copy()
{
	return new MachineSetDispenceSpeedCommand(m_speed);
}

bool MachineSetDispenceSpeedCommand::IsValid()
{
	if (m_speed < 1 || m_speed > 12)
	{
		return false;
	}
	else
	{
		return true;
	}
}