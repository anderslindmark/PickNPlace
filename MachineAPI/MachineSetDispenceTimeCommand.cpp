#include "MachineSetDispenceTimeCommand.h"
#include <iostream>

#define COMMAND_STRING "Machine Set Time Command"
#define TIMEUNIT	0.1f

MachineSetDispenceTimeCommand::MachineSetDispenceTimeCommand(DispenceTimeType tt, int multiplier)
{
	m_tt = tt;
	m_multiplier = multiplier;
}

MachineSetDispenceTimeCommand::~MachineSetDispenceTimeCommand(void)
{
}

string MachineSetDispenceTimeCommand::ToString()
{
	return string(COMMAND_STRING);
}

MachineState MachineSetDispenceTimeCommand::GetAfterState(MachineState &oldms)
{
	MachineStateStruct mss = oldms.GetState();
	switch (m_tt)
	{
		case (DISPENCETIME_BEFORE):
			mss.dispenceState.beforeTime = m_multiplier * TIMEUNIT;
			break;
		case (DISPENCETIME_AFTER):
			mss.dispenceState.afterTime = m_multiplier * TIMEUNIT;
			break;
		case (DISPENCETIME_SUCKBACK):
			mss.dispenceState.suckBackTime = m_multiplier * TIMEUNIT;
			break;
	}
	
	return MachineState(mss);
}


bool MachineSetDispenceTimeCommand::DoCommand(SerialPort &sp)
{
	char regStr[4];
	char cmdStr[15];
	switch (m_tt)
	{
		case (DISPENCETIME_BEFORE):
			sprintf_s(regStr, sizeof(regStr), "T35");
			break;
		case (DISPENCETIME_AFTER):
			sprintf_s(regStr, sizeof(regStr), "T36");
			break;
		case (DISPENCETIME_SUCKBACK):
			sprintf_s(regStr, sizeof(regStr), "T37");
			break;
	}

	sprintf_s(cmdStr, sizeof(cmdStr), "WS %s %d", regStr, m_multiplier);
	ExecCommand(sp, cmdStr, M_ANS_OK);

	return true;
}

MachineSetDispenceTimeCommand* MachineSetDispenceTimeCommand::Copy()
{
	return new MachineSetDispenceTimeCommand(m_tt, m_multiplier);
}