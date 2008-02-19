#include "MachineEvent.h"

MachineEvent::MachineEvent(MachineEventType eventType, string eventMsg)
{
	_eventType = eventType;
	_eventMsg = eventMsg;
}

string MachineEvent::getEventMsg()
{
	return _eventMsg;
}

MachineEventType MachineEvent::getEventType()
{
	return _eventType;
}
