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

/// \struct PickStateStruct
/// \brief Keeps the current state for the Pick and Place head parameters.
struct PickStateStruct
{
	int offsetX;		///< Distance between the center of the pick tool and the camera in X
	int offsetY;		///< Distance between the center of the pick tool and the camera in Y

	int afterPickTime;	///< Wait after pick (* 0.1s)
	int pickPressDownTime;	///< Press-Down time during pick (* 0.1s)
	int placePressDownTime; ///< Press-Down time during place (* 0.1s)
	int afterPlaceTime;	///< Wait after place (* 0.1s)

	int headHeight; ///< Height in micrometer of the head-tool.
	int pickHeight; ///< Height in micrometers between the floor and the head-tool in it's lowest position (during pick)
	int placeHeight; ///< Height in micrometers between the PCB and the head-tool in it's lowest position (during place)

	/// \brief Default constructor for the Pick State Struct.
	///
	/// See code for default settings.
	PickStateStruct(void): offsetX(0), offsetY(0), afterPickTime(0), pickPressDownTime(0), placePressDownTime(0), afterPlaceTime(0),
		headHeight(43000), pickHeight(1100), placeHeight(1100) {};
};

/// \struct DispenceStateStruct
/// \brief Keeps the current state for the dispencer parameters.
struct DispenceStateStruct
{
	int offsetX; ///< Distance between the center of the dispencer needle and the camera in X
	int offsetY; ///< Distance between the center of the dispencer needle and the camera in Y
	int offsetZ; ///< Distance between the center of the dispencer needle and the "floor" in Z
	int offsetZs; ///< Distance the needle should be lowered after the after time has been applaid
	int offsetTurn; ///< The offset that the machine moves to avoid creating a blob when dispensing and making a turn.
	int speed;	///< The speed the machine should move in
	int beforeTime; ///< The time the solder should be applied before the first movement, multiplied with 0.1s
	int afterTime; ///< The time the solder should be applied after the last movement, multiplied with 0.1s
	int suckBackTime; ///< The time the solder should be sucked back after the last movement, multiplied with 0.1s
	bool needleDown; ///< Indicates whether the needle has been lowered
	
	/// \brief Default constructor for the Dispence State Struct.
	///
	/// See code for default settings.
	DispenceStateStruct(void): offsetX(0), offsetY(0), offsetZ(0), offsetZs(0), offsetTurn(0), speed(1), beforeTime(0), afterTime(0), suckBackTime(0), needleDown(false) {};
};

/// \struct MachineStateStruct
/// \brief Keeps the current state of the Pick and Place machine.
struct MachineStateStruct
{
	int x; ///< Current x position
	int y; ///< Current y position
	int z; ///< Current z position
	float rot; ///< Current rotation angle of the head
	int lampCameraBrightness; ///< Current camera lamp brightness
	int lampLookupBrightness; ///< Current look up lamp brightness
	DispenceStateStruct dispenceState; ///< Current dispencer state
	PickStateStruct pickState; ///< Current pick and place head state

	/// \brief Default constructor for the Machine State Struct.
	///
	/// See code for default settings.
	MachineStateStruct(void): x(0), y(0), z(0), rot(0.0), lampCameraBrightness(8), lampLookupBrightness(8),dispenceState(), pickState() {};
};

/// \class MachineState
/// \brief Represent a state of the Pick n Place machine
class MachineState
{
public:
	/// \brief Default constructor.
	MachineState();

	/// \brief Constructor to create a Machine State from a MachineStateStruct.
	///
	/// \param mss The MachineStateStruct
	MachineState(MachineStateStruct &mss);

	/// \brief Copy constructor.
	///
	/// \param ms the state to be coppied
	MachineState(const MachineState &ms);

	/// \brief Get the state struct.
	///
	/// \return state struct
	MachineStateStruct GetState();

	/// \brief Get a string representation of the Machine State.
	///
	/// \return The string
	string ToString();

private:
	MachineStateStruct m_mss; ///< The state of the MachineState
	
};

#endif //__MACHINESTATE_H__
