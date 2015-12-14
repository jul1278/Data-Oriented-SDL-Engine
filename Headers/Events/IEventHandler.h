//
// Created by Julian  on 26/11/15.
//

#ifndef SDLRTS_EVENTHANDLER_H
#define SDLRTS_EVENTHANDLER_H

#include "Events/Events.h"
#include "Events/Event.h"
#include "Components/BaseComponent.h"
#include "ComponentType.h"
#include <vector>
#include <map>

class Events;
using namespace std;

class IEventHandler
{
private:

    int id;    
	map<ComponentType, map<int, BaseComponent*>> components; 

public:

    IEventHandler(int id)
    {
	    this->id = id;
    }

    virtual ~IEventHandler()
    {}

    int Id() const
    {
	    return this->id;
    }

	map<ComponentType, map<int, BaseComponent*>> Components() const { return this->components; }
		
	void AddComponents(ComponentType componentType, BaseComponent* component)
    {
		if (this->components.find(componentType) == this->components.end()) {
			this->components.insert(pair<ComponentType, map<int, BaseComponent*>>(componentType, map<int, BaseComponent*>()));
		}
		this->components[componentType].insert(pair<int, BaseComponent*>(component->id, component));
    }

	virtual void HandleEvent(Event* event, Events* events) = 0;
};


#endif //SDLRTS_EVENTHANDLER_H
