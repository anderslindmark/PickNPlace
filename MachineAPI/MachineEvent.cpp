/**
 	\file MachineEvent.cpp
 
 	\brief
 	Source file for the MachineEvent class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/

#include "MachineEvent.h"

MachineEvent::MachineEvent(MachineEventType eventType, string eventMsg)
{
	m_eventType = eventType;
	m_eventMsg = eventMsg;
}

MachineEvent::MachineEvent(MachineEvent &e)
{
	m_eventType = e.GetEventType();
	m_eventMsg  = e.GetEventMsg();
}

string MachineEvent::GetEventMsg()
{
	return m_eventMsg;
}

MachineEventType MachineEvent::GetEventType()
{
	return m_eventType;
}
