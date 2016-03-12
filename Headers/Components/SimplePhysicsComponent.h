//
// Created by Julian  on 18/12/15.
//

#ifndef SIMPLE_PHYSICS_COMPONENT_H
#define SIMPLE_PHYSICS_COMPONENT_H

#include "BaseComponent.h"
#include "TransformComponent.h"

struct SimplePhysicsComponent : BaseComponent
{
	Vector2D velocity; 
	
	TransformComponent* transformComponent;

	SimplePhysicsComponent()
	{
		this->transformComponent = nullptr; 
	}

	SimplePhysicsComponent(Vector2D velocity, TransformComponent* transformComponent = nullptr)
	{
		this->transformComponent = transformComponent;
		this->velocity = velocity; 
	}
};

#endif //SIMPLE_PHYSICS_COMPONENT