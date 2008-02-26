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

string MachineMoveAbsoluteCommand::toString(void)
{
	return string(MOVE_ABSOLUTE_COMMAND_STRING);
}

MachineState MachineMoveAbsoluteCommand::getAfterState(MachineState &oldms)
{
	switch (m_axis)
	{
	case AXIS_X:
		return MachineState(m_pos, oldms.getY(), oldms.getZ(), oldms.getRot());
		break;
	case AXIS_Y:
		return MachineState(oldms.getX(), m_pos, oldms.getZ(), oldms.getRot());
		break;
	case AXIS_Z:
		return MachineState(oldms.getX(), oldms.getY(), m_pos, oldms.getRot());
		break;
	}
}

bool MachineMoveAbsoluteCommand::doCommand(SerialPort &sp)
{
	double fpos;
	int pos;
	char movecmd[20];
	stringstream converter;

	switch (m_axis)
	{
	case AXIS_X:
		MachineMoveAbsoluteCommand(AXIS_Z, 0).doCommand(sp);	
		fpos = m_pos/STEP_PRECISION_X;
		pos = (int)floor(fpos + 0.5);
		converter << M_POS_ABS_MOVE_X;
		strcpy_s(movecmd, converter.str().c_str());
		execCommand(sp, M_READY_1515,		M_ANS_1);
		execCommand(sp, M_DO_ABS_MOVE_X,	M_ANS_OK);
		execCommand(sp, movecmd,			M_ANS_OK);
		execCommand(sp, M_STORE_ABS_MOVE_X,	M_ANS_OK);
		execCommand(sp, M_EXEC_MOVE_X,		M_ANS_OK);
		execCommand(sp, M_READY_1515,		M_ANS_1);
		break;

	case AXIS_Y:
		MachineMoveAbsoluteCommand(AXIS_Z, 0).doCommand(sp);
		fpos = m_pos/STEP_PRECISION_Y;
		pos = (int)floor(fpos + 0.5);
		converter << M_POS_ABS_MOVE_Y;
		strcpy_s(movecmd, converter.str().c_str());
		execCommand(sp, M_READY_1515,		M_ANS_1);
		execCommand(sp, M_DO_ABS_MOVE_Y,	M_ANS_OK);
		execCommand(sp, movecmd,			M_ANS_OK);
		execCommand(sp, M_STORE_ABS_MOVE_Y,	M_ANS_OK);
		execCommand(sp, M_EXEC_MOVE_Y,		M_ANS_OK);
		execCommand(sp, M_READY_1515,		M_ANS_1);
		break;

	case AXIS_Z:
		fpos = m_pos/STEP_PRECISION_Z;
		pos = (int)floor(fpos + 0.5);
		converter << M_POS_ABS_MOVE_Z;
		strcpy_s(movecmd, converter.str().c_str());
		execCommand(sp, M_READY_1515,		M_ANS_1);
		execCommand(sp, M_DO_ABS_MOVE_Z,	M_ANS_OK);
		execCommand(sp, movecmd,			M_ANS_OK);
		execCommand(sp, M_STORE_ABS_MOVE_Z,	M_ANS_OK);
		execCommand(sp, M_EXEC_MOVE_Z,		M_ANS_OK);
		execCommand(sp, M_READY_1515,		M_ANS_1);
		break;
	}

	// TODO: Macroifiera skiten så att man kan skicka med axis till macrona.
	/*execCommand(sp, M_READY_1515,		M_ANS_1);
	execCommand(sp, M_DO_ABS_MOVE_X,	M_ANS_OK);
	execCommand(sp, movecmd,			M_ANS_OK);
	execCommand(sp, M_STORE_ABS_MOVE_X,	M_ANS_OK);
	execCommand(sp, M_EXEC_MOVE_X,		M_ANS_OK);
	execCommand(sp, M_READY_1515,		M_ANS_1);*/

	return TRUE;
}


MachineMoveAbsoluteCommand* MachineMoveAbsoluteCommand::copy()
{
	return new MachineMoveAbsoluteCommand(m_axis, m_pos);
}