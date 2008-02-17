#include "MachineState.h"

MachineState::MachineState(int x, int y, int z, float rot)
{
	_x = x;
	_y = y;
	_z = z;
	_rot = rot;
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