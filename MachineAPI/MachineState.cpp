/**
 	\file MachineState.cpp
 
 	\brief
 	Source file for the MachineState class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#include "MachineState.h"

MachineState::MachineState(int x, int y, int z, float rot)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_rot = rot;
}

MachineState::MachineState(const MachineState& ms)
{
	m_x = ms.m_x;
	m_y = ms.m_y;
	m_z = ms.m_z;
	m_rot = ms.m_rot;
}

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