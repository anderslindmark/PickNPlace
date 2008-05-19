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

bool MachinePolygon::AddPoint(MachinePolygonPoint pp)
{
	return AddPoint(Size(), pp);
}

bool MachinePolygon::AddPoint(int index, MachinePolygonPoint pp)
{
	if (index > Size() || index < 0)
	{
		return false;
	}
	else
	{
		m_points.insert(m_points.begin()+index, pp);
		return true;
	}
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

vector<MachinePolygonPoint> &MachinePolygon::GetPoints()
{
	return m_points;
}


