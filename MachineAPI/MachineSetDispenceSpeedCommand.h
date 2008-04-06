#ifndef __MachineSetDispenceSpeedCommand_H__
#define __MachineSetDispenceSpeedCommand_H__

#include "MachineCommand.h"
#include "MachineState.h"

class MachineSetDispenceSpeedCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachineSetDispenceSpeedCommand(int speed);
	~MachineSetDispenceSpeedCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool IsValid()
	{
		return true;
	}

private:
	bool DoCommand(SerialPort &sp);
	MachineSetDispenceSpeedCommand* Copy();
	int m_speed;
};

#endif // __MachineSetDispenceSpeedCommand_H__