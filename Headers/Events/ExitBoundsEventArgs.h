#ifndef EXIT_BOUNDS_EVENT_ARGS_H
#define EXIT_BOUNDS_EVENT_ARGS_H

#include "Events/IEventArgs.h"

class ExitBoundsEventArgs : public IEventArgs
{
public:

	ExitBoundsEventArgs(unsigned transformComponentId, unsigned physicsComponentId, unsigned entityId, string collectionName, Vector2D exitPoint)
	{
		this->entityId = entityId; 
		this->transformComponentId = transformComponentId; 
		this->physicsComponentId = physicsComponentId; 
		this->collectionName = collectionName;
		this->exitPoint = exitPoint; 
	}

	unsigned entityId;
	unsigned transformComponentId;
	unsigned physicsComponentId;

	Vector2D exitPoint;
	string collectionName;
};

#endif // EXIT_BOUNDS_EVENT_ARGS_H