#include "MachineMoveAbsoluteCommand.h"
#include <iostream>
#include <sstream>

MachineMoveAbsoluteCommand::MachineMoveAbsoluteCommand(Axis axis, int position)
{
	float fpos = position/STEP_PRECISION;
	m_axis = axis;
	m_pos = floor(fpos + 0.5);

}

MachineMoveAbsoluteCommand::~MachineMoveAbsoluteCommand(void)
{
}

bool MachineMoveAbsoluteCommand::doCommand(SerialPort &sp)
{
	char movecmd[20];
	stringstream converter;
	converter << M_POS_ABS_MOVE_X << m_pos;
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
