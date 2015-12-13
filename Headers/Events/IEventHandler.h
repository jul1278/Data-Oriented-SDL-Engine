//
// Created by Julian  on 26/11/15.
//

#ifndef SDLRTS_EVENTHANDLER_H
#define SDLRTS_EVENTHANDLER_H

#include "Event.h"
#include "Events.h"
#include <vector>
#include <map>
#include <Components/BaseComponent.h>
#include <Entity.h>


using namespace std;

class IEventHandler
{
private:

    uint32_t id;    
	map<ComponentType, BaseComponent*> components; 

public:

    IEventHandler(uint32_t id)
    {
	    this->id = id;
    }

    virtual ~IEventHandler() {}

    uint32_t Id() const
    {
	    return this->id;
    }

    void InsertComponent(BaseComponent* component, ComponentType componentType)
    {
		if (components.find(componentType) == components.end()) {
			components.insert(pair<ComponentType, BaseComponent*>(componentType, component)); 
		}
    }

	template<typename T>
	T* Component(ComponentType componentType)
    {
		if (this->components.find(componentType) != this->components.end()) {
			return static_cast<T*>(components[componentType]); 
		}
		return nullptr; 
    }

	virtual std::vector<Event*> HandleEvent(Event* event) = 0;
};


#endif //SDLRTS_EVENTHANDLER_H
