#include "MachinePolygon.h"

MachinePolygon::MachinePolygon()
{
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

void MachinePolygon::AddPoint(int index, MachinePolygonPoint pp)
{
	m_points.insert(m_points.begin()+index, pp);
}

void MachinePolygon::DelPoint(int index)
{
	m_points.erase(m_points.begin()+index);
}

MachinePolygonPoint MachinePolygon::GetPoint(int index)
{
	return m_points[index];
}

int MachinePolygon::Size()
{
	return m_points.size();
}

/*
vector<MachinePolygonPoint> &MachinePolygon::GetPoints()
{
	return m_points;
}
*/

