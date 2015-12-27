//
// Created by Julian  on 10/12/15.
//
#ifndef SDLRTS_SIMPLE_BUTTON_EVENT_HANDLER_H
#define SDLRTS_SIMPLE_BUTTON_EVENT_HANDLER_H

#include "Events/IEventHandler.h"
#include "ComponentType.h"
#include "Components/GraphicsComponent.h"
#include "Components/TransformComponent.h"

class SimpleButtonEventHandler : public IEventHandler
{
public:

	SimpleButtonEventHandler(int id) : IEventHandler(id) {}; 

	void HandleEvent(Event* event, Events* events) override final
	{
		switch (event->eventType) {
			case EVENT_MOUSE_OVER:
			{
				this->HandleEventMouseOver(static_cast<MouseOverEvent*>(event->eventInfo), events);
				break; 
			}
			case EVENT_MOUSE_OFF:
			{
				this->HandleEventMouseOff(static_cast<MouseOffEvent*>(event->eventInfo), events);
				break; 
			}
			case EVENT_MOUSE_UP:
			{
				this->HandleEventMouseUp(static_cast<MouseUpEvent*>(event->eventInfo), events);
				break; 
			}
		}
	}

	void HandleEventMouseOver(MouseOverEvent* mouseOverEvent, Events* events)
	{
		auto clickableComponents = &this->Components()[CLICKABLE_COMPONENT];
		auto transformComponents = &this->Components()[GRAPHICS_COMPONENT]; 

		ClickAbleComponent* clickAbleComponent = static_cast<ClickAbleComponent*>((*clickableComponents)[mouseOverEvent->sourceId]); 
		TransformComponent* transformComponent = static_cast<TransformComponent*>((*transformComponents)[clickAbleComponent->transformId]); 
		
		transformComponent->scale.x = 1.25f; 
		transformComponent->scale.y = 1.25f; 
	}

	void HandleEventMouseOff(MouseOffEvent* mouseOffEvent, Events* events)
	{
		auto clickableComponents = &this->Components()[CLICKABLE_COMPONENT];
		auto transformComponents = &this->Components()[GRAPHICS_COMPONENT];

		ClickAbleComponent* clickAbleComponent = static_cast<ClickAbleComponent*>((*clickableComponents)[mouseOffEvent->sourceId]);
		TransformComponent* transformComponent = static_cast<TransformComponent*>((*transformComponents)[clickAbleComponent->transformId]);

		transformComponent->scale.x = 1.0f;
		transformComponent->scale.y = 1.0f;
	}

	void HandleEventMouseUp(MouseUpEvent* mouseUpEvent, Events* events)
	{
		// get the component we're talking about
		auto clickableComponents = &this->Components()[CLICKABLE_COMPONENT];
		ClickAbleComponent* clickAbleComponent = static_cast<ClickAbleComponent*>((*clickableComponents)[mouseUpEvent->sourceId]);
	}
};

#endif // SDLRTS_SIMPLE_BUTTON_EVENT_HANDLER_H