//
// Created by Julian  on 26/11/15.
//

#ifndef SDLRTS_EVENTMAP_H
#define SDLRTS_EVENTMAP_H

#include <map>
#include <vector>
#include <queue>
#include "Events/EventType.h"
#include "Events/EventHandler.h"
#include "Events/Event.h"
#include "Events/EventType.h"

class EventMap
{
private:

    std::queue<Event*> eventQueue;
    std::map<EventType, std::vector<EventHandler*>> eventHandlerMap;

public:

    EventMap()
    {

    }

    ~EventMap()
    {

    }

    void Update()
    {
        std::queue<Event*> nextEventQueue;

        while (!eventQueue.empty()) {
            Event* currEvent;
            currEvent = eventQueue.front();

            for ( EventHandler* eventHandler : eventHandlerMap[currEvent->eventType] ) {
                std::vector<Event*> newEvents = eventHandler->PassEvent(currEvent);
                nextEventQueue.push(newEvents);
            }

            eventQueue.pop();
        }

        eventQueue = nextEventQueue;
    }
    
    void AddEventMap(EventType eventType, EventHandler* eventHandler )
    {
        if (eventHandlerMap.find(eventType) == eventHandlerMap.end()) {
            eventHandlerMap.insert(std::pair<EventType, new std::vector<EventHandler*>>());
        }

        eventHandlerMap[eventType].push_back(eventHandler);
    }

    void RaiseEvent(Event* event)
    {
        if (event) {
            eventQueue.push(event);
        }
    }

};

#endif //SDLRTS_EVENTMAP_H
