#ifndef __COORDINATE_H__
#define __COORDINATE_H__

namespace PicknPlaceGui
{
	struct Coordinate3D
	{
		int x;
		int y;
		int z;
		Coordinate3D(): x(0), y(0), z(0) {};
		Coordinate3D(int _x, int _y, int _z): x(_x), y(_y), z(_z) {};
	};

	struct Coordinate2D
	{
		int x;
		int y;
		Coordinate2D(): x(0), y(0) {};
		Coordinate2D(int _x, int _y): x(_x), y(_y) {};
	};
}

#endif // __COORDINATE_H__