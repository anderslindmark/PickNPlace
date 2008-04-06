#ifndef __POLYGON_H__
#define __POLYGON_H__

#include "Axis.h"
#include <vector>

using namespace std;

struct MachinePolygonPoint
{
	int x;
	int y;
	MachinePolygonPoint(int pos_x, int pos_y): x(pos_x), y(pos_y) {};
};

class MachinePolygon
{
public:
	MachinePolygon();
	MachinePolygon(const MachinePolygon &p);
	~MachinePolygon(void);
	void AddPoint(MachinePolygonPoint pp); // Adds a point to the end of the list
	void AddPoint(int index, MachinePolygonPoint pp); // Adds a point to the specified index of the list
	void DelPoint(int index); // Deletes a point from the specified index
	MachinePolygonPoint GetPoint(int index); // Returns the point at the specified index
	int Size(); // Returns size of point-list
	//vector<MachinePolygonPoint> &GetPoints();

private:
	vector<MachinePolygonPoint> m_points;
};


#endif // __POLYGON_H__