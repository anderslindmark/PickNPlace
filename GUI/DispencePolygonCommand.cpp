#include "DispencePolygonCommand.h"

namespace PicknPlaceGui
{
	DispencePolygonCommand::DispencePolygonCommand(DispenceStateStruct settings)
	{
		m_settings = settings;
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
		m_cmd->Add(MachineSetDispenceTimeCommand(DISPENCETIME_AFTER, m_settings.afterTime));
		m_cmd->Add(MachineSetDispenceTimeCommand(DISPENCETIME_BEFORE, m_settings.beforeTime));
		m_cmd->Add(MachineSetDispenceTimeCommand(DISPENCETIME_SUCKBACK, m_settings.suckBackTime));
		m_cmd->Add(MachineSetDispenceOffsetCommand(OFFSET_Z, m_settings.offsetZ));
		m_cmd->Add(MachineSetDispenceOffsetCommand(OFFSET_ZS, m_settings.offsetZs));
		m_cmd->Add(MachineSetDispenceOffsetCommand(OFFSET_TURN, m_settings.offsetTurn));
		m_cmd->Add(MachineSetDispenceSpeedCommand(m_settings.speed));
		m_cmd->Add(MachinePolygonDispenceCommand(*this));
		return *m_cmd;
	}

	void DispencePolygonCommand::SetSpeed(int speed)
	{
		m_settings.speed = speed;
	}

	int DispencePolygonCommand::GetSpeed()
	{
		return m_settings.speed;
	}

	DispenceStateStruct DispencePolygonCommand::GetSettings()
	{
		return m_settings;
	}

	void DispencePolygonCommand::SetSettings(DispenceStateStruct settings)
	{
		m_settings = settings;
	}
}