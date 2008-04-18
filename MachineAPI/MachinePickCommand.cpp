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
	return oldms;
}

bool MachinePickCommand::HasNextState()
{
	return false;
}


bool MachinePickCommand::DoCommand(SerialPort &sp)
{
	ExecCommand(sp, M_READY_1915, M_ANS_1);
	switch (m_cmd) {
		case (PICKCMD_PICK):
			ExecCommand(sp, "ST 1907", M_ANS_OK);
			break;

		case (PICKCMD_PLACE):
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
	return true;
}

MachinePickCommand* MachinePickCommand::Copy()
{
	return new MachinePickCommand(m_cmd);
}