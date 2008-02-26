/**
 	\file MachineEventType.h
 
 	\brief
 	Contains the MachineEventType enum
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MACHINEEVENTTYPE_H__
#define __MACHINEEVENTTYPE_H__

/// \enum MachineEventType
/// \brief Type of an MachineEvent
enum MachineEventType
{
	EVENT_DONE, ///< Command runned successfully
	EVENT_INITIALIZED, ///< Machine is initiated
	EVENT_MACHINE_ERROR, ///< Internal error in the MachineController
	EVENT_ILLEGAL_COMMAND, 
	EVENT_CMD_OUT_OF_BOUNDS, ///< The command tried to execute was out of bounds
	EVENT_EXCEPTION_SP_READ, ///< Error while reading the SerialPort
	EVENT_EXCEPTION_SP_WRITE ///< Error while writing the SerialPort
};

#endif // __MACHINEEVENTTYPE_H__