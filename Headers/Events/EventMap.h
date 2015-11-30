//
// Created by Julian  on 26/11/15.
//

#ifndef SDLRTS_EVENTMAP_H
#define SDLRTS_EVENTMAP_H

#include <map>
#include <vector>
#include <queue>
#include "Events/EventType.h"
#include "Events/IEventHandler.h"
#include "Events/Event.h"
#include "Events/EventType.h"

class EventMap
{
private:

    std::queue<Event*> eventQueue;
    std::map<EventType, std::vector<IEventHandler*>> eventHandlerMap;

public:

    EventMap()
    {}

    ~EventMap()
    {}

    void ProcessEvents()
    {
        std::queue<Event*> nextEventQueue;

        while (!eventQueue.empty()) {
            Event* currEvent;
            currEvent = eventQueue.front();

            for ( IEventHandler* eventHandler : eventHandlerMap[currEvent->eventType] ) {
                std::vector<Event*> newEvents = eventHandler->PassEvent(currEvent);

                for (Event* newEvent : newEvents) {
                    nextEventQueue.push(newEvent);
                }
            }

            eventQueue.pop();
        }

        eventQueue = nextEventQueue;
    }

    void AddEventMap(EventType eventType, IEventHandler* eventHandler )
    {
        if (eventHandlerMap.find(eventType) == eventHandlerMap.end()) {
            eventHandlerMap.insert(std::pair<EventType, std::vector<IEventHandler*>>());
        }

        // we could add an event type with null eventHandler
        if (eventHandler) {
            eventHandlerMap[eventType].push_back(eventHandler);
        }

    }

    void RaiseEvent(Event* event)
    {
        if (event) {
            eventQueue.push(event);
        }
    }
};

#endif //SDLRTS_EVENTMAP_H
