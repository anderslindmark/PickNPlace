#include "MachineSetSpeedCommand.h"
#include <iostream>

#define SET_SPEED_COMMAND_STRING "Machine Set Speed Command"
#define CONVERT_TO_MACHINE_SPEED(x)	256*x+1

MachineSetSpeedCommand::MachineSetSpeedCommand(int speed)
{
	m_speed = speed;
}

MachineSetSpeedCommand::~MachineSetSpeedCommand(void)
{
}

string MachineSetSpeedCommand::ToString()
{
	return string(SET_SPEED_COMMAND_STRING);
}

MachineState MachineSetSpeedCommand::GetAfterState(MachineState &oldms)
{
	MachineStateStruct mss = oldms.GetState();
	mss.speed = m_speed;
	return MachineState(mss);
}


bool MachineSetSpeedCommand::DoCommand(SerialPort &sp)
{
	char speedStr[20];
	sprintf_s(speedStr, sizeof(speedStr), "WR DM211 %d", CONVERT_TO_MACHINE_SPEED(m_speed));
	cout << "Machine Speed: " << speedStr << endl;
	// Set speed: x=256*val+1 WR DM210 57346 WR DM211 (x)
	ExecCommand(sp, "WR DM210 57346", M_ANS_OK);
	ExecCommand(sp, M_READY_1515, M_ANS_1);
	ExecCommand(sp, speedStr, M_ANS_OK);
	ExecCommand(sp, M_READY_1515, M_ANS_1);
	return true;
}

MachineSetSpeedCommand* MachineSetSpeedCommand::Copy()
{
	return new MachineSetSpeedCommand(m_speed);
}