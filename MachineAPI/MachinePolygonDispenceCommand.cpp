#include "MachinePolygonDispenceCommand.h"
#include "MachineCommands.h"
#include "Axis.h"

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
	}
	else if (m_vectorIndex == m_polygon.Size())
	{
		return MachineState(m_state);
	}
	MachinePolygonPoint pp = m_polygon.GetPoint(m_vectorIndex);
	MachineStateStruct mss = oldms.GetState();
	mss.x = pp.x+m_state.dispenceState.offsetX;
	mss.y = pp.y+m_state.dispenceState.offsetY;
	return MachineState(mss);
}

bool MachinePolygonDispenceCommand::HasNextState()
{
	if (m_polygon.Size() == m_vectorIndex)
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
			MachineMoveAllCommand(startPp.x+m_state.dispenceState.offsetX, startPp.y+m_state.dispenceState.offsetY, -1).DoCommand(sp);
			ExecCommand(sp, "RS 1613", M_ANS_OK); // Set line dispence mode
			// MachineMoveAbsoluteCommand(AXIS_Z, m_state.dispenceState.offsetZ).DoCommand(sp); // Not needed
			MachineMoveNeedleCommand(NEEDLEMOVEMENT_DOWN).DoCommand(sp);
		}
		else if (m_vectorIndex+1 == m_polygon.Size()) // Last step, set suckback etc
		{
			MachinePolygonPoint oldPp = m_polygon.GetPoint(m_vectorIndex-1);
			MachinePolygonPoint pp = m_polygon.GetPoint(m_vectorIndex);
			// Set after/suckback time to the real values
			MachineSetDispenceTimeCommand(DISPENCETIME_AFTER, m_state.dispenceState.afterTime).DoCommand(sp);
			MachineSetDispenceTimeCommand(DISPENCETIME_SUCKBACK, m_state.dispenceState.suckBackTime).DoCommand(sp);

			dispenceLine(sp, oldPp, pp);

			MachineSetDispenceTimeCommand(DISPENCETIME_BEFORE, m_state.dispenceState.beforeTime).DoCommand(sp);
		}
		else if (m_vectorIndex == m_polygon.Size()) // Everything is done, return to home-position
		{
			MachineMoveNeedleCommand(NEEDLEMOVEMENT_UP).DoCommand(sp);
			MachineSetDispenceSpeedCommand(m_state.dispenceState.speed).DoCommand(sp); // Set normal speed incase last line was Y-line
			MachineMoveAbsoluteCommand(AXIS_Z, m_state.z).DoCommand(sp);
			MachineMoveAllCommand(m_state.x, m_state.y, -1).DoCommand(sp);
		}
		else
		{
			MachinePolygonPoint oldPp = m_polygon.GetPoint(m_vectorIndex-1);
			MachinePolygonPoint pp = m_polygon.GetPoint(m_vectorIndex);

			dispenceLine(sp, oldPp, pp);
			
			if (m_vectorIndex == 1)
			{
				MachineSetDispenceTimeCommand(DISPENCETIME_BEFORE, 0).DoCommand(sp); // No delays between lines in the polygon
			}
		}
	} while (HasNextState());
	return true;
}

void MachinePolygonDispenceCommand::dispenceLine(SerialPort sp, MachinePolygonPoint from, MachinePolygonPoint to)
{
	char cmdStr[15];
	int length;
	if (from.x == to.x)	// Y-line
	{
		// Double speed (Y moves half as fast as X)
		MachineSetDispenceSpeedCommand(m_state.dispenceState.speed*2).DoCommand(sp);
		length = abs(to.y - from.y);
		length = (int)floor(length/STEP_PRECISION_Y + 0.5);
		sprintf_s(cmdStr, sizeof(cmdStr), "WR DM215 %d", length); // Set y-length of dispence to ...
		ExecCommand(sp, cmdStr, M_ANS_OK); // Set dispence-length
		ExecCommand(sp, "WR DM213 0",	M_ANS_OK); // Set x-length of dispence to 0
	}
	else	// X-line
	{
		// Set normal speed
		MachineSetDispenceSpeedCommand(m_state.dispenceState.speed).DoCommand(sp);
		length = abs(to.x - from.x);
		length = (int)floor(length/STEP_PRECISION_X + 0.5);
		sprintf_s(cmdStr, sizeof(cmdStr), "WR DM213 %d", length); 
		ExecCommand(sp, cmdStr, M_ANS_OK); // Set dispence-length	
		ExecCommand(sp, "WR DM215 0",	M_ANS_OK); // Set y-length of dispence to 0
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