/**
 	\file MachineState.h
 
 	\brief
 	Header file for the MachineState class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MACHINESTATE_H__
#define __MACHINESTATE_H__

#include <string>

using namespace std;

struct DispenceStateStruct
{
	int offsetX;
	int offsetY;
	int offsetZ;
	int offsetZs;
	int offsetTurn; // The offset that the machine moves to avoid creating a blob when dispensing and making a turn.
	int speed;
	int beforeTime; // Time multipliers ( *0.1s)
	int afterTime;
	int suckBackTime;
	bool needleDown;

	DispenceStateStruct(void): offsetX(0), offsetY(0), offsetZ(0), offsetZs(0), offsetTurn(0), speed(1), beforeTime(0), afterTime(0), suckBackTime(0), needleDown(false) {};
};

struct MachineStateStruct
{
	int x;
	int y;
	int z;
	float rot;
	int lampCameraBrightness;
	int lampLookupBrightness;
	DispenceStateStruct dispenceState;
	MachineStateStruct(void): x(0), y(0), z(0), rot(0.0), lampCameraBrightness(8), lampLookupBrightness(8),dispenceState() {};
};

/// \class MachineState
/// \brief Represent a state of the Pick n Place machine
class MachineState
{
public:
	/// \brief Constructor
	///
	/// \param x x position
	/// \param y y position
	/// \param z z position
	/// \param rot the heads angle
	MachineState();
	MachineState(MachineStateStruct &mss);

	/// \brief Copy constructor
	///
	/// \param ms the state to be coppied
	MachineState(const MachineState &ms);

	/// \brief Get the state struct
	///
	/// \return state struct
	MachineStateStruct GetState();

	string ToString();

	/// \brief Get the x position of the state
	/// 
	/// \return x position
	//int GetX();

	
	/// \brief Get the y position of the state
	/// 
	/// \return y position
	//int GetY();

	
	/// \brief Get the z position of the state
	/// 
	/// \return z position
	//int GetZ();

	
	/// \brief Get the angle of the head of the state
	/// 
	/// \return head angle
	//float GetRot();

private:
	/*
	int m_x; ///< x position
	int m_y; ///< y position
	int m_z; ///< z position
	float m_rot; ///< head angle
	*/
	MachineStateStruct m_mss;
	
};

#endif //__MACHINESTATE_H__