#ifndef COLLISION_EVENT_ARGS_H
#define COLLISION_EVENT_ARGS_H

#include "IEventArgs.h"
#include <string>

using namespace std; 

class CollisionEventArgs : public IEventArgs
{
public:
	
	string collectionName1;
	string collectionName2;

	unsigned int physicsComponentId1;
	unsigned int physicsComponentId2;

	unsigned int entityId1;
	unsigned int entityId2;

	CollisionEventArgs(string collection1, string collection2, unsigned int physicsComponentId1, 
		unsigned int physicsComponentId2, unsigned int entityId1, unsigned int entityId2) :
		collectionName1(collection1), collectionName2(collection2),
		physicsComponentId1(physicsComponentId1), physicsComponentId2(physicsComponentId2),
		entityId1(entityId1), entityId2(entityId2)
	{

	}
};

#endif // COLLISION_EVENT_ARGS_H