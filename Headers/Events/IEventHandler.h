//
// Created by Julian  on 26/11/15.
//

#ifndef SDLRTS_EVENTHANDLER_H
#define SDLRTS_EVENTHANDLER_H

#include "Event.h"
#include <vector>
#include <map>
#include <Components/BaseComponent.h>
#include <Entity.h>

class IEventHandler
{
private:

    uint32_t id; 
    std::map<ComponentType, std::vector<BaseComponent*>> componentMap;

    virtual std::vector<Event*> ProcessEvent(std::map<ComponentType, std::vector<BaseComponent*>>* componentMap, Event* event) = 0;
public:

    IEventHandler(uint32_t id) { this->id = id; }

    virtual ~IEventHandler() {}

    uint32_t Id() { return this->id; }

    void InsertComponents(std::vector<BaseComponent*> components, ComponentType componentType)
    {
        // check if this event type is already mapped
        if (this->componentMap.find(componentType) == this->componentMap.end()) {
            this->componentMap.insert(std::pair<ComponentType, std::vector<BaseComponent*>>(
                    componentType,
                    std::vector<BaseComponent*>())
            );
        }

        if (components.size() != 0) {
            for ( BaseComponent* baseComponent : components) {
                this->componentMap[componentType].push_back(baseComponent);
            }
        }
    }

    void InsertComponent(BaseComponent* component, ComponentType componentType)
    {
        // check if this event type is already mapped
        if (this->componentMap.find(componentType) == this->componentMap.end()) {
            this->componentMap.insert(std::pair<ComponentType, std::vector<BaseComponent*>>(
                    componentType,
                    std::vector<BaseComponent*>())
            );
        }

        if (component) {
            this->componentMap[componentType].push_back(component);
        }
    }

    std::vector<Event*> PassEvent(Event* event)
    {
        return this->ProcessEvent(&this->componentMap, event);
    }
};


#endif //SDLRTS_EVENTHANDLER_H
