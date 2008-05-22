/**
 	\file MachineController.cpp
 
 	\brief
 	Source file for the MachineInitCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#include "MachineInitCommand.h"
#include "MachineCommands.h"

#define COMMAND_STRING "Machine init command"

MachineInitCommand::MachineInitCommand(void)
{
}

MachineInitCommand::~MachineInitCommand(void)
{
}

MachineState MachineInitCommand::GetAfterState(MachineState &current)
{
	MachineState state = MachineState();
	m_state = state.GetState();
	return state;
}

string MachineInitCommand::ToString()
{
	return COMMAND_STRING; 
}

MachineCommand* MachineInitCommand::Copy()
{
	return new MachineInitCommand();
}

bool MachineInitCommand::DoCommand(SerialPort &sp)
{
	ExecCommand(sp, "CR", M_ANS_CC);
	// Set lamps to medium brightness
	MachineLightBrightnessCommand(LAMP_CAMERA, m_state.lampCameraBrightness).DoCommand(sp);
	MachineLightBrightnessCommand(LAMP_LOOKUP, m_state.lampLookupBrightness).DoCommand(sp);

	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "ST 1900", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "CR", M_ANS_CC);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "RD 1515", M_ANS_1);
	ExecCommand(sp, "ST 1800", M_ANS_OK);	// Some kind of park
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM215 400", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM213 0", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WS T35 0", M_ANS_OK);	// Set Before time to 0s
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WS T36 0", M_ANS_OK);	// Set After time to 0s
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WS T37 0", M_ANS_OK);	// Set Suckback time to 0s
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM210 57346", M_ANS_OK);	// Dispence speed prelude
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM211 257", M_ANS_OK);	// Set dispence speed to 1
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM300 35328", M_ANS_OK);
	ExecCommand(sp, "WR DM301 2500", M_ANS_OK);
	ExecCommand(sp, "WR DM51 2", M_ANS_OK);
	ExecCommand(sp, "WR DM50 300", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM300 35840", M_ANS_OK);
	ExecCommand(sp, "WR DM301 50", M_ANS_OK);
	ExecCommand(sp, "WR DM51 2", M_ANS_OK);
	ExecCommand(sp, "WR DM50 300", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM300 36608", M_ANS_OK);
	ExecCommand(sp, "WR DM301 0", M_ANS_OK);
	ExecCommand(sp, "WR DM51 2", M_ANS_OK);
	ExecCommand(sp, "WR DM50 300", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM310 35328", M_ANS_OK);
	ExecCommand(sp, "WR DM311 5000", M_ANS_OK);
	ExecCommand(sp, "WR DM61 2", M_ANS_OK);
	ExecCommand(sp, "WR DM60 310", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM310 35840", M_ANS_OK);
	ExecCommand(sp, "WR DM311 100", M_ANS_OK);
	ExecCommand(sp, "WR DM61 2", M_ANS_OK);
	ExecCommand(sp, "WR DM60 310", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM310 36608", M_ANS_OK);
	ExecCommand(sp, "WR DM311 0", M_ANS_OK);
	ExecCommand(sp, "WR DM61 2", M_ANS_OK);
	ExecCommand(sp, "WR DM60 310", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM320 35328", M_ANS_OK);
	ExecCommand(sp, "WR DM321 500", M_ANS_OK);
	ExecCommand(sp, "WR DM71 2", M_ANS_OK);
	ExecCommand(sp, "WR DM70 320", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM320 35840", M_ANS_OK);
	ExecCommand(sp, "WR DM321 25", M_ANS_OK);
	ExecCommand(sp, "WR DM71 2", M_ANS_OK);
	ExecCommand(sp, "WR DM70 320", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM320 36608", M_ANS_OK);
	ExecCommand(sp, "WR DM321 0", M_ANS_OK);
	ExecCommand(sp, "WR DM71 2", M_ANS_OK);
	ExecCommand(sp, "WR DM70 320", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM320 33280", M_ANS_OK);
	ExecCommand(sp, "WR DM321 0", M_ANS_OK);
	ExecCommand(sp, "WR DM71 2", M_ANS_OK);
	ExecCommand(sp, "WR DM70 320", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM300 57410", M_ANS_OK);
	ExecCommand(sp, "WR DM301 12802", M_ANS_OK);	// Set X min/max speed TODO: Comment better.
	ExecCommand(sp, "WR DM51 2", M_ANS_OK);
	ExecCommand(sp, "WR DM50 300", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM310 57410", M_ANS_OK);
	ExecCommand(sp, "WR DM311 19201", M_ANS_OK);
	ExecCommand(sp, "WR DM61 2", M_ANS_OK);
	ExecCommand(sp, "WR DM60 310", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM320 57361", M_ANS_OK);
	ExecCommand(sp, "WR DM321 15362", M_ANS_OK);
	ExecCommand(sp, "WR DM71 2", M_ANS_OK);
	ExecCommand(sp, "WR DM70 320", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM330 57460", M_ANS_OK);	// Settings for Z 
	ExecCommand(sp, "WR DM331 2561", M_ANS_OK);
	ExecCommand(sp, "WR DM81 2", M_ANS_OK);
	ExecCommand(sp, "WR DM80 330", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM320 33536", M_ANS_OK);
	ExecCommand(sp, "WR DM321 2400", M_ANS_OK);
	ExecCommand(sp, "WR DM71 2", M_ANS_OK);
	ExecCommand(sp, "WR DM70 320", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);
	ExecCommand(sp, "WR DM330 33024", M_ANS_OK);
	ExecCommand(sp, "WR DM331 1800", M_ANS_OK);
	ExecCommand(sp, "WR DM81 2", M_ANS_OK);
	ExecCommand(sp, "WR DM80 330", M_ANS_OK);
	ExecCommand(sp, "RD 1915", M_ANS_1);

	// Set the dispence offsets to 0 for safety reasons
	MachineSetDispenceOffsetCommand(OFFSET_Z, m_state.dispenceState.offsetZ).DoCommand(sp);
	MachineSetDispenceOffsetCommand(OFFSET_ZS, m_state.dispenceState.offsetZs).DoCommand(sp);
	//MachineMoveAllCommand(0, 0, 0).DoCommand(sp);
	return true;
}
