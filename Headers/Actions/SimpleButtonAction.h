#ifndef SIMPLE_BUTTON_ACTION_H
#define SIMPLE_BUTTON_ACTION_H

#include "Game/IStage.h"
#include "Actions/IAction.h"
#include "Components/SimpleButtonComponent.h"
#include <Events/SDLEventCollector.h>
#include <Events/MouseMotionEventArgs.h>
#include <Events/MouseButtonEventArgs.h>

class MouseMotionEventArgs;
class MouseButtonEventArgs;

class SimpleButtonAction : public IAction
{
private:

	IStage* stage; 
	int buttonId; 

public:


	explicit SimpleButtonAction(float x, float y, float width, float height, const string& text, IStage* stage)
		: IAction(stage)
	{
			
	}

	explicit SimpleButtonAction(IStage* stage, SimpleButtonComponent* simpleButtonComponent, SDLEventCollector* sdlEventCollector)
		: IAction(stage)
	{
		this->buttonId = simpleButtonComponent->id; 

		sdlEventCollector->RegisterMouseClickHandler(simpleButtonComponent, bind(&SimpleButtonAction::OnMouseClick, this, placeholders::_1)); 
		sdlEventCollector->RegisterMouseOverHandler(simpleButtonComponent, bind(&SimpleButtonAction::OnMouseOver, this, placeholders::_1));
	}


	virtual void OnMouseClick(const MouseButtonEventArgs& mouseButtonEventArgs)
	{
		
	}
	
	virtual void OnMouseOver(const MouseMotionEventArgs& mouseMotionEventArgs)
	{
		auto componentCollectionRepository = this->stage->GetComponentCollectionRepository();
		auto buttonComponent = componentCollectionRepository->Select<SimpleButtonComponent>(this->buttonId);

		if (mouseMotionEventArgs.MouseOver()) {
			buttonComponent->transformComponent->scale = Vector2D(1.2f, 1.2f); 
		} else {
			buttonComponent->transformComponent->scale = Vector2D(1.0f, 1.0f);
		}
	}
};

#endif // SIMPLE_BUTTON_ACTION_H