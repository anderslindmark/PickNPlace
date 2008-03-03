/**
 	\file MachineMoveAvsoluteCommand.cpp
 
 	\brief
 	Source file for the MachineMoveAvsoluteCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#include "MachineMoveAbsoluteCommand.h"
#include <iostream>
#include <sstream>

#define MOVE_ABSOLUTE_COMMAND_STRING "Machine move absolute command"

MachineMoveAbsoluteCommand::MachineMoveAbsoluteCommand(Axis axis, int position)
{
	m_axis = axis;
	m_pos = position;
}

MachineMoveAbsoluteCommand::~MachineMoveAbsoluteCommand(void)
{
}

string MachineMoveAbsoluteCommand::ToString(void)
{
	return string(MOVE_ABSOLUTE_COMMAND_STRING);
}

MachineState MachineMoveAbsoluteCommand::GetAfterState(MachineState &oldms)
{
	MachineStateStruct mss = oldms.GetState();
	switch (m_axis)
	{
		default:
		case AXIS_X:
			mss.x = m_pos;
			return MachineState(mss);
			break;
		case AXIS_Y:
			mss.y = m_pos;
			return MachineState(mss);
			break;
		case AXIS_Z:
			mss.z = m_pos;
			return MachineState(mss);
			break;
	}
}

bool MachineMoveAbsoluteCommand::DoCommand(SerialPort &sp)
{
	double fpos;
	int pos;
	char movecmd[20];
	stringstream converter;

	switch (m_axis)
	{
	case AXIS_X:
		MachineMoveAbsoluteCommand(AXIS_Z, 0).DoCommand(sp);	
		fpos = m_pos/STEP_PRECISION_X;
		pos = (int)floor(fpos + 0.5);
		converter << M_POS_ABS_MOVE_X;
		strcpy_s(movecmd, converter.str().c_str());
		ExecCommand(sp, M_READY_1515,		M_ANS_1);
		ExecCommand(sp, M_DO_ABS_MOVE_X,	M_ANS_OK);
		ExecCommand(sp, movecmd,			M_ANS_OK);
		ExecCommand(sp, M_STORE_ABS_MOVE_X,	M_ANS_OK);
		ExecCommand(sp, M_EXEC_MOVE_X,		M_ANS_OK);
		ExecCommand(sp, M_READY_1515,		M_ANS_1);
		break;

	case AXIS_Y:
		MachineMoveAbsoluteCommand(AXIS_Z, 0).DoCommand(sp);
		fpos = m_pos/STEP_PRECISION_Y;
		pos = (int)floor(fpos + 0.5);
		converter << M_POS_ABS_MOVE_Y;
		strcpy_s(movecmd, converter.str().c_str());
		ExecCommand(sp, M_READY_1515,		M_ANS_1);
		ExecCommand(sp, M_DO_ABS_MOVE_Y,	M_ANS_OK);
		ExecCommand(sp, movecmd,			M_ANS_OK);
		ExecCommand(sp, M_STORE_ABS_MOVE_Y,	M_ANS_OK);
		ExecCommand(sp, M_EXEC_MOVE_Y,		M_ANS_OK);
		ExecCommand(sp, M_READY_1515,		M_ANS_1);
		break;

	case AXIS_Z:
		fpos = m_pos/STEP_PRECISION_Z;
		pos = (int)floor(fpos + 0.5);
		converter << M_POS_ABS_MOVE_Z;
		strcpy_s(movecmd, converter.str().c_str());
		ExecCommand(sp, M_READY_1515,		M_ANS_1);
		ExecCommand(sp, M_DO_ABS_MOVE_Z,	M_ANS_OK);
		ExecCommand(sp, movecmd,			M_ANS_OK);
		ExecCommand(sp, M_STORE_ABS_MOVE_Z,	M_ANS_OK);
		ExecCommand(sp, M_EXEC_MOVE_Z,		M_ANS_OK);
		ExecCommand(sp, M_READY_1515,		M_ANS_1);
		break;
	}

	// TODO: Macroifiera skiten så att man kan skicka med axis till macrona.
	/*ExecCommand(sp, M_READY_1515,		M_ANS_1);
	ExecCommand(sp, M_DO_ABS_MOVE_X,	M_ANS_OK);
	ExecCommand(sp, movecmd,			M_ANS_OK);
	ExecCommand(sp, M_STORE_ABS_MOVE_X,	M_ANS_OK);
	ExecCommand(sp, M_EXEC_MOVE_X,		M_ANS_OK);
	ExecCommand(sp, M_READY_1515,		M_ANS_1);*/

	return TRUE;
}


MachineMoveAbsoluteCommand* MachineMoveAbsoluteCommand::Copy()
{
	return new MachineMoveAbsoluteCommand(m_axis, m_pos);
}