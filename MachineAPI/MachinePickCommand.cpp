/**
 	\file MachinePickCommand.cpp
 
 	\brief
 	Source file for the MachinePickCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/


#include "MachinePickCommand.h"
#include "MachineCommands.h"
#include "Axis.h"

#include <iostream>
using namespace std;

#define COMMAND_STRING	"Machine Pick Command"

MachinePickCommand::MachinePickCommand(PickCommandType cmd, int componentX, int componentY, float angle)
{
	m_x = componentX;
	m_y = componentY;
	m_cmd = cmd;
	m_firstState = true;
	m_angle = angle;
}

MachinePickCommand::~MachinePickCommand(void)
{
}

string MachinePickCommand::ToString()
{
	return string(COMMAND_STRING);
}

MachineState MachinePickCommand::GetAfterState(MachineState &oldms)
{
	m_state = oldms.GetState();
	m_state.x = m_x - m_state.pickState.offsetX;
	m_state.y = m_y - m_state.pickState.offsetY;
	m_state.rot = m_angle;
	
	return MachineState(m_state);
}

bool MachinePickCommand::HasNextState()
{
	return false;
}


bool MachinePickCommand::DoCommand(SerialPort &sp)
{
	PickStateStruct pickState = m_state.pickState;
	char cmdStr[20];
	int height;
	ExecCommand(sp, M_READY_1915, M_ANS_1);
	switch (m_cmd) {
		case (PICKCMD_PICK):
			// Move the pick head over the component
			MachineMoveAbsoluteCommand(AXIS_Z, 0).DoCommand(sp);
			MachineMoveAllCommand(m_state.x, m_state.y, -1).DoCommand(sp);
			MachineRotateAbsoluteCommand(m_angle).DoCommand(sp);
			// Set the height
			height = ROUND( (TOOL_MOUNT_MAX_Z - pickState.headHeight - pickState.pickHeight)/STEP_PRECISION_Z );
			sprintf_s(cmdStr, sizeof(cmdStr), "WR DM321 %d", height);
			ExecCommand(sp, "WR DM320 33792", M_ANS_OK);
			ExecCommand(sp, cmdStr, M_ANS_OK);
			ExecCommand(sp, "WR DM71 2", M_ANS_OK);
			ExecCommand(sp, "WR DM70 320", M_ANS_OK);
			ExecCommand(sp, "RD 1515", M_ANS_1);

			// Pick
			ExecCommand(sp, "ST 1907", M_ANS_OK);
			break;

		case (PICKCMD_PLACE):
			// Set height
			MachineMoveAbsoluteCommand(AXIS_Z, 0).DoCommand(sp);
			MachineMoveAllCommand(m_state.x, m_state.y, -1).DoCommand(sp);
			MachineRotateAbsoluteCommand(m_angle).DoCommand(sp);
			height = ROUND( (TOOL_MOUNT_MAX_Z - pickState.headHeight - pickState.placeHeight)/STEP_PRECISION_Z );
			sprintf_s(cmdStr, sizeof(cmdStr), "WR DM321 %d", height);
			ExecCommand(sp, "WR DM320 34048", M_ANS_OK);
			ExecCommand(sp, cmdStr, M_ANS_OK);
			ExecCommand(sp, "WR DM71 2", M_ANS_OK);
			ExecCommand(sp, "WR DM70 320", M_ANS_OK);
			ExecCommand(sp, "RD 1915", M_ANS_1);

			// Place	
			ExecCommand(sp, "ST 1614", M_ANS_OK);
			ExecCommand(sp, M_READY_1915, M_ANS_1);
			ExecCommand(sp, "ST 1914", M_ANS_OK);
			break;

		case (PICKCMD_DROP):
			MachineMoveAbsoluteCommand(AXIS_Z, 0).DoCommand(sp);
			MachineMoveAllCommand(m_state.x, m_state.y, -1).DoCommand(sp);
			MachineRotateAbsoluteCommand(m_angle).DoCommand(sp);
			ExecCommand(sp, "RS 1912", M_ANS_OK);
			ExecCommand(sp, M_READY_1915, M_ANS_1);
			ExecCommand(sp, "RS 702", M_ANS_OK);
			ExecCommand(sp, M_READY_1915, M_ANS_1);
			ExecCommand(sp, "RS 703", M_ANS_OK);
			break;
	}
	ExecCommand(sp, M_READY_1915, M_ANS_1);
	MachineMoveAbsoluteCommand(AXIS_Z, m_state.z).DoCommand(sp);
	return true;
}

MachinePickCommand* MachinePickCommand::Copy()
{
	return new MachinePickCommand(m_cmd, m_x, m_y, m_angle);
}