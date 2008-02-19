#pragma once
#include <string>
#include "MachineEventType.h"

using namespace std;

class MachineEvent
{
public:
	MachineEvent(MachineEventType eventType, string eventMsg);
	
	MachineEventType	getEventType();
	string				getEventMsg();


private:
	MachineEventType	_eventType;
	string				_eventMsg;
};