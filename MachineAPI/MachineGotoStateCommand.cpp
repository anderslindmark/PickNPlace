/**
 	\file MachineGotoStateCommand.cpp
 
 	\brief
 	Source file for the MachineGotoStateCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#include "MachineGotoStateCommand.h"
#include <iostream>

#define COMMAND_STRING "Machine Goto State Command"

MachineGotoStateCommand::MachineGotoStateCommand(MachineState state)
{
	m_state = state;
	m_initialize = false;
}

MachineGotoStateCommand::MachineGotoStateCommand(MachineState state, bool initialize)
{
	m_state = state;
	m_initialize = initialize;
}


MachineGotoStateCommand::~MachineGotoStateCommand(void)
{
}

string MachineGotoStateCommand::ToString()
{
	return string(COMMAND_STRING);
}

MachineState MachineGotoStateCommand::GetAfterState(MachineState &oldms)
{
	return m_state;
}


bool MachineGotoStateCommand::DoCommand(SerialPort &sp)
{
	MachineStateStruct state = m_state.GetState();

	// Initialize the machine
	if (m_initialize)
	{
		MachineInitCommand().DoCommand(sp);
	}

	// Move
	MachineMoveAllCommand(state.x, state.y, state.z).DoCommand(sp);
	MachineRotateAbsoluteCommand(state.rot).DoCommand(sp);
	// Set dispence:
	MachineSetDispenceSpeedCommand(state.dispenceState.speed).DoCommand(sp);
	MachineSetDispenceOffsetCommand(OFFSET_Z, state.dispenceState.offsetZ).DoCommand(sp);
	MachineSetDispenceOffsetCommand(OFFSET_ZS, state.dispenceState.offsetZs).DoCommand(sp);
	MachineSetDispenceTimeCommand(DISPENCETIME_BEFORE, state.dispenceState.beforeTime).DoCommand(sp);
	MachineSetDispenceTimeCommand(DISPENCETIME_AFTER, state.dispenceState.afterTime).DoCommand(sp);
	MachineSetDispenceTimeCommand(DISPENCETIME_SUCKBACK, state.dispenceState.suckBackTime).DoCommand(sp);

	// Set pick:
	MachineSetPickTimeCommand(PICKTIME_AFTER_PICK, state.pickState.afterPickTime).DoCommand(sp);
	MachineSetPickTimeCommand(PICKTIME_AFTER_PLACE, state.pickState.afterPlaceTime).DoCommand(sp);
	MachineSetPickTimeCommand(PICKTIME_PRESS_PICK, state.pickState.pickPressDownTime).DoCommand(sp);
	MachineSetPickTimeCommand(PICKTIME_PRESS_PLACE, state.pickState.placePressDownTime).DoCommand(sp);

	// Set brightness:
	MachineLightBrightnessCommand(LAMP_CAMERA, state.lampCameraBrightness).DoCommand(sp);
	MachineLightBrightnessCommand(LAMP_LOOKUP, state.lampLookupBrightness).DoCommand(sp);

	return true;
}

MachineGotoStateCommand* MachineGotoStateCommand::Copy()
{
	return new MachineGotoStateCommand(m_state, m_initialize);
}