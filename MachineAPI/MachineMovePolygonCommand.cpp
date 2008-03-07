#include "MachineMovePolygonCommand.h"
#include "MachineMoveAbsoluteCommand.h"

#define MOVE_POLYGON_COMMAND_STRING	"Machine Move Polygon Command"

MachineMovePolygonCommand::MachineMovePolygonCommand(MachinePolygon polygon) : m_polygon(polygon)
{
	m_vectorIndex = 0;
}

MachineMovePolygonCommand::~MachineMovePolygonCommand(void)
{
}

string MachineMovePolygonCommand::ToString()
{
	return string(MOVE_POLYGON_COMMAND_STRING);
}

MachineState MachineMovePolygonCommand::GetAfterState(MachineState &oldms)
{
	MachineMoveAbsoluteCommand moveCmd(m_polygon.GetPoints()[m_vectorIndex].axis, m_polygon.GetPoints()[m_vectorIndex].position);
	return moveCmd.GetAfterState(oldms);
}

bool MachineMovePolygonCommand::HasNextState()
{
	if (m_polygon.GetPoints().size() == m_vectorIndex+1)
	{
		m_vectorIndex = 0;
		return false;
	}
	else
	{
		m_vectorIndex++;
		return true;
	}
}

bool MachineMovePolygonCommand::DoCommand(SerialPort &sp)
{
	MachineMoveAbsoluteCommand moveCmd(m_polygon.GetPoints()[m_vectorIndex].axis, m_polygon.GetPoints()[m_vectorIndex].position);
	return moveCmd.DoCommand(sp);
}


MachineMovePolygonCommand* MachineMovePolygonCommand::Copy()
{
	return new MachineMovePolygonCommand(m_polygon);
}

