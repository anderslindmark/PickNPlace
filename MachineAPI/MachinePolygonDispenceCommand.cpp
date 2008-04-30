/**
 	\file MachinePolygonDispenceCommand.cpp
 
 	\brief
 	Source file for the MachinePolygonDispenceCommand class.

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#include "MachinePolygonDispenceCommand.h"
#include "MachineCommands.h"
#include "Axis.h"

#include <iostream>
using namespace std;

#define COMMAND_STRING	"Machine Dispence Polygon Command"

MachinePolygonDispenceCommand::MachinePolygonDispenceCommand(MachinePolygon polygon) : m_polygon(polygon)
{
	m_vectorIndex = 0;
	ValidatePolygon();
}

MachinePolygonDispenceCommand::MachinePolygonDispenceCommand()
{
	m_vectorIndex = 0;
	m_valid = true;
}

MachinePolygonDispenceCommand::~MachinePolygonDispenceCommand(void)
{
}

string MachinePolygonDispenceCommand::ToString()
{
	return string(COMMAND_STRING);
}

MachineState MachinePolygonDispenceCommand::GetAfterState(MachineState &oldms)
{
	if (m_vectorIndex == 0)
	{
		m_state = oldms.GetState();
		m_tempState = m_state;
	}
	//else if (m_vectorIndex == m_polygon.Size())
	//{
	//	return MachineState(m_state);
	//}
	MachinePolygonPoint pp = m_polygon.GetPoint(m_vectorIndex);
	MachineStateStruct mss = oldms.GetState();
	mss.x = pp.x+m_state.dispenceState.offsetX;
	mss.y = pp.y+m_state.dispenceState.offsetY;
	return MachineState(mss);
}

bool MachinePolygonDispenceCommand::HasNextState()
{
	if (m_polygon.Size()-1 == m_vectorIndex)
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

MachinePolygon MachinePolygonDispenceCommand::GetPolygon()
{
	return m_polygon;
}

bool MachinePolygonDispenceCommand::SetPolygon(MachinePolygon polygon)
{
	m_polygon = polygon;
	return ValidatePolygon();
}

bool MachinePolygonDispenceCommand::DoCommand(SerialPort &sp)
{
	do 
	{
		if (m_vectorIndex == 0)
		{
			MachineSetDispenceTimeCommand(DISPENCETIME_AFTER, 0).DoCommand(sp);	// Set after times to 0 for all but the last polygon
			MachineSetDispenceTimeCommand(DISPENCETIME_SUCKBACK, 0).DoCommand(sp); // No suckback between polygon points
			MachinePolygonPoint startPp = m_polygon.GetPoint(0);
			MachineMoveAbsoluteCommand(AXIS_Z, 0).DoCommand(sp);
			MachineMoveAllCommand(startPp.x - m_state.dispenceState.offsetX, startPp.y - m_state.dispenceState.offsetY, -1).DoCommand(sp);
			// Update local state
			m_tempState.x = startPp.x + m_state.dispenceState.offsetX;
			m_tempState.y = startPp.y + m_state.dispenceState.offsetY;
			ExecCommand(sp, "RS 1613", M_ANS_OK); // Set line dispence mode
			// MachineMoveAbsoluteCommand(AXIS_Z, m_state.dispenceState.offsetZ).DoCommand(sp); // Not needed
			MachineMoveNeedleCommand(NEEDLEMOVEMENT_DOWN).DoCommand(sp);
		}
		else if (m_vectorIndex == m_polygon.Size()-1) // Last step, set suckback etc
		{
			MachinePolygonPoint oldPp = m_polygon.GetPoint(m_vectorIndex-1);
			MachinePolygonPoint pp = m_polygon.GetPoint(m_vectorIndex);
			// Set after/suckback time to the real values
			MachineSetDispenceTimeCommand(DISPENCETIME_AFTER, m_state.dispenceState.afterTime).DoCommand(sp);
			MachineSetDispenceTimeCommand(DISPENCETIME_SUCKBACK, m_state.dispenceState.suckBackTime).DoCommand(sp);

			moveOffset(sp, oldPp, pp);
			dispenceLine(sp, oldPp, pp);

			MachineSetDispenceTimeCommand(DISPENCETIME_BEFORE, m_state.dispenceState.beforeTime).DoCommand(sp);
			
			MachineMoveNeedleCommand(NEEDLEMOVEMENT_UP).DoCommand(sp);
			MachineSetDispenceSpeedCommand(m_state.dispenceState.speed).DoCommand(sp); // Set normal speed incase last line was Y-line
		}
		else
		{
			MachinePolygonPoint oldPp = m_polygon.GetPoint(m_vectorIndex-1);
			MachinePolygonPoint pp = m_polygon.GetPoint(m_vectorIndex);

			if (m_vectorIndex > 1)
			{
				moveOffset(sp, oldPp, pp);
			}

			dispenceLine(sp, oldPp, pp);
			
			if (m_vectorIndex == 1)
			{
				MachineSetDispenceTimeCommand(DISPENCETIME_BEFORE, 0).DoCommand(sp); // No delays between lines in the polygon
			}
		}
	} while (HasNextState());
	return true;
}

void MachinePolygonDispenceCommand::moveOffset(SerialPort &sp, MachinePolygonPoint oldPp, MachinePolygonPoint pp)
{
	if (m_state.dispenceState.offsetTurn != 0)
	{
		if (oldPp.x == pp.x) // Move in X
		{
			if (oldPp.y < pp.y)
			{
				MachineMoveAbsoluteCommand(AXIS_Y, m_tempState.y + m_state.dispenceState.offsetTurn, false).DoCommand(sp);
			}
			else
			{
				MachineMoveAbsoluteCommand(AXIS_Y, m_tempState.y - m_state.dispenceState.offsetTurn, false).DoCommand(sp);
			}
		}
		else
		{
			if (oldPp.x < pp.x)
			{
				MachineMoveAbsoluteCommand(AXIS_X, m_tempState.x + m_state.dispenceState.offsetTurn, false).DoCommand(sp);
			}
			else
			{
				MachineMoveAbsoluteCommand(AXIS_X, m_tempState.x - m_state.dispenceState.offsetTurn, false).DoCommand(sp);
			}
		}
	}
}

void MachinePolygonDispenceCommand::dispenceLine(SerialPort &sp, MachinePolygonPoint from, MachinePolygonPoint to)
{
	char cmdStr[15];
	int length;
	if (from.x == to.x)	// Y-line
	{
		from.y -= m_state.dispenceState.offsetTurn; // Make room for the "anti-blob" move

		// Double speed (Y moves half as fast as X)
		MachineSetDispenceSpeedCommand(m_state.dispenceState.speed*2).DoCommand(sp);
		length = abs(to.y - from.y);
		length = ROUND(length/STEP_PRECISION_Y);
		sprintf_s(cmdStr, sizeof(cmdStr), "WR DM215 %d", length); // Set y-length of dispence to ...
		ExecCommand(sp, cmdStr, M_ANS_OK); // Set dispence-length
		ExecCommand(sp, "WR DM213 0",	M_ANS_OK); // Set x-length of dispence to 0

		m_tempState.y += to.y - from.y; // Update local state information
	}
	else	// X-line
	{
		from.x -= m_state.dispenceState.offsetTurn;

		// Set normal speed
		MachineSetDispenceSpeedCommand(m_state.dispenceState.speed).DoCommand(sp);
		length = abs(to.x - from.x);
		length = ROUND(length/STEP_PRECISION_X);
		sprintf_s(cmdStr, sizeof(cmdStr), "WR DM213 %d", length); 
		ExecCommand(sp, cmdStr, M_ANS_OK); // Set dispence-length	
		ExecCommand(sp, "WR DM215 0",	M_ANS_OK); // Set y-length of dispence to 0

		m_tempState.x += to.x - from.x;
	}
	

	if (to.x < from.x || to.y < from.y) // Backa
	{
		ExecCommand(sp, "ST 1909", M_ANS_OK);
	}
	else
	{
		ExecCommand(sp, "ST 1908", M_ANS_OK);
	}

	ExecCommand(sp, M_READY_1915, M_ANS_1);
}

bool MachinePolygonDispenceCommand::IsValid()
{
	return m_valid;
}


MachinePolygonDispenceCommand* MachinePolygonDispenceCommand::Copy()
{
	return new MachinePolygonDispenceCommand(m_polygon);
}

bool MachinePolygonDispenceCommand::ValidatePolygon()
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