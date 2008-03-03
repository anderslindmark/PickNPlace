/**
 	\file MachineState.cpp
 
 	\brief
 	Source file for the MachineState class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#include "MachineState.h"

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

/*
int MachineState::GetX()
{
	return m_x;
}

int MachineState::GetY()
{
	return m_y;
}

int MachineState::GetZ()
{
	return m_z;
}

float MachineState::GetRot()
{
	return m_rot;
}
*/