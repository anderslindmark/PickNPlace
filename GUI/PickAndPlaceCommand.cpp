#include "PickAndPlaceCommand.h"
#include <math.h>
#include <iostream>
using namespace std;

#define PI 3.14159265f
//#define ROUND(x) floor(x+0.5)

namespace PicknPlaceGui
{
	PickAndPlaceCommand::PickAndPlaceCommand(Coordinate2D pickOrientTL,
						Coordinate2D pickOrientTR,
						Coordinate2D pickOrientBR,
						Coordinate2D placeOrientTL,
						Coordinate2D placeOrientTR,
						Coordinate2D placeOrientBR,
						PickStateStruct settings)
	{
		CalcCoordinate(	pickOrientTL,
						pickOrientTR,
						pickOrientBR,
						m_pick,
						m_pickAngle);
		CalcCoordinate(	placeOrientTL,
						placeOrientTR,
						placeOrientBR,
						m_place,
						m_placeAngle);
		m_settings = settings;
		Init();
	}

	PickAndPlaceCommand::PickAndPlaceCommand(int pickX, int pickY, float pickAngle,
						int placeX, int placeY, float placeAngle, PickStateStruct settings)
	{
		m_pick = Coordinate2D(pickX, pickY);
		m_pickAngle = pickAngle;
		m_place = Coordinate2D(placeX, placeY);
		m_placeAngle = placeAngle;
		m_settings = settings;
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
	
	void PickAndPlaceCommand::SetSettings(PickStateStruct settings)
	{
		m_settings = settings;
	}

	PickStateStruct PickAndPlaceCommand::GetSettings()
	{
		return m_settings;
	}

	MachineWrapperCommand& PickAndPlaceCommand::GetMachineCommand()
	{
		if (m_cmd)
		{
			delete m_cmd;
		}

		m_cmd = new MachineWrapperCommand(false);

		// Pick parameters
		m_cmd->Add(MachineSetPickTimeCommand(PICKTIME_AFTER_PICK, m_settings.afterPickTime));
		m_cmd->Add(MachineSetPickTimeCommand(PICKTIME_PRESS_PICK, m_settings.pickPressDownTime));
		m_cmd->Add(MachineSetPickOffsetCommand(PICKOFFSET_TOOLHEIGHT, m_settings.headHeight));
		m_cmd->Add(MachineSetPickOffsetCommand(PICKOFFSET_PICKHEIGHT, m_settings.pickHeight));
		m_cmd->Add(MachinePickCommand(PICKCMD_PICK, m_pick.x, m_pick.y, m_pickAngle));

		// Place parameters
		m_cmd->Add(MachineSetPickTimeCommand(PICKTIME_AFTER_PLACE, m_settings.afterPlaceTime));
		m_cmd->Add(MachineSetPickTimeCommand(PICKTIME_PRESS_PLACE, m_settings.placePressDownTime));
		m_cmd->Add(MachineSetPickOffsetCommand(PICKOFFSET_PLACEHEIGHT, m_settings.placeHeight));
		m_cmd->Add(MachinePickCommand(PICKCMD_PLACE, m_place.x, m_place.y, m_placeAngle));

		return *m_cmd;
	}


	void PickAndPlaceCommand::SetPickCoordinate(int x, int y, float angle)
	{
		m_pick = Coordinate2D(x, y);
		m_pickAngle = angle;
	}

	void PickAndPlaceCommand::SetPickCoordinate(Coordinate2D pickOrientTL,
								Coordinate2D pickOrientTR,
								Coordinate2D pickOrientBR)
	{
		CalcCoordinate(	pickOrientTL,
						pickOrientTR,
						pickOrientBR,
						m_pick,
						m_pickAngle);
	}

	void PickAndPlaceCommand::SetPickX(int x)
	{
		m_pick.x = x;
	}

	void PickAndPlaceCommand::SetPickY(int y)
	{
		m_pick.y = y;
	}

	void PickAndPlaceCommand::SetPickAngle(float angle)
	{
		m_pickAngle = angle;
	}

	void PickAndPlaceCommand::SetPlaceCoordinate(int x, int y, float angle)
	{
		m_place = Coordinate2D(x, y);
		m_placeAngle = angle;
	}

	void PickAndPlaceCommand::SetPlaceCoordinate(Coordinate2D placeOrientTL,
								Coordinate2D placeOrientTR,
								Coordinate2D placeOrientBR)
	{
		CalcCoordinate(	placeOrientTL,
						placeOrientTR,
						placeOrientBR,
						m_place,
						m_placeAngle);
	}

	void PickAndPlaceCommand::SetPlaceX(int x)
	{
		m_place.x = x;
	}

	void PickAndPlaceCommand::SetPlaceY(int y)
	{
		m_place.y = y;
	}

	void PickAndPlaceCommand::SetPlaceAngle(float angle)
	{
		m_placeAngle = angle;
	}

	Coordinate2D PickAndPlaceCommand::GetPickCoordinate()
	{
		return m_pick;
	}

	float PickAndPlaceCommand::GetPickAngle()
	{
		return m_pickAngle;
	}
	
	Coordinate2D PickAndPlaceCommand::GetPlaceCoordinate()
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
									Coordinate2D &coordinate,
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