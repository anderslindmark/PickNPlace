#ifndef __DISPENCEPOLYGONCOMMAND_H__
#define __DISPENCEPOLYGONCOMMAND_H__

#include "MachinePolygon.h"
#include "MachineCommands.h"

namespace PicknPlaceGui
{
	class DispencePolygonCommand : public MachinePolygon
	{
	public:
		DispencePolygonCommand(DispenceStateStruct settings);
		~DispencePolygonCommand(void);
		MachineWrapperCommand& GetMachineCommand();
		int GetSpeed();
		void SetSpeed(int speed);
		DispenceStateStruct GetSettings();
		void SetSettings(DispenceStateStruct settings);

	private:
		DispenceStateStruct m_settings;
		MachineWrapperCommand *m_cmd;
	};
}
#endif // __DISPENCEPOLYGONCOMMAND_H__