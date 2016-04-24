#ifndef SIMPLE_STATE_COMPONENT_H
#define SIMPLE_STATE_COMPONENT_H

#include "Components\BaseComponent.h"

struct SimpleStateComponent : public BaseComponent
{
	unsigned int state; 

	SimpleStateComponent(unsigned int initalState) : state(initalState) {}
};

#endif // SIMPLE_STATE_COMPONENT_H