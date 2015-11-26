//
// Created by Julian  on 26/11/15.
//

#ifndef SDLRTS_EVENTHANDLER_H
#define SDLRTS_EVENTHANDLER_H

#include "ITransform.h"
#include "Event.h"
#include <vector>

class EventHandler
{
private:

    std::vector<ITransform*> transforms;

public:

    EventHandler(){}
    ~EventHandler() {}

    std::vector<Event*> PassEvent(Event* event)
    {
        std::vector<Event*> events;

        return events;
    }
};


#endif //SDLRTS_EVENTHANDLER_H
