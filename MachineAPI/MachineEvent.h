/**
 	\file MachineEvent.h
 
 	\brief
 	Header file for the MachineEvent class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#ifndef __MACHINEEVENT_H__
#define __MACHINEEVENT_H__

#include <string>
#include "MachineEventType.h"

using namespace std;

/// \class MachineEvent
/// \brief Event sent by the MachineController
///
class MachineEvent
{
public:
	/// \brief Constructor
	///
	/// \param eventType type of event
	/// \param eventMsg message in the event
	MachineEvent(MachineEventType eventType, string eventMsg);

	/// \brief Copy constuctor
	MachineEvent(MachineEvent &e);

	/// \brief Get the event type
	///
	/// \return type of the event
	MachineEventType	GetEventType();

	/// \brief Get the message stored in the event
	///
	/// \return message stored in the event
	string				GetEventMsg();


private:
	MachineEventType	m_eventType; ///< The event type
	string				m_eventMsg; ///< The event message
};

#endif //__MACHINEEVENT_H__