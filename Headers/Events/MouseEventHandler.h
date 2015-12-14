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
#include "Events/IEventHandler.h"
#include <iostream>

// Handle mouse events, click, motion, etc
class MouseEventHandler : public IEventHandler
{
public:
	void HandleEvent(Event* event, Events* events) override final
	{
		MouseMoveEvent* mouseMoveEvent = static_cast<MouseMoveEvent*>(event->eventInfo);

		auto clickableComponents = &this->Components()[CLICKABLE_COMPONENT]; 
		auto transformComponents = &this->Components()[TRANSFORM_COMPONENT]; 
		
		for (auto baseComponent : *clickableComponents) {

			ClickAbleComponent* clickAbleComponent = static_cast<ClickAbleComponent*>(baseComponent.second); 
			TransformComponent* transformComponent = static_cast<TransformComponent*>((*transformComponents)[clickAbleComponent->transformId]);

			Vector2D lastPos = mouseMoveEvent->lastPos;
			Vector2D currPos = mouseMoveEvent->currPos;

			// TODO: vector diff here 
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
				}
				else
				{
					lastPosWasInside = false;
				}
			}

			// 
			if (currDx > 0.0f && currDy > 0.0f) {

				if ((currDx < clickAbleComponent->clickArea.x) && (currDy < clickAbleComponent->clickArea.y)) {
					currentPosInside = true;
				}
				else {
					currentPosInside = false;
				}
			}

			if (currentPosInside == true && lastPosWasInside == false) {

				int targetId = clickAbleComponent->eventHandlerId;
				int sourceId = clickAbleComponent->id; 

				Event* mouseOverEvent = new Event(EVENT_MOUSE_OVER, new MouseOverEvent(targetId, sourceId));
				events->PostEvent(event);

			} else if (lastPosWasInside == true && currentPosInside == false) {

				int targetId = clickAbleComponent->eventHandlerId; 
				int sourceId = clickAbleComponent->id; 

				Event* mouseOffEvent = new Event(EVENT_MOUSE_OFF, new MouseOffEvent(targetId, sourceId));
				events->PostEvent(event);
			}
		}		
	};
};

#endif
