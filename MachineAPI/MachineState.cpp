/**
 	\file MachineState.cpp
 
 	\brief
 	Source file for the MachineState class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#include "MachineState.h"

MachineState::MachineState(int x, int y, int z, float rot)
{
	_x = x;
	_y = y;
	_z = z;
	_rot = rot;
}

MachineState::MachineState(const MachineState& ms)
{
	_x = ms._x;
	_y = ms._y;
	_z = ms._z;
	_rot = ms._rot;
}

int MachineState::getX()
{
	return _x;
}

int MachineState::getY()
{
	return _y;
}

int MachineState::getZ()
{
	return _z;
}

float MachineState::getRot()
{
	return _rot;
}