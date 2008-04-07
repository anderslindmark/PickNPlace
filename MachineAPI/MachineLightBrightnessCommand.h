#ifndef __MachineLightBrightnessCommand_H__
#define __MachineLightBrightnessCommand_H__

#include "MachineCommand.h"
#include "MachineState.h"

enum Lamp
{
	LAMP_CAMERA,
	LAMP_LOOKUP
};

class MachineLightBrightnessCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachineLightBrightnessCommand(Lamp lamp, int brightness); // 0..15
	~MachineLightBrightnessCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool IsValid()
	{
		return true;
	}

private:
	bool DoCommand(SerialPort &sp);
	MachineLightBrightnessCommand* Copy();

	Lamp m_lamp;
	int m_brightness;
};

#endif // __MachineLightBrightnessCommand_H__
