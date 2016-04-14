#ifndef SIMPLE_BUTTON_COMPONENT_H
#define SIMPLE_BUTTON_COMPONENT_H

#include "Components/BaseComponent.h"
#include "TransformComponent.h"

class SimpleButtonComponent : public BaseComponent
{
public:

	bool mouseOverState; 
	bool toggleState;

	TransformComponent* transformComponent;

	Vector2D size;

	SimpleButtonComponent() : mouseOverState(false), toggleState(false), transformComponent(nullptr)
	{}

	explicit SimpleButtonComponent(Vector2D size): mouseOverState(false), toggleState(false), transformComponent(nullptr)
	{
		this->size = size; 
	}
};

#endif // SIMPLE_BUTTON_COMPONENT_H