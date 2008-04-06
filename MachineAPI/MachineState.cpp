/**
 	\file MachineState.cpp
 
 	\brief
 	Source file for the MachineState class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#include "MachineState.h"
#include <sstream>

MachineState::MachineState()
{
	m_mss = MachineStateStruct();
}

MachineState::MachineState(MachineStateStruct &mss)
{
	m_mss = mss;
}

MachineState::MachineState(const MachineState& ms)
{
	m_mss = ms.m_mss;
}

MachineStateStruct MachineState::GetState()
{
	return m_mss;
}

string MachineState::ToString()
{
	stringstream ss;
	ss << "X: " << m_mss.x << " Y: " << m_mss.y << " Z: " << m_mss.z << " Speed: " << m_mss.dispenceState.speed;
	return ss.str();
}
