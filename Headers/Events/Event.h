//
// Created by Julian  on 26/11/15.
//

#ifndef SDLRTS_EVENT_H
#define SDLRTS_EVENT_H

#include "EventType.h"
#include "EventInfo.h"

struct Event
{
    EventType eventType;
    IEventInfo* eventInfo;

    Event(EventType eventType)
    {
        this->eventType = eventType;
    }

    Event(EventType eventType, IEventInfo* eventInfo)
    {
        this->eventType = eventType;
        this->eventInfo = eventInfo;
    }

    ~Event()
    {
        delete eventInfo;
    }

};




#endif //SDLRTS_EVENT_H
