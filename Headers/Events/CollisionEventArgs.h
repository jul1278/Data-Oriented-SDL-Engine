#ifndef COLLISION_EVENT_ARGS_H
#define COLLISION_EVENT_ARGS_H

#include "IEventArgs.h"
#include "Components/PhysicsComponent.h"
#include <string>

using namespace std; 

class CollisionEventArgs : public IEventArgs
{
public:
	
	CollisionEventArgs(PhysicsComponent* simplePhysicsComponent1, 
		PhysicsComponent* simplePhysicsComponent2) 
		: IEventArgs(CollisionEvent) 
	{
		this->physicsComponent1 = simplePhysicsComponent1; 
		this->physicsComponent2 = simplePhysicsComponent2; 
	}

	string collectionName; 

	PhysicsComponent* physicsComponent1; 
	PhysicsComponent* physicsComponent2;
};

#endif // COLLISION_EVENT_ARGS_H