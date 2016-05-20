#ifndef INTERSECTION_EVENT_ARGS_H
#define INTERSECTION_EVENT_ARGS_H

#include "Events/IEventArgs.h"
#include <Components/TransformComponent.h>

class IntersectionEventArgs : public IEventArgs
{
private:

	TransformComponent* component1; 
	TransformComponent* component2; 

public:

	IntersectionEventArgs(TransformComponent* component1, TransformComponent* component2)
	{
		this->component1 = component1; 
		this->component2 = component2; 
	}

	~IntersectionEventArgs() override
	{
		// don't delete our components they belong to somewhere else
	}

	TransformComponent* TransformComponent1() const
	{
		return this->component1; 
	}

	TransformComponent* TransformComponent2() const
	{
		return this->component2; 
	}

};


#endif // INTERSECTION_EVENT_ARGS_H
