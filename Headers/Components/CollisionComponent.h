//
// Created by Julian  on 18/12/15.
//

#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "Vector.h"
#include "BaseComponent.h"

struct CollisionComponent : BaseComponent
{
	float radius; 
	TransformComponent* transformComponent; 

	CollisionComponent(float radius, TransformComponent* transformComponent = nullptr)
	{
		this->transformComponent = transformComponent; 
		this->radius = radius; 
	}
};

#endif //CLICKABLECOMPONENT_H
