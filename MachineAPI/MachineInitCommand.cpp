#include "MachineInitCommand.h"

#define INIT_COMMAND_STRING "Machine init command"

MachineInitCommand::MachineInitCommand(void)
{
}

MachineInitCommand::~MachineInitCommand(void)
{
}

MachineState MachineInitCommand::getAfterState(MachineState &current)
{
	return MachineState(0,0,0,0);
}

string MachineInitCommand::toString()
{
	return INIT_COMMAND_STRING; 
}

MachineCommand* MachineInitCommand::copy()
{
	return new MachineInitCommand();
}

bool MachineInitCommand::doCommand(SerialPort &sp)
{
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "ST 1900", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "CR", M_ANS_CC);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "RD 1515", M_ANS_1);
	execCommand(sp, "ST 1800", M_ANS_OK);	// Some kind of park
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM215 400", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM213 0", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WS T35 0", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WS T36 0", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WS T37 0", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM210 57346", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM211 257", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM300 35328", M_ANS_OK);
	execCommand(sp, "WR DM301 2500", M_ANS_OK);
	execCommand(sp, "WR DM51 2", M_ANS_OK);
	execCommand(sp, "WR DM50 300", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM300 35840", M_ANS_OK);
	execCommand(sp, "WR DM301 50", M_ANS_OK);
	execCommand(sp, "WR DM51 2", M_ANS_OK);
	execCommand(sp, "WR DM50 300", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM300 36608", M_ANS_OK);
	execCommand(sp, "WR DM301 0", M_ANS_OK);
	execCommand(sp, "WR DM51 2", M_ANS_OK);
	execCommand(sp, "WR DM50 300", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM310 35328", M_ANS_OK);
	execCommand(sp, "WR DM311 5000", M_ANS_OK);
	execCommand(sp, "WR DM61 2", M_ANS_OK);
	execCommand(sp, "WR DM60 310", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM310 35840", M_ANS_OK);
	execCommand(sp, "WR DM311 100", M_ANS_OK);
	execCommand(sp, "WR DM61 2", M_ANS_OK);
	execCommand(sp, "WR DM60 310", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM310 36608", M_ANS_OK);
	execCommand(sp, "WR DM311 0", M_ANS_OK);
	execCommand(sp, "WR DM61 2", M_ANS_OK);
	execCommand(sp, "WR DM60 310", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM320 35328", M_ANS_OK);
	execCommand(sp, "WR DM321 500", M_ANS_OK);
	execCommand(sp, "WR DM71 2", M_ANS_OK);
	execCommand(sp, "WR DM70 320", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM320 35840", M_ANS_OK);
	execCommand(sp, "WR DM321 25", M_ANS_OK);
	execCommand(sp, "WR DM71 2", M_ANS_OK);
	execCommand(sp, "WR DM70 320", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM320 36608", M_ANS_OK);
	execCommand(sp, "WR DM321 0", M_ANS_OK);
	execCommand(sp, "WR DM71 2", M_ANS_OK);
	execCommand(sp, "WR DM70 320", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM320 33280", M_ANS_OK);
	execCommand(sp, "WR DM321 0", M_ANS_OK);
	execCommand(sp, "WR DM71 2", M_ANS_OK);
	execCommand(sp, "WR DM70 320", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM300 57410", M_ANS_OK);
	execCommand(sp, "WR DM301 12802", M_ANS_OK);
	execCommand(sp, "WR DM51 2", M_ANS_OK);
	execCommand(sp, "WR DM50 300", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM310 57410", M_ANS_OK);
	execCommand(sp, "WR DM311 19201", M_ANS_OK);
	execCommand(sp, "WR DM61 2", M_ANS_OK);
	execCommand(sp, "WR DM60 310", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM320 57361", M_ANS_OK);
	execCommand(sp, "WR DM321 15362", M_ANS_OK);
	execCommand(sp, "WR DM71 2", M_ANS_OK);
	execCommand(sp, "WR DM70 320", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM330 57460", M_ANS_OK);
	execCommand(sp, "WR DM331 2561", M_ANS_OK);
	execCommand(sp, "WR DM81 2", M_ANS_OK);
	execCommand(sp, "WR DM80 330", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM320 33536", M_ANS_OK);
	execCommand(sp, "WR DM321 2400", M_ANS_OK);
	execCommand(sp, "WR DM71 2", M_ANS_OK);
	execCommand(sp, "WR DM70 320", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
	execCommand(sp, "WR DM330 33024", M_ANS_OK);
	execCommand(sp, "WR DM331 1800", M_ANS_OK);
	execCommand(sp, "WR DM81 2", M_ANS_OK);
	execCommand(sp, "WR DM80 330", M_ANS_OK);
	execCommand(sp, "RD 1915", M_ANS_1);
  


	return TRUE;
	
}