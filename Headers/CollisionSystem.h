//
// Created by Julian  on 10/12/15.
//
#ifndef SDLRTS_COLLISION_SYSTEM_H
#define SDLRTS_COLLISION_SYSTEM_H

#include "Entity.h"
#include "Components/TransformComponent.h"
#include "Components/CollisionComponent.h"
#include <map>

using namespace std; 

class CollisionSystem
{
private:

public:

	CollisionSystem(); 
	~CollisionSystem(); 

	void Update()
	{
		//for each possible collision
		//	check for collision, record it if a collision occurs

		//for each found collision
		//	handle collision, record the collision response(delete object, ignore, etc.)

		//for each collision response
		//	modify collision world according to response
	}
};

#endif
