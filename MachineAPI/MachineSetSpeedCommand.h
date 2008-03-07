#ifndef __MACHINESETSPEEDCOMMAND_H__
#define __MACHINESETSPEEDCOMMAND_H__

#include "MachineCommand.h"
#include "MachineState.h"

class MachineSetSpeedCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachineSetSpeedCommand(int speed);
	~MachineSetSpeedCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
private:
	bool DoCommand(SerialPort &sp);
	MachineSetSpeedCommand* Copy();
	int m_speed;
};

#endif // __MACHINESETSPEEDCOMMAND_H__