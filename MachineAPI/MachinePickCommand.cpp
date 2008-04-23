#include "MachinePickCommand.h"
#include "MachineCommands.h"
#include "Axis.h"

#include <iostream>
using namespace std;

#define COMMAND_STRING	"Machine Pick Command"

MachinePickCommand::MachinePickCommand(PickCommandType cmd)
{
	m_cmd = cmd;
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
	m_oldZ = oldms.GetState().z;
	return oldms;
}

bool MachinePickCommand::HasNextState()
{
	return false;
}


bool MachinePickCommand::DoCommand(SerialPort &sp)
{
	char heightStr[6];
	ExecCommand(sp, M_READY_1915, M_ANS_1);
	switch (m_cmd) {
		case (PICKCMD_PICK):
			// Set the height of the tool
			ExecCommand(sp, "WR DM320 33792", M_ANS_OK);
			cout << "WR DM321 0" <<endl;
			ExecCommand(sp, "WR DM321 9200", M_ANS_OK); // 8985
			cout << "WR DM71 2" << endl;
			ExecCommand(sp, "WR DM71 2", M_ANS_OK);
			cout << "WR DM70 320"<< endl;
			ExecCommand(sp, "WR DM70 320", M_ANS_OK);
			ExecCommand(sp, "RD 1515", M_ANS_1);

			ExecCommand(sp, "ST 1907", M_ANS_OK);
			break;

		case (PICKCMD_PLACE):
			// Set height?
			ExecCommand(sp, "WR DM320 34048", M_ANS_OK);
			ExecCommand(sp, "WR DM321 8985", M_ANS_OK);
			ExecCommand(sp, "WR DM71 2", M_ANS_OK);
			ExecCommand(sp, "WR DM70 320", M_ANS_OK);
			ExecCommand(sp, "RD 1915", M_ANS_1);

			ExecCommand(sp, "ST 1614", M_ANS_OK);
			ExecCommand(sp, M_READY_1915, M_ANS_1);
			ExecCommand(sp, "ST 1914", M_ANS_OK);
			break;

		case (PICKCMD_DROP):
			ExecCommand(sp, "RS 1912", M_ANS_OK);
			ExecCommand(sp, M_READY_1915, M_ANS_1);
			ExecCommand(sp, "RS 702", M_ANS_OK);
			ExecCommand(sp, M_READY_1915, M_ANS_1);
			ExecCommand(sp, "RS 703", M_ANS_OK);

			break;
	}
	ExecCommand(sp, M_READY_1915, M_ANS_1);
	MachineMoveAbsoluteCommand(AXIS_Z, m_oldZ).DoCommand(sp);
	return true;
}

MachinePickCommand* MachinePickCommand::Copy()
{
	return new MachinePickCommand(m_cmd);
}