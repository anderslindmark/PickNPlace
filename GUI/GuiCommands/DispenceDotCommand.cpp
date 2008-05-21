
#include "DispenceDotCommand.h"

namespace PicknPlaceGui
{
	DispenceDotCommand::DispenceDotCommand(int x, int y, DispenceStateStruct settings)
	{
		m_x = x;
		m_y = y;
		m_cmd = NULL;
		m_settings = settings;
	}

	DispenceDotCommand::~DispenceDotCommand(void)
	{
		delete m_cmd;
	}

	MachineWrapperCommand& DispenceDotCommand::GetMachineCommand()
	{
		delete m_cmd;
		m_cmd = new MachineWrapperCommand(false);
		m_cmd->Add(MachineSetDispenceTimeCommand(DISPENCETIME_AFTER, m_settings.afterTime));
		m_cmd->Add(MachineSetDispenceTimeCommand(DISPENCETIME_BEFORE, m_settings.beforeTime));
		m_cmd->Add(MachineSetDispenceTimeCommand(DISPENCETIME_SUCKBACK, m_settings.suckBackTime));
		m_cmd->Add(MachineSetDispenceOffsetCommand(OFFSET_Z, m_settings.offsetZ));
		m_cmd->Add(MachineSetDispenceOffsetCommand(OFFSET_ZS, m_settings.offsetZs));
		m_cmd->Add(MachineDotDispenceCommand(m_x, m_y));
		return *m_cmd;
	}

	void DispenceDotCommand::SetX(int x)
	{
		m_x = x;
	}

	void DispenceDotCommand::SetY(int y)
	{
		m_y = y;
	}

	void DispenceDotCommand::SetCoordinate(Coordinate2D coord)
	{
		m_x = coord.x;
		m_y = coord.y;
	}

	Coordinate2D DispenceDotCommand::GetCoordinate()
	{
		return Coordinate2D(m_x, m_y);
	}

	int DispenceDotCommand::GetSize()
	{
		return (m_settings.beforeTime+m_settings.afterTime);
	}

	DispenceStateStruct DispenceDotCommand::GetSettings()
	{
		return m_settings;
	}

	void DispenceDotCommand::SetSettings(DispenceStateStruct settings)
	{
		m_settings = settings;
	}

	QString DispenceDotCommand::toString()
	{
		return QString("Dispense dot command");
	}
}