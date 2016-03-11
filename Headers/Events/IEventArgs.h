#ifndef IEVENT_ARGS_H
#define IEVENT_ARGS_H

#include "Events\EventTypes.h"

class IEventArgs 
{
private:

	EventType eventType; 

public:

	IEventArgs(EventType eventType)
	{
		this->eventType = eventType; 
	}

	virtual ~IEventArgs() {}; 

	EventType GetEventType() { return this->eventType; }
};

#endif // IEVENT_ARGS_H
