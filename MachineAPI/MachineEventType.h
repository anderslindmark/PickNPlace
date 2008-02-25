/**
 	\file MachineEventType.h
 
 	\brief
 	Contains the MachineEventType enum
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MachineEventType_H__
#define __MachineEventType_H__

/// \enum MachineEventType
/// \brief Type of an MachineEvent
enum MachineEventType
{
	EVENT_DONE, ///< Command runned successfully
	EVENT_MACHINE_ERROR, ///< Internal error in the MachineController
	EVENT_ILLEGAL_COMMAND, 
	EVENT_CMD_OUT_OF_BOUNDS, ///< The command tried to execute was out of bounds
	EVENT_EXCEPTION_SP_READ, ///< Error while reading the SerialPort
	EVENT_EXCEPTION_SP_WRITE ///< Error while writing the SerialPort
};

#endif // __MachineEventType_H__