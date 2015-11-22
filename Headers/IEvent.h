//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_IEVENT_H
#define SDLRTS_IEVENT_H

#include "EventType.h"

// NOTE: this is a bit of a hack for now...

class IEvent
{
private:

    EventType eventType;

public:

    IEvent(EventType eventType)
    {
        this->eventType = eventType;
    }

    EventType GetEventType() { return this->eventType; }
};

#endif //SDLRTS_IEVENT_H
