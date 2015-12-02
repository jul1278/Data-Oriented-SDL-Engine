//
// Created by Julian  on 2/12/15.
//

#ifndef SDLRTS_SIMPLEBUTTONEVENTHANDLER_H
#define SDLRTS_SIMPLEBUTTONEVENTHANDLER_H

#include "Events/IEventHandler.h"
#include "Components/ClickableComponent.h"
#include "Components/TransformComponent.h"
#include <algorithm>
#include <ostream>

class SimpleButtonEventHandler : public IEventHandler
{
private:

    virtual std::vector<Event*> ProcessEvent(std::map<ComponentType, std::vector<BaseComponent*>> componentMap, Event* event)
    {
        MouseMoveEvent* mouseMoveEvent = static_cast<MouseMoveEvent*>(event->eventInfo);

        if (mouseMoveEvent == nullptr) {
            return std::vector<Event*>();
        }

        if (componentMap.find(CLICKABLE_COMPONENT) == componentMap.end()
            || componentMap.find(TRANSFORM_COMPONENT) == componentMap.end()) {

            return std::vector<Event*>();
        }

        std::vector<BaseComponent*> clickAbleComponents = componentMap[CLICKABLE_COMPONENT];
        std::vector<BaseComponent*> transformComponents = componentMap[TRANSFORM_COMPONENT];
        
        for (BaseComponent* baseComponent : clickAbleComponents) {

            ClickAbleComponent* clickAbleComponent = static_cast<ClickAbleComponent*>(baseComponent);

            if (clickAbleComponent == nullptr) {
                continue;
            }

            int i = clickAbleComponent->transformId;

            auto transformComponentIt = std::find_if(transformComponents.begin(), transformComponents.end(),
                [i](BaseComponent* item)->bool
            {
                return item->id == i;
            });

            TransformComponent* transformComponent = static_cast<TransformComponent*>(*transformComponentIt);

            transformComponent->scale.x = 1.0f;
            transformComponent->scale.y = 1.0f;

            // if the mouse moves over the 
            float dx = mouseMoveEvent->lastPos.x - transformComponent->position.x;
            float dy = mouseMoveEvent->lastPos.y - transformComponent->position.y;

            if (dx > 0.0f && dy > 0.0f)
            {
                if ((dx < clickAbleComponent->clickArea.x) && (dy < clickAbleComponent->clickArea.y)) {       
                    transformComponent->scale.x = 1.1f; 
                    transformComponent->scale.y = 1.1f; 
                } 
            }
        }

        return std::vector<Event*>();
    }

public:

    SimpleButtonEventHandler(){}
    ~SimpleButtonEventHandler(){}
};


#endif // SDLRTS_SIMPLEBUTTONEVENTHANDLER_H