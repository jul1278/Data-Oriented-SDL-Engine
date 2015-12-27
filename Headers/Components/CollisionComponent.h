//
// Created by Julian  on 18/12/15.
//

#ifndef SDLRTS_COLLISION_COMPONENT_H
#define SDLRTS_COLLISION_COMPONENT_H

#include "Vector.h"
#include "BaseComponent.h"

struct CollisionComponent : IBaseComponent
{
	int transformId;
	float radius; 

	CollisionComponent(int transformId, float radius)
	{
		this->transformId = transformId;
		this->radius = radius; 
	}
};

#endif //SDLRTS_CLICKABLECOMPONENT_H