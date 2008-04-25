/**
 	\file MachineMovePolygonCommand.h
 
 	\brief
 	Header file for the MachineMovePolygonCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/
#ifndef __MACHINEMOVEPOLYGONCOMMAND_H__
#define __MACHINEMOVEPOLYGONCOMMAND_H__

#include "MachineCommand.h"
#include "MachinePolygon.h"

/// \class MachineMovePolygonCommand
/// \brief Move the Pick n Place machine along a polygon
class MachineMovePolygonCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	MachineMovePolygonCommand(MachinePolygon polygon);
	MachineMovePolygonCommand();
	~MachineMovePolygonCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool HasNextState();
	MachinePolygon GetPolygon();
	bool SetPolygon(MachinePolygon polygon);
	bool IsValid();

private:
	bool DoCommand(SerialPort &sp);
	MachineMovePolygonCommand *Copy();
	bool ValidatePolygon();

	MachinePolygon m_polygon;
	int m_vectorIndex;
	bool m_valid;
};


#endif // __MACHINEMOVEPOLYGONCOMMAND_H__

