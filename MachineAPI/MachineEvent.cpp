#include "MachineEvent.h"

MachineEvent::MachineEvent(MachineEventType eventType, string eventMsg)
{
	_eventType = eventType;
	_eventMsg = eventMsg;
}

MachineEvent::MachineEvent(MachineEvent &e)
{
	_eventType = e.getEventType();
	_eventMsg  = e.getEventMsg();
}

string MachineEvent::getEventMsg()
{
	return _eventMsg;
}

MachineEventType MachineEvent::getEventType()
{
	return _eventType;
}
