/**
 	\file MachineMoveNeedleCommand.cpp
 
 	\brief
 	Source file for the MachineMoveNeedleCommand class
 
 	\author	Henrik Mäkitaavola & Anders Lindmark
**/


#include "MachineMoveNeedleCommand.h"

#define COMMAND_STRING "Machine Move Needle Command"

MachineMoveNeedleCommand::MachineMoveNeedleCommand(MachineNeedleMovement move)
{
	m_move = move;
}

MachineMoveNeedleCommand::~MachineMoveNeedleCommand(void)
{
}

string MachineMoveNeedleCommand::ToString()
{
	return string(COMMAND_STRING);
}

MachineState MachineMoveNeedleCommand::GetAfterState(MachineState &oldms)
{
	MachineStateStruct oldmss = oldms.GetState();
	if (m_move == NEEDLEMOVEMENT_DOWN)
		oldmss.dispenceState.needleDown = true;
	else
		oldmss.dispenceState.needleDown = false;
	return MachineState(oldmss);
}

MachineMoveNeedleCommand *MachineMoveNeedleCommand::Copy()
{
	return new MachineMoveNeedleCommand(m_move);
}
	
bool MachineMoveNeedleCommand::DoCommand(SerialPort &sp)
{
	if (m_move == NEEDLEMOVEMENT_DOWN)
		ExecCommand(sp, "RS 704",	M_ANS_OK);
	else
		ExecCommand(sp, "ST 704",	M_ANS_OK);

	ExecCommand(sp, M_READY_1915, M_ANS_1);
	return true;
}