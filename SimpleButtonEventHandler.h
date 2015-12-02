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

class SimpleButtonClickHandler : public IEventHandler
{
private:

    virtual std::vector<Event*> ProcessEvent(std::map<ComponentType, std::vector<BaseComponent*>> componentMap, Event* event)
    {
        MouseClickEvent* mouseClickEvent = static_cast<MouseClickEvent*>(event->eventInfo);

        if (mouseClickEvent == nullptr) {
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

            float dx = mouseClickEvent->pos.x - transformComponent->position.x;
            float dy = mouseClickEvent->pos.y - transformComponent->position.y;

            if (dx > 0.0f && dy > 0.0f)
            {
                if ((dx < clickAbleComponent->clickArea.x) && (dy < clickAbleComponent->clickArea.y)) {       
                    transformComponent->scale.x += 1.0f; 
                    transformComponent->scale.y += 1.0f; 
                }
            }
        }

        return std::vector<Event*>();
    }

public:

    SimpleButtonClickHandler(){}
    ~SimpleButtonClickHandler(){}
};


#endif // SDLRTS_SIMPLEBUTTONEVENTHANDLER_H