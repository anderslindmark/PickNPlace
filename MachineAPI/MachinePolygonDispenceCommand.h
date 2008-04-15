
#ifndef __MachinePolygonDispenceCommand_H__
#define __MachinePolygonDispenceCommand_H__

#include "MachineCommand.h"
#include "MachinePolygon.h"

class MachinePolygonDispenceCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachinePolygonDispenceCommand(MachinePolygon polygon);
	MachinePolygonDispenceCommand();
	~MachinePolygonDispenceCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool HasNextState();
	MachinePolygon GetPolygon();
	bool SetPolygon(MachinePolygon polygon);
	bool IsValid();

private:
	bool DoCommand(SerialPort &sp);
	MachinePolygonDispenceCommand *Copy();
	bool ValidatePolygon();
	void dispenceLine(SerialPort &sp, MachinePolygonPoint from, MachinePolygonPoint to);
	void moveOffset(SerialPort &sp, MachinePolygonPoint oldPp, MachinePolygonPoint pp);
	MachinePolygon m_polygon;
	int m_vectorIndex;
	bool m_valid;
	MachineStateStruct m_state;
	MachineStateStruct m_tempState;
};


#endif // __MachinePolygonDispenceCommand_H__

