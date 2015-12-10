//
// Created by Julian  on 10/12/15.
//

#ifndef SDL_RTS_EVENTS_H
#define SDL_RTS_EVENTS_H

#include "Events/Event.h"
#include "Components/BaseComponent.h"
#include "Components/TransformComponent.h"
#include "Components/ClickableComponent.h"
#include "Events/ClickEventHandler.h"
#include <map>
#include <vector>

class Events
{
private:
    
    int handlerId;
    int GetNextHandlerId() { return handlerId++; }

    std::map<int, ClickEventHandler*> clickEventHandlerMap; 

public:

    Events() { this->handlerId = 0; }

    int AddHandler(ClickEventHandler* clickEventHandler)
    {
        int id = GetNextHandlerId(); 
        this->clickEventHandlerMap.insert(std::pair<int, ClickEventHandler*>(id, clickEventHandler)); 
        return id; 
    }

    void Update(Event* event, std::vector<BaseComponent*> transformComponents, std::vector<BaseComponent*> clickableComponents)
    {
        for (BaseComponent* component : clickableComponents)
        {
            ClickAbleComponent* clickableComponent = static_cast<ClickAbleComponent*>(component); 
            TransformComponent* transformComponent = static_cast<TransformComponent*>(transformComponents[clickableComponent->transformId]); 
            ClickEventHandler* handler = this->clickEventHandlerMap[clickableComponent->eventHandlerId];
            handler->Handle(event, transformComponent, clickableComponent); 
        }
    }    
    
    ~Events()
    {
        for (auto mappedPair : this->clickEventHandlerMap)
        {
            delete mappedPair.second;
        }
    }
};

#endif //SDL_RTS_EVENTS_H