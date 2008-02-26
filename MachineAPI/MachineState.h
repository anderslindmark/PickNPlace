/**
 	\file MachineState.h
 
 	\brief
 	Header file for the MachineState class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MACHINESTATE_H__
#define __MACHINESTATE_H__


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
	MachineState(int x, int y, int z, float rot);

	/// \brief Copy constructor
	///
	/// \param ms the state to be coppied
	MachineState(const MachineState &ms);

	/// \brief Get the x position of the state
	/// 
	/// \return x position
	int GetX();

	
	/// \brief Get the y position of the state
	/// 
	/// \return y position
	int GetY();

	
	/// \brief Get the z position of the state
	/// 
	/// \return z position
	int GetZ();

	
	/// \brief Get the angle of the head of the state
	/// 
	/// \return head angle
	float GetRot();

private:
	int m_x; ///< x position
	int m_y; ///< y position
	int m_z; ///< z position
	float m_rot; ///< head angle
};

#endif //__MACHINESTATE_H__