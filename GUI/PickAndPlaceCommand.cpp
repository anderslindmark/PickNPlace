#include "PickAndPlaceCommand.h"
#include <math.h>
#include <iostream>
using namespace std;

#define PI 3.14159265f
#define ROUND(x) floor(x+0.5)

namespace PicknPlaceGui
{
	PickAndPlaceCommand::PickAndPlaceCommand(Coordinate2D pickOrientTL,
						Coordinate2D pickOrientTR,
						Coordinate2D pickOrientBR,
						int pickZ,
						Coordinate2D placeOrientTL,
						Coordinate2D placeOrientTR,
						Coordinate2D placeOrientBR,
						int placeZ)
	{
		CalcCoordinate(	pickOrientTL,
						pickOrientTR,
						pickOrientBR,
						m_pick,
						m_pickAngle);
		m_pick.z = pickZ;
		CalcCoordinate(	placeOrientTL,
						placeOrientTR,
						placeOrientBR,
						m_place,
						m_placeAngle);
		m_place.z = placeZ;
		Init();
	}

	PickAndPlaceCommand::PickAndPlaceCommand(int pickX, int pickY, int pickZ, float pickAngle,
						int placeX, int placeY, int placeZ, float placeAngle)
	{
		m_pick = Coordinate3D(pickX, pickY, pickZ);
		m_pickAngle = pickAngle;
		m_place = Coordinate3D(placeX, placeY, placeZ);
		m_placeAngle = placeAngle;
		Init();
	}

	PickAndPlaceCommand::~PickAndPlaceCommand(void)
	{
		delete m_cmd;
	}

	void PickAndPlaceCommand::Init()
	{
		m_cmd = NULL;
	}
	
	void PickAndPlaceCommand::SetTimes(PAPCTimes times)
	{
		m_times = times;
	}

	PAPCTimes PickAndPlaceCommand::GetTimes()
	{
		return m_times;
	}

	MachineWrapperCommand& PickAndPlaceCommand::GetMachineCommand()
	{
		delete m_cmd;
		m_cmd = new MachineWrapperCommand(false);

		// Pick parameters
		m_cmd->Add(MachineSetPickTimeCommand(PICKTIME_AFTER_PICK, m_times.afterPick);
		m_cmd->Add(MachineSetPickTimeCommand(PICKTIME_PRESS_PICK, m_times.pressPick);
		m_cmd->Add(MachineSetPickOffsetCommand(PICKOFFSET_TOOLHEIGHT, m_pick.z);
		m_cmd->Add(MachinePickCommand(PICKCMD_PICK, m_pick.x, m_pick.y);

		// Place parameters
		m_cmd->Add(MachineSetPickTimeCommand(PICKTIME_AFTER_PLACE, m_times.afterPlace);
		m_cmd->Add(MachineSetPickTimeCommand(PICKTIME_PRESS_PLACE, m_times.pressPlace);
		m_cmd->Add(MachineSetPickOffsetCommand(PICKOFFSET_TOOLHEIGHT, m_place.z);
		m_cmd->Add(MachinePickCommand(PICKCMD_PLACE, m_place.x, m_place.y);

		return *m_cmd;
	}


	void PickAndPlaceCommand::SetPickCoordinate(int x, int y, int z, float angle)
	{
		m_pick = Coordinate3D(x, y , z);
		m_pickAngle = angle;
	}

	void PickAndPlaceCommand::SetPickCoordinate(Coordinate2D pickOrientTL,
								Coordinate2D pickOrientTR,
								Coordinate2D pickOrientBR,
								int pickZ)
	{
		CalcCoordinate(	pickOrientTL,
						pickOrientTR,
						pickOrientBR,
						m_pick,
						m_pickAngle);
		m_pick.z = pickZ;
	}

	void PickAndPlaceCommand::SetPickCoordinate(Coordinate3D coordinate, float angle)
	{
		m_pick = coordinate;
		m_pickAngle = angle;
	}

	void PickAndPlaceCommand::SetPickX(int x)
	{
		m_pick.x = x;
	}

	void PickAndPlaceCommand::SetPickY(int y)
	{
		m_pick.y = y;
	}

	void PickAndPlaceCommand::SetPickZ(int z)
	{
		m_pick.z = z;
	}

	void PickAndPlaceCommand::SetPickAngle(float angle)
	{
		m_pickAngle = angle;
	}

	void PickAndPlaceCommand::SetPlaceCoordinate(int x, int y, int z, float angle)
	{
		m_place = Coordinate3D(x, y , z);
		m_placeAngle = angle;
	}

	void PickAndPlaceCommand::SetPlaceCoordinate(Coordinate2D placeOrientTL,
								Coordinate2D placeOrientTR,
								Coordinate2D placeOrientBR,
								int placeZ)
	{
		CalcCoordinate(	placeOrientTL,
						placeOrientTR,
						placeOrientBR,
						m_place,
						m_placeAngle);
		m_place.z = placeZ;
	}

	void PickAndPlaceCommand::SetPlaceCoordinate(Coordinate3D coordinate, float angle)
	{
		m_place = coordinate;
		m_placeAngle = angle;
	}

	void PickAndPlaceCommand::SetPlaceX(int x)
	{
		m_place.x = x;
	}

	void PickAndPlaceCommand::SetPlaceY(int y)
	{
		m_place.y = y;
	}

	void PickAndPlaceCommand::SetPlaceZ(int z)
	{
		m_place.z = z;
	}

	void PickAndPlaceCommand::SetPlaceAngle(float angle)
	{
		m_placeAngle = angle;
	}

	Coordinate3D PickAndPlaceCommand::GetPickCoordinate()
	{
		return m_pick;
	}

	float PickAndPlaceCommand::GetPickAngle()
	{
		return m_pickAngle;
	}
	
	Coordinate3D PickAndPlaceCommand::GetPlaceCoordinate()
	{
		return m_place;
	}

	float PickAndPlaceCommand::GetPlaceAngle()
	{
		return m_placeAngle;
	}

	void PickAndPlaceCommand::CalcCoordinate(Coordinate2D orientTL,
									Coordinate2D orientTR,
									Coordinate2D orientBR,
									Coordinate3D &coordinate,
									float &angle)
	{
		// calculate the centrum of the component
		float length = sqrt(pow(float(orientBR.x - orientTL.x), 2) + pow(float(orientBR.y - orientTL.y), 2)) / 2;
		//cout <<"DEBUG LENGTH: "<<length<<endl;

		float direction = atan2(float(abs(orientBR.y - orientTL.y)), float(abs(orientBR.x - orientTL.x)));
		//cout <<"DEBUG direction: "<<direction<<endl;
		
		if (orientTL.y <= orientBR.y && orientTL.y > orientTR.y || orientTL.y < orientBR.y  )
		{
			coordinate.x = int(ROUND(float(orientTL.x) - (length * cos(direction))));
			coordinate.y = int(ROUND(float(orientTL.y) + (length * sin(direction))));
		}
		else
		{
			coordinate.x = int(ROUND(float(orientBR.x) - (length * cos(direction))));
			coordinate.y = int(ROUND(float(orientBR.y) + (length * sin(direction))));
		}

		//cout <<"DEBUG X: "<<coordinate.x<<endl;
		//cout <<"DEBUG Y: "<<coordinate.y<<endl;

		// calculate the angle
		direction = atan2(float(abs(orientTL.y - orientTR.y)), float(abs(orientTL.x - orientTR.x)));
		if (orientTL.y > orientTR.y && orientTL.x < orientTR.x)
		{
			direction = 2*PI - direction;
		} 
		else if (orientTL.x > orientTR.x)
		{
			direction += PI;
		}

		angle = direction;
		//cout <<"DEBUG ANGLE: "<<angle<<endl;
	}
	
	
	/*void PickAndPlaceCommand::SetOrientation1(int x, int y)
	{
		m_orientation1 = Coordinate2D(x, y);
	}

	void PickAndPlaceCommand::SetOrientation1(Coordinate2D coordinate)
	{
		m_orientation1 = coordinate;
	}

	Coordinate2D PickAndPlaceCommand::GetOrientation1()
	{
		return m_orientation1;
	}

	void PickAndPlaceCommand::SetOrientation2(int x, int y)
	{
		m_orientation2 = Coordinate2D(x, y);
	}

	void PickAndPlaceCommand::SetOrientation2(Coordinate2D coordinate)
	{
		m_orientation2 = coordinate;
	}

	Coordinate2D PickAndPlaceCommand::GetOrientation2()
	{
		return m_orientation2;
	}

	void PickAndPlaceCommand::SetOrientation3(int x, int y)
	{
		m_orientation3 = Coordinate2D(x, y);
	}

	void PickAndPlaceCommand::SetOrientation3(Coordinate2D coordinate)
	{
		m_orientation3 = coordinate;
	}

	Coordinate2D PickAndPlaceCommand::GetOrientation3()
	{
		return m_orientation3;
	} */
}