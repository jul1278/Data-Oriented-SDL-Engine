//
// Created by Julian  on 10/12/15.
//

#ifndef SDL_RTS_EVENTS_H
#define SDL_RTS_EVENTS_H

#include "Events/Event.h"
#include "Components/BaseComponent.h"
#include "Components/TransformComponent.h"
#include "Components/ClickableComponent.h"
#include "Events/IEventHandler.h"
#include <map>
#include <vector>

class Events
{
private:
    
    int handlerId;
    int GetNextHandlerId() { return handlerId++; }

	map<int, IEventHandler*> eventHandlers; 
	map<EventType, vector<int>> eventTypeMap; 
	vector<Event*> events; 

public:

    Events() { this->handlerId = 0; }

    int AddHandler(IEventHandler* eventHandler)
    {
		if (eventHandler == nullptr) {
			return -1; 
		}

        int id = GetNextHandlerId(); 
       
		eventHandlers.insert(pair<int, IEventHandler*>(id, eventHandler)); 

		// TODO: get the 'handler description' and put the correct components into it?
        return id; 
    }

	void Update()
    {
	    for (auto eventIt = this->events.begin(); eventIt != this->events.end(); ++eventIt)
        {
			for (auto* eventHandler : this->eventHandlers) {
				eventHandler->HandleEvent(eventIt, this); 
			}
        }

		this->events.clear(); 
    }

	void PostEvent(Event* event)
    {
		if (event) {
			this->events.push_back(event);
		}
    }
};

#endif //SDL_RTS_EVENTS_H