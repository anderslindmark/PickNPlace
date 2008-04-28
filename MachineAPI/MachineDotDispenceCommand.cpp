/**
 	\file MachineDotDispenceCommand.cpp
 
 	\brief
 	Header file for the dot dispence command
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/


#include "MachineDotDispenceCommand.h"
#include "MachineCommands.h"

#define COMMAND_STRING "Machine Dot Dispence Command"

MachineDotDispenceCommand::MachineDotDispenceCommand(int dotX, int dotY)
{
	m_x = dotX;
	m_y = dotY;
}

MachineDotDispenceCommand::~MachineDotDispenceCommand(void)
{
}

string MachineDotDispenceCommand::ToString()
{
	return string(COMMAND_STRING);
}

MachineState MachineDotDispenceCommand::GetAfterState(MachineState &oldms)
{
	m_state = oldms.GetState();
	m_state.x = m_x - m_state.dispenceState.offsetX;
	m_state.y = m_y - m_state.dispenceState.offsetY;
	
	return MachineState(m_state);
}

MachineDotDispenceCommand *MachineDotDispenceCommand::Copy()
{
	return new MachineDotDispenceCommand();
}

bool MachineDotDispenceCommand::DoCommand(SerialPort &sp)
{
	// Move solder tool above the spot:
	MachineMoveAbsoluteCommand(AXIS_Z, 0).DoCommand(sp);
	MachineMoveAllCommand(m_state.x, m_state.y, -1).DoCommand(sp);
		
	//SOLDER:
	ExecCommand(sp, "ST 1613",	M_ANS_OK); // Set dot dispence mode
	MachineMoveNeedleCommand(NEEDLEMOVEMENT_DOWN).DoCommand(sp);
	ExecCommand(sp, "ST 1908",	M_ANS_OK);	// Execute dispence
	ExecCommand(sp, M_READY_1915,	M_ANS_1);

	// Move up head
	MachineMoveNeedleCommand(NEEDLEMOVEMENT_UP).DoCommand(sp);
	
	return true;
}