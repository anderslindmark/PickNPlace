/**
 	\file MachineMovePolygonCommand.cpp
 
 	\brief
 	Source file for the MachineMovePolygonCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/


#include "MachineMovePolygonCommand.h"
#include "MachineCommands.h"
#include "Axis.h"

#define COMMAND_STRING	"Machine Move Polygon Command"

MachineMovePolygonCommand::MachineMovePolygonCommand(MachinePolygon polygon) : m_polygon(polygon)
{
	m_vectorIndex = 0;
	ValidatePolygon();
}

MachineMovePolygonCommand::MachineMovePolygonCommand()
{
	m_vectorIndex = 0;
	m_valid = true;
}

MachineMovePolygonCommand::~MachineMovePolygonCommand(void)
{
}

string MachineMovePolygonCommand::ToString()
{
	return string(COMMAND_STRING);
}

MachineState MachineMovePolygonCommand::GetAfterState(MachineState &oldms)
{
	MachinePolygonPoint pp = m_polygon.GetPoint(m_vectorIndex);
	MachineStateStruct mss = oldms.GetState();
	mss.x = pp.x;
	mss.y = pp.y;
	return MachineState(mss);
}

bool MachineMovePolygonCommand::HasNextState()
{
	if (m_polygon.Size() == m_vectorIndex+1)
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

MachinePolygon MachineMovePolygonCommand::GetPolygon()
{
	return m_polygon;
}

bool MachineMovePolygonCommand::SetPolygon(MachinePolygon polygon)
{
	m_polygon = polygon;
	return ValidatePolygon();
}

bool MachineMovePolygonCommand::DoCommand(SerialPort &sp)
{
	MachinePolygonPoint pp = m_polygon.GetPoint(m_vectorIndex);
	if (m_vectorIndex == 0)
		return MachineMoveAllCommand(pp.x, pp.y, -1).DoCommand(sp);
	
	MachinePolygonPoint ppp = m_polygon.GetPoint(m_vectorIndex-1);
	Axis axis;
	int pos;
	if (ppp.x == pp.x)
	{
		axis = AXIS_Y;
		pos = pp.y;
	}
	else
	{
		axis = AXIS_X;
		pos = pp.x;
	}
	MachineMoveAbsoluteCommand moveCmd(axis, pos);
	
	return moveCmd.DoCommand(sp);
}

bool MachineMovePolygonCommand::IsValid()
{
	return m_valid;
}


MachineMovePolygonCommand* MachineMovePolygonCommand::Copy()
{
	return new MachineMovePolygonCommand(m_polygon);
}

bool MachineMovePolygonCommand::ValidatePolygon()
{
	if (m_polygon.Size() == 0)
	{
		m_valid = true;
		return m_valid;
	}

	MachinePolygonPoint pp = m_polygon.GetPoint(0);
	for (int i = 1; i < m_polygon.Size(); i++)
	{
		MachinePolygonPoint pp2 = m_polygon.GetPoint(i);
		// Check that it is a straight line in one axis
		if (! (pp.x == pp2.x || pp.y == pp2.y) )
		{
			m_valid = false;
			return m_valid;
		}

		pp = pp2;
	}

	m_valid = true;
	return m_valid;
}
