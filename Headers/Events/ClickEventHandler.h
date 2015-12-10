//
// Created by Julian  on 10/12/15.
//
#ifndef SDLRTS_CLICK_EVENT_HANDLER_H
#define SDLRTS_CLICK_EVENT_HANDLER_H

#include "Vector.h"
#include "Components/BaseComponent.h"
#include "Components/ClickableComponent.h"
#include "Components/TransformComponent.h"
#include "Events/Event.h"
#include <iostream>

class ClickEventHandler
{
private:

public:

    ClickEventHandler(){}
    ~ClickEventHandler() {} 

    void Handle(Event* event, TransformComponent* transformComponent, ClickAbleComponent* clickAbleComponent)
    {
        MouseClickEvent* mouseClickEvent = static_cast<MouseClickEvent*>(event->eventInfo);

        if (mouseClickEvent == nullptr) {
            return;
        }

        float dx = mouseClickEvent->pos.x - transformComponent->position.x;
        float dy = mouseClickEvent->pos.y - transformComponent->position.y;

        if (dx > 0.0f && dy > 0.0f)
        {
            if ((dx < clickAbleComponent->clickArea.x) && (dy < clickAbleComponent->clickArea.y)) {
                std::cout << "Button was pressed." << std::endl;
            }
        }
    }
};



#endif
