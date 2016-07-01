#ifndef COLLISION_EVENT_ARGS_H
#define COLLISION_EVENT_ARGS_H

#include "IEventArgs.h"
#include "Components/PhysicsComponent.h"
#include <string>

using namespace std; 

class CollisionEventArgs : public IEventArgs
{
public:
	
	CollisionEventArgs(unsigned int physicsComponentId1, unsigned int physicsComponentId2)
	{
		this->collectionName1 = collectionName1; 
		this->collectionName2 = collectionName2; 

		this->physicsComponentId1 = physicsComponentId1;
		this->physicsComponentId2 = physicsComponentId2;
	}

	string collectionName1;
	string collectionName2;

	unsigned int physicsComponentId1;
	unsigned int physicsComponentId2;
};

#endif // COLLISION_EVENT_ARGS_H