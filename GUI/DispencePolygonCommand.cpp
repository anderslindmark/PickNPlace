#include "DispencePolygonCommand.h"

namespace PicknPlaceGui
{
	DispencePolygonCommand::DispencePolygonCommand(void)
	{
		m_cmd = NULL;
	}

	DispencePolygonCommand::~DispencePolygonCommand(void)
	{
		delete m_cmd;
	}

	MachineWrapperCommand& DispencePolygonCommand::GetMachineCommand()
	{
		delete m_cmd;
		m_cmd = new MachineWrapperCommand(false);
		m_cmd->Add(MachineSetDispenceTimeCommand(DISPENCETIME_AFTER, m_times.after));
		m_cmd->Add(MachineSetDispenceTimeCommand(DISPENCETIME_BEFORE, m_times.before));
		m_cmd->Add(MachineSetDispenceTimeCommand(DISPENCETIME_SUCKBACK, m_times.suckback));
		m_cmd->Add(MachineSetDispenceSpeedCommand(m_speed));
		m_cmd->Add(MachinePolygonDispenceCommand(*this));
		return *m_cmd;
	}

	void DispencePolygonCommand::SetSpeed(int speed)
	{
		m_speed = speed;
	}

	int DispencePolygonCommand::GetSpeed()
	{
		return m_speed;
	}

	DPCTimes DispencePolygonCommand::GetTimes()
	{
		return m_times;
	}

	void DispencePolygonCommand::SetTimes(DPCTimes times)
	{
		m_times = times;
	}
}