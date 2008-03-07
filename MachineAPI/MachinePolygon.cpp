#include "MachinePolygon.h"

MachinePolygon::MachinePolygon(int startX, int startY, int startZ)
{
	m_points.push_back(MachinePolygonPoint(AXIS_X, startX));
	m_points.push_back(MachinePolygonPoint(AXIS_Y, startY));
	m_points.push_back(MachinePolygonPoint(AXIS_Z, startZ));
}

MachinePolygon::MachinePolygon(const MachinePolygon &p)
{
	m_points = p.m_points;
}

MachinePolygon::~MachinePolygon(void)
{
}

void MachinePolygon::AddPoint(MachinePolygonPoint pp)
{
	m_points.push_back(pp);
}

vector<MachinePolygonPoint> &MachinePolygon::GetPoints()
{
	return m_points;
}

