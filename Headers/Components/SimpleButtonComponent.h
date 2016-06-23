#ifndef SIMPLE_BUTTON_COMPONENT_H
#define SIMPLE_BUTTON_COMPONENT_H

#include "Components/BaseComponent.h"

struct SimpleButtonComponent : public BaseComponent
{
public:

	bool mouseOverState; 
	bool toggleState;

	unsigned int transformComponentId; 

	Vector2D size;

	SimpleButtonComponent() : mouseOverState(false), toggleState(false), transformComponentId(0)
	{}

	explicit SimpleButtonComponent(Vector2D size) : mouseOverState(false), toggleState(false), transformComponentId(0)
	{
		this->size = size; 
	}
};

#endif // SIMPLE_BUTTON_COMPONENT_H