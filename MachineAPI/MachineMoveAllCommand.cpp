

/**
 	\file MachineMoveAllCommand.cpp
 
 	\brief
 	Source file for the MachineMoveAllCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/
#include "MachineMoveAllCommand.h"
#include "MachineMoveAbsoluteCommand.h"
#include <iostream>
#include <sstream>

#define MOVE_ABSOLUTE_COMMAND_STRING "Machine move all axis simultaneously command"

MachineMoveAllCommand::MachineMoveAllCommand(int x, int y, int z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

MachineMoveAllCommand::~MachineMoveAllCommand(void)
{
}

string MachineMoveAllCommand::ToString(void)
{
	return string(MOVE_ABSOLUTE_COMMAND_STRING);
}

MachineState MachineMoveAllCommand::GetAfterState(MachineState &oldms)
{
	MachineStateStruct mss = oldms.GetState();
	if (m_x != -1) mss.x = m_x;
	if (m_y != -1) mss.y = m_y;
	if (m_z != -1) mss.z = m_z;
	return MachineState(mss);
}

bool MachineMoveAllCommand::DoCommand(SerialPort &sp)
{
	int pos;
	char movecmd_x[20];
	char movecmd_y[20];
	char movecmd_z[20];
	stringstream converter_x;
	stringstream converter_y;
	stringstream converter_z;

	//MachineMoveAbsoluteCommand(AXIS_Z, 0).DoCommand(sp);

	// Get the machine-world coordinates:
	int pos_x = ROUND(m_x/STEP_PRECISION_X);
	int pos_y = ROUND(m_y/STEP_PRECISION_Y);
	int pos_z = ROUND(m_z/STEP_PRECISION_Z);

	pos = pos_x;
	converter_x << M_POS_ABS_MOVE_X;
	strcpy_s(movecmd_x, converter_x.str().c_str());

	pos = pos_y;
	converter_y << M_POS_ABS_MOVE_Y;
	strcpy_s(movecmd_y, converter_y.str().c_str());
	
	pos = pos_z;
	converter_z << M_POS_ABS_MOVE_Z;
	strcpy_s(movecmd_z, converter_z.str().c_str());

	// Wait for machine-ready
	ExecCommand(sp, M_READY_1515,		M_ANS_1);
	
	// Write X movement:
	if (m_x != -1)
	{
		ExecCommand(sp, M_DO_ABS_MOVE_X,	M_ANS_OK);
		ExecCommand(sp, movecmd_x,			M_ANS_OK);
		ExecCommand(sp, M_STORE_ABS_MOVE_X,	M_ANS_OK);
	}
	
	// Write Y movement:
	if (m_y != -1)
	{
		ExecCommand(sp, M_DO_ABS_MOVE_Y,	M_ANS_OK);
		ExecCommand(sp, movecmd_y,			M_ANS_OK);
		ExecCommand(sp, M_STORE_ABS_MOVE_Y,	M_ANS_OK);
	}
	
	// Write Z movement:
	if (m_z != -1)
	{
		ExecCommand(sp, M_DO_ABS_MOVE_Z,	M_ANS_OK);
		ExecCommand(sp, movecmd_z,			M_ANS_OK);
		ExecCommand(sp, M_STORE_ABS_MOVE_Z,	M_ANS_OK);
	}

	// Execute all movement commands:
	if (m_x != -1) ExecCommand(sp, M_EXEC_MOVE_X,		M_ANS_OK);
	if (m_y != -1) ExecCommand(sp, M_EXEC_MOVE_Y,		M_ANS_OK);

	// Wait for machine-ready
	ExecCommand(sp, M_READY_1515,		M_ANS_1);
	
	// Lower head
	if (m_z != -1)
	{
		ExecCommand(sp, M_EXEC_MOVE_Z,		M_ANS_OK);
		ExecCommand(sp, M_READY_1515,		M_ANS_1);
	}

	return TRUE;
}


MachineMoveAllCommand* MachineMoveAllCommand::Copy()
{
	return new MachineMoveAllCommand(m_x, m_y, m_z);
}