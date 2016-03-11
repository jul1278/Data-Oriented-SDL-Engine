#ifndef COLLISION_EVENT_ARGS_H
#define COLLISION_EVENT_ARGS_H

#include "Components\SimplePhysicsComponent.h"
#include "IEventArgs.h"

class CollisionEventArgs : public IEventArgs
{
public:
	
	CollisionEventArgs(SimplePhysicsComponent* simplePhysicsComponent1, 
		SimplePhysicsComponent* simplePhysicsComponent2) 
		: IEventArgs(CollisionEvent) 
	{
		this->simplePhysicsComponent1 = simplePhysicsComponent1; 
		this->simplePhysicsComponent2 = simplePhysicsComponent2; 
	}

	SimplePhysicsComponent* simplePhysicsComponent1; 
	SimplePhysicsComponent* simplePhysicsComponent2;
};

#endif // COLLISION_EVENT_ARGS_H