#ifndef __MACHINEDOTDISPENCECOMMAND_H__
#define __MACHINEDOTDISPENCECOMMAND_H__
#include "machinecommand.h"

class MachineDotDispenceCommand :
	public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachineDotDispenceCommand();
	~MachineDotDispenceCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool HasNextState();
	bool IsValid()
	{
		return true;
	}

private:
	MachineDotDispenceCommand *Copy();
	bool DoCommand(SerialPort &sp);

	MachineStateStruct m_state;
	bool m_moreStates;

};

#endif // __MACHINEDOTDISPENCECOMMAND_H__
