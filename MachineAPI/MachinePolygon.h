#ifndef __POLYGON_H__
#define __POLYGON_H__

#include "Axis.h"
#include <vector>

using namespace std;

struct MachinePolygonPoint
{
	Axis axis;
	int position;
	MachinePolygonPoint(Axis a, int p): axis(a), position(p) {};
};

class MachinePolygon
{
public:
	MachinePolygon(int startX, int startY, int startZ);
	MachinePolygon(const MachinePolygon &p);
	~MachinePolygon(void);
	void AddPoint(MachinePolygonPoint pp);
	vector<MachinePolygonPoint> &GetPoints();

private:
	vector<MachinePolygonPoint> m_points;
};


#endif // __POLYGON_H__