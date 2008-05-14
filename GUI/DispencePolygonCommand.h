#ifndef __DISPENCEPOLYGONCOMMAND_H__
#define __DISPENCEPOLYGONCOMMAND_H__

#include "MachinePolygon.h"
#include "MachineCommands.h"

namespace PicknPlaceGui
{
	struct DPCTimes
	{
		int before;
		int after;
		int suckback;
		DPCTimes() : before(0), after(0), suckback(0) {};
	};

	class DispencePolygonCommand : public MachinePolygon
	{
	public:
		DispencePolygonCommand(void);
		~DispencePolygonCommand(void);
		MachineWrapperCommand& GetMachineCommand();
		void SetSpeed(int speed);
		int GetSpeed();
		DPCTimes GetTimes();
		void SetTimes(DPCTimes times);

	private:
		int m_speed;
		DPCTimes m_times;
		MachineWrapperCommand *m_cmd;
	};
}
#endif // __DISPENCEPOLYGONCOMMAND_H__