#include "MachineLightBrightnessCommand.h"
#include <iostream>

#define COMMAND_STRING "Machine Set Lamp Brightness Command"

MachineLightBrightnessCommand::MachineLightBrightnessCommand(Lamp lamp, int brightness)
{
	m_lamp = lamp;
	m_brightness = brightness;
}

MachineLightBrightnessCommand::~MachineLightBrightnessCommand(void)
{
}

string MachineLightBrightnessCommand::ToString()
{
	return string(COMMAND_STRING);
}

MachineState MachineLightBrightnessCommand::GetAfterState(MachineState &oldms)
{
	MachineStateStruct mss = oldms.GetState();
	switch (m_lamp)
	{
		case (LAMP_CAMERA):
			mss.lampCameraBrightness = m_brightness;
			break;
		case (LAMP_LOOKUP):
			mss.lampLookupBrightness = m_brightness;
			break;
	}
	return MachineState(mss);
}


bool MachineLightBrightnessCommand::DoCommand(SerialPort &sp)
{
	char regStr[6];
	char cmdStr[15];
	switch (m_lamp)
	{
		case (LAMP_CAMERA):
			sprintf_s(regStr, sizeof(regStr), "DM402");
			break;
		case (LAMP_LOOKUP):
			sprintf_s(regStr, sizeof(regStr), "DM401");
			break;
	}

	sprintf_s(cmdStr, sizeof(cmdStr), "WR %s %d", regStr, m_brightness);
	ExecCommand(sp, cmdStr, M_ANS_OK);

	return true;
}

MachineLightBrightnessCommand* MachineLightBrightnessCommand::Copy()
{
	return new MachineLightBrightnessCommand(m_lamp, m_brightness);
}