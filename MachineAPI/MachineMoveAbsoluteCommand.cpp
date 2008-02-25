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
	return MachineState(m_pos, oldms.getY(), oldms.getZ(), oldms.getRot());
}

bool MachineMoveAbsoluteCommand::doCommand(SerialPort &sp)
{
	float fpos = m_pos/STEP_PRECISION;
	int pos = floor(fpos + 0.5);
	char movecmd[20];
	stringstream converter;
	converter << M_POS_ABS_MOVE_X << pos;
	strcpy(movecmd, converter.str().c_str());

	// TODO: Macroifiera skiten så att man kan skicka med axis till macrona.
	execCommand(sp, M_READY_1515,		M_ANS_1);
	execCommand(sp, M_DO_ABS_MOVE_X,	M_ANS_OK);
	execCommand(sp, movecmd,			M_ANS_OK);
	execCommand(sp, M_STORE_ABS_MOVE_X,	M_ANS_OK);
	execCommand(sp, M_EXEC_MOVE_X,		M_ANS_OK);
	execCommand(sp, M_READY_1515,		M_ANS_1);

	return TRUE;
}


MachineMoveAbsoluteCommand* MachineMoveAbsoluteCommand::copy()
{
	return new MachineMoveAbsoluteCommand(m_axis, m_pos);
}