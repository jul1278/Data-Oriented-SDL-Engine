//
// Created by Julian  on 13/12/15.
//

#ifndef SDLRTS_ICOMPONENT_PROCESS_H
#define SDLRTS_ICOMPONENT_PROCESS_H

#include "Events/Event.h"
#include "Events/Events.h"
#include "Components/BaseComponent.h"
#include "ComponentType.h"
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class IComponentProcess
{
private:

	int id;

	map<EventType, vector<ComponentType>> componentTypes; 

public:

	IComponentProcess(int id)
	{
		this->id = id; 
	}; 
 
	virtual void Process(Event* event, Events* events, map<ComponentType, vector<BaseComponent*>*>& componentMap) = 0;

	int Id() { return this->id; }

	void AddEventComponentMapping(EventType eventType, ComponentType componentType)
	{
		if (this->componentTypes.find(eventType) != this->componentTypes.end()) {
			this->componentTypes[eventType].push_back(componentType);
			return; 
		} 
		
		this->componentTypes.insert(pair<EventType, vector<ComponentType>>(eventType, vector<ComponentType>()));
		this->componentTypes[eventType].push_back(componentType); 
	}

	map<EventType, vector<ComponentType>> GetProcessDescription()
	{
		return this->componentTypes; 
	}
};

#endif //SDLRTS_ICOMPONENT_PROCESS_H