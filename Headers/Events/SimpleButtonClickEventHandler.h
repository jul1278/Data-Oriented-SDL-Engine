//
// Created by Julian  on 28/11/15.
//

#ifndef SDLRTS_SIMPLEBUTTONCLICKEVENTHANDLER_H
#define SDLRTS_SIMPLEBUTTONCLICKEVENTHANDLER_H

#include "Events/IEventHandler.h"
#include "Components/ClickableComponent.h"
#include "Components/TransformComponent.h"
#include <algorithm>

class SimpleButtonClickEventHandler : public IEventHandler
{
private:

    virtual std::vector<Event*> ProcessEvent(std::map<ComponentType, std::vector<BaseComponent*>> componentMap, Event* event)
    {
        MouseClickEvent* mouseClickEvent = (MouseClickEvent*) event->eventInfo;

        if (mouseClickEvent == NULL) {
            return std::vector<Event*>();
        }

        if (componentMap.find(CLICKABLE_COMPONENT) == componentMap.end()
            || componentMap.find(TRANSFORM_COMPONENT) == componentMap.end() ) {

            return std::vector<Event*>();
        }

        // get the component vector pointers
        std::vector<BaseComponent*> clickAbleComponents = componentMap[CLICKABLE_COMPONENT];
        std::vector<BaseComponent*> transformComponents = componentMap[TRANSFORM_COMPONENT];

        for (BaseComponent* baseComponent : clickAbleComponents) {

            ClickAbleComponent* clickAbleComponent = (ClickAbleComponent*) baseComponent;

            if (clickAbleComponent == NULL) {
                continue;
            }

            int i = clickAbleComponent->transformId;

            auto transformComponentIt = std::find_if(transformComponents.begin(), transformComponents.end(),
            [i](BaseComponent* item)->bool
            {
                return item->id == i;
            });

            TransformComponent* transformComponent = (TransformComponent*) *transformComponentIt;

            float dx, dy;

            dx = fabsf(transformComponent->position.x - mouseClickEvent->pos.x);
            dy = fabsf(transformComponent->position.y - mouseClickEvent->pos.y);

            if ( (dx < clickAbleComponent->clickArea.x) && (dy < clickAbleComponent->clickArea.y)) {
                std::cout << "Button was pressed." << std::endl;
            }
        }

        return std::vector<Event*>();
    }

public:

    SimpleButtonClickEventHandler() {}
    ~SimpleButtonClickEventHandler() {}
};

#endif //SDLRTS_SIMPLEBUTTONCLICKEVENTHANDLER_H
