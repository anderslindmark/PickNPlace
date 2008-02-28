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
	EVENT_CMD_DONE, ///< Command runned successfully
	EVENT_CMD_OUT_OF_BOUNDS, ///< The command tried to execute was out of bounds
	EVENT_CMD_ILLEGAL,	// TODO: Is this needed? or is it replaced by OUT_OF_BOUNDS?

	EVENT_MACHINE_INITIALIZED, ///< Machine is initiated
	EVENT_MACHINE_ERROR, ///< Internal error in the MachineController
	
	EVENT_SERIAL_READERROR, ///< Error while reading the SerialPort
	EVENT_SERIAL_WRITEERROR ///< Error while writing the SerialPort
};

#endif // __MACHINEEVENTTYPE_H__