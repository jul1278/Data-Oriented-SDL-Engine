//
// Created by Julian  on 18/12/15.
//

#ifndef VELOCITY_COMPONENT_H
#define VELOCITY_COMPONENT_H

#include "BaseComponent.h"
#include "Utility/Vector.h"

struct VelocityComponent : public BaseComponent
{
	Vector2D velocity; 
	unsigned int transformComponentId;

	VelocityComponent()
	{
		this->transformComponentId = 0; 
	}

	VelocityComponent(Vector2D velocity, unsigned int transformComponentId) : velocity(velocity), transformComponentId(transformComponentId) {}
};

#endif // VELOCITY_COMPONENT_H