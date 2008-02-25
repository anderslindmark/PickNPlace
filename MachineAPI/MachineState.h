#pragma once

class MachineState
{
public:
	MachineState(int x, int y, int z, float rot);
	MachineState(const MachineState &ms);

	int getX();
	int getY();
	int getZ();
	float getRot();

private:
	int _x;
	int _y;
	int _z;
	float _rot;
};