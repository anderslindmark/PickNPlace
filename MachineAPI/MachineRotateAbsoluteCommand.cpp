/**
 	\file MachineRotateAbsoluteCommand.cpp
 
 	\brief
 	Source file for the MachineRotateAbsoluteCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#include "MachineRotateAbsoluteCommand.h"
#include <sstream>

#define ROTATE_ABSOLUTE_COMMAND_STRING "Rotate absolute command"

MachineRotateAbsoluteCommand::MachineRotateAbsoluteCommand(float angle)
{
	m_angle = angle;
}

MachineRotateAbsoluteCommand::~MachineRotateAbsoluteCommand(void)
{
}

MachineState MachineRotateAbsoluteCommand::GetAfterState(MachineState &current)
{
	return MachineState(current.GetX(), current.GetY(), current.GetZ(), m_angle);
}

string MachineRotateAbsoluteCommand::ToString(void)
{
	return string(ROTATE_ABSOLUTE_COMMAND_STRING);
}

MachineRotateAbsoluteCommand* MachineRotateAbsoluteCommand::Copy()
{
	return new MachineRotateAbsoluteCommand(m_angle);
}

bool MachineRotateAbsoluteCommand::DoCommand(SerialPort &sp)
{
	char movecmd[20];
	stringstream converter;
	int pos = (int) m_angle/(2*M_PI) * 4000;
	converter << M_POS_ABS_ROTATE;
	strcpy_s(movecmd, converter.str().c_str());
	ExecCommand(sp, M_READY_1515,		M_ANS_1);
	ExecCommand(sp, M_DO_ABS_ROTATE,	M_ANS_OK);
	ExecCommand(sp, movecmd,			M_ANS_OK);
	ExecCommand(sp, M_STORE_ABS_ROTATE,	M_ANS_OK);
	ExecCommand(sp, M_EXEC_ROTATE,		M_ANS_OK);
	ExecCommand(sp, M_READY_1515,		M_ANS_1);

	return true;
}