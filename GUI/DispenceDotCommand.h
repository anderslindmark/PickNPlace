#ifndef __DISPENCEDOTCOMMAND_H__
#define __DISPENCEDOTCOMMAND_H__

#include "DispencePolygonCommand.h"
#include "MachineCommands.h"
#include "Coordinate.h"

namespace PicknPlaceGui
{
	class DispenceDotCommand
	{
	public:
		DispenceDotCommand(int x, int y, DispenceStateStruct settings);
		~DispenceDotCommand(void);
		MachineWrapperCommand& GetMachineCommand();
		void SetX(int x);
		void SetY(int y);
		void SetCoordinate(Coordinate2D coord);
		Coordinate2D GetCoordinate();
		int GetSize();
		DispenceStateStruct GetSettings();
		void SetSettings(DispenceStateStruct settings);

	private:
		int m_x;
		int m_y;
		DispenceStateStruct m_settings;
		MachineWrapperCommand *m_cmd;
	};
}


#endif // __DISPENCEDOTCOMMAND_H__