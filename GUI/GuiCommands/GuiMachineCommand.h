
#ifndef __GUIMACHINECOMMAND_H__
#define __GUIMACHINECOMMAND_H__

#include "MachinePolygon.h"
#include "MachineCommands.h"
#include <QString>

namespace PicknPlaceGui
{
	class GuiMachineCommand
	{
	public:
		virtual QString toString() = 0;
		virtual MachineWrapperCommand& GetMachineCommand() = 0;
	};
}

#endif // __GUIMACHINECOMMAND_H__

