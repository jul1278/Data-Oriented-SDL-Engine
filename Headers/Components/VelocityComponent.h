//
// Created by Julian  on 18/12/15.
//

#ifndef VELOCITY_COMPONENT_H
#define VELOCITY_COMPONENT_H

#include "BaseComponent.h"
#include "TransformComponent.h"

struct VelocityComponent : BaseComponent
{
	Vector2D velocity; 
	
	TransformComponent* transformComponent;

	VelocityComponent()
	{
		this->transformComponent = nullptr; 
	}

	VelocityComponent(Vector2D velocity, TransformComponent* transformComponent = nullptr)
	{
		this->transformComponent = transformComponent;
		this->velocity = velocity; 
	}
};

#endif // VELOCITY_COMPONENT_H