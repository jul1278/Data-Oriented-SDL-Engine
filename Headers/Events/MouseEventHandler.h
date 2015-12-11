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
#include "Events/Events.h" 
#include <iostream>

class MouseEventHandler
{
private:

public:

    MouseEventHandler(){}
    ~MouseEventHandler() {}

    void Handle(Event* event, TransformComponent* transformComponent, ClickAbleComponent* clickAbleComponent)
    {
        MouseMoveEvent* mouseMoveEvent = static_cast<MouseMoveEvent*>(event->eventInfo);

        if (mouseMoveEvent == nullptr) {
            return;
        }
		
		Vector2D lastPos = mouseMoveEvent->lastPos; 
		Vector2D currPos = mouseMoveEvent->currPos; 

		
        float prevDx = mouseMoveEvent->lastPos.x - transformComponent->position.x;
        float prevDy = mouseMoveEvent->lastPos.y - transformComponent->position.y;

        float currDx = mouseMoveEvent->currPos.x - transformComponent->position.x;
        float currDy = mouseMoveEvent->currPos.y - transformComponent->position.y;

        bool lastPosWasInside = false;
        bool currentPosInside = false;

        // if the lastPos was inside the clickArea then
        if (prevDx > 0.0f && prevDy > 0.0f)
        {
            if ((prevDx < clickAbleComponent->clickArea.x) && (prevDy < clickAbleComponent->clickArea.y)) {
                lastPosWasInside = true; 
            } else
            {
                lastPosWasInside = false;
            }
        }
		
        if (currDx > 0.0f && currDy > 0.0f) {
            if ((currDx < clickAbleComponent->clickArea.x) && (currDy < clickAbleComponent->clickArea.y)) {
                currentPosInside = true; 
            } else {
                currentPosInside = false; 
            }
        }        

        if (currentPosInside == true && lastPosWasInside == false) {
            transformComponent->scale = Vector2D(1.25f, 1.25f);
        } else if (lastPosWasInside == true && currentPosInside == false) {
            // otherwise default scale
            transformComponent->scale = Vector2D(1.0f, 1.0f);
        }
    }
};



#endif
