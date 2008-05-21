
#ifndef __DISPENCEPOLYGONCOMMAND_H__
#define __DISPENCEPOLYGONCOMMAND_H__

#include "MachinePolygon.h"
#include "MachineCommands.h"
#include "GuiMachineCommand.h"

namespace PicknPlaceGui
{
	class DispencePolygonCommand : public MachinePolygon, public GuiMachineCommand
	{
	public:
		DispencePolygonCommand();
		DispencePolygonCommand(const DispencePolygonCommand &cmd);
		DispencePolygonCommand(DispenceStateStruct settings);
		~DispencePolygonCommand(void);
		MachineWrapperCommand& GetMachineCommand();
		int GetSpeed();
		void SetSpeed(int speed);
		DispenceStateStruct GetSettings();
		void SetSettings(DispenceStateStruct settings);
		void isNull();

	private:
		bool m_isNull;
		DispenceStateStruct m_settings;
		MachineWrapperCommand *m_cmd;
	};
}
#endif // __DISPENCEPOLYGONCOMMAND_H__
