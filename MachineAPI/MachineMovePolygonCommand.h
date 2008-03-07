
#ifndef __MACHINEMOVEPOLYGONCOMMAND_H__
#define __MACHINEMOVEPOLYGONCOMMAND_H__

#include "MachineCommand.h"
#include "MachinePolygon.h"

class MachineMovePolygonCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachineMovePolygonCommand(MachinePolygon polygon);
	~MachineMovePolygonCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool HasNextState();

private:
	bool DoCommand(SerialPort &sp);
	MachineMovePolygonCommand *Copy();

	MachinePolygon m_polygon;
	int m_vectorIndex;
};


#endif // __MACHINEMOVEPOLYGONCOMMAND_H__

