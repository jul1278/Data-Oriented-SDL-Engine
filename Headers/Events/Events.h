//
// Created by Julian  on 10/12/15.
//

#ifndef SDL_RTS_EVENTS_H
#define SDL_RTS_EVENTS_H

#include "Events/Event.h"
#include "Components/BaseComponent.h"
#include "Components/TransformComponent.h"
#include "Components/ClickableComponent.h"
#include "Events/MouseEventHandler.h"
#include <map>
#include <vector>

class Events
{
private:
    
    int handlerId;
    int GetNextHandlerId() { return handlerId++; }

    std::map<int, MouseEventHandler*> clickEventHandlerMap; 

public:

    Events() { this->handlerId = 0; }

    int AddHandler(MouseEventHandler* clickEventHandler)
    {
        int id = GetNextHandlerId(); 
        this->clickEventHandlerMap.insert(std::pair<int, MouseEventHandler*>(id, clickEventHandler));

		// TODO: get the 'handler description' and put the correct components into it?

        return id; 
    }

    void Update(Event* event, std::vector<BaseComponent*> transformComponents, std::vector<BaseComponent*> clickableComponents)
    {
        for (BaseComponent* component : clickableComponents)
        {
            ClickAbleComponent* clickableComponent = static_cast<ClickAbleComponent*>(component); 
            TransformComponent* transformComponent = static_cast<TransformComponent*>(transformComponents[clickableComponent->transformId]); 
            MouseEventHandler* handler = this->clickEventHandlerMap[clickableComponent->eventHandlerId];
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