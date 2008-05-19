/**
 	\file MachinePolygon.h
 
 	\brief
 	The header file for the MachinePolygon class
 
 	\author	Henrik Mäkitaavola & Anders Lindmark
**/


#ifndef __POLYGON_H__
#define __POLYGON_H__

#include "Axis.h"
#include <vector>

using namespace std;

/// \struct MachinePolygonPoint
/// \brief A data structure that contains a position on the x and y plane.
struct MachinePolygonPoint
{
	int x; ///< The x coordinate
	int y; ///< The y coordinate

	/// \brief Constructor for the Machine Polygon Point.
	///
	/// \param pos_x	The x coordinate
	/// \param pos_y	The y coordinate
	MachinePolygonPoint(int pos_x, int pos_y): x(pos_x), y(pos_y) {};
};

/// \class MachinePolygon
/// \brief A polygon to describe a path that the machine should take.
class MachinePolygon
{
public:
	/// \brief Constructor to create a empty Machine Polygon.
	MachinePolygon();

	/// \brief Copy constructor for the Machine Polygon.
	///
	/// \param p	The machine polygon that should be copied
	MachinePolygon(const MachinePolygon &p);

	/// \brief Deconstructor for the Machine Polygon.
	~MachinePolygon(void);

	/// \brief Add a point connected to the last point in the polygon.
	///
	/// \param pp	The point to be added
	/// \return true if the insertion succeeded, false otherwise
	bool AddPoint(MachinePolygonPoint pp);

	/// \brief Add a point on a specific index in the polygon.
	///
	/// \param pp		The point to be added
	/// \param index	The index of the point
	/// \return true if the insertion succeeded, false otherwise
	bool AddPoint(int index, MachinePolygonPoint pp);

	/// \brief Delete a point on a specific index in the polygon.
	///
	/// \param index	The index of the point to be deleted
	void DelPoint(int index);

	/// \brief Get a point at a specific index in the polygon.
	///
	/// \param index	The index of the point that should be received.
	/// \return			The point
	MachinePolygonPoint GetPoint(int index);

	/// \brief Get the number of points in the polygon.
	///
	/// \return		The number of points in the polygon
	int Size(); // Returns size of point-list
	
	vector<MachinePolygonPoint> &GetPoints();

protected:
	vector<MachinePolygonPoint> m_points; ///< The vector that contains the points
};


#endif // __POLYGON_H__