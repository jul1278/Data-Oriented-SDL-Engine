#ifndef EXIT_BOUNDS_EVENT_ARGS_H
#define EXIT_BOUNDS_EVENT_ARGS_H

#include "Events/IEventArgs.h"

class ExitBoundsEventArgs : public IEventArgs
{
public:

	ExitBoundsEventArgs(unsigned int transformComponentId, unsigned int physicsComponentId, string collectionName, Vector2D exitPoint)
	{
		this->transformComponentId = transformComponentId; 
		this->physicsComponentId = physicsComponentId; 
		this->collectionName = collectionName;
		this->exitPoint = exitPoint; 
	}

	unsigned int transformComponentId;
	unsigned int physicsComponentId;

	Vector2D exitPoint;
	string collectionName;
};

#endif // EXIT_BOUNDS_EVENT_ARGS_H