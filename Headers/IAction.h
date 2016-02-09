#ifndef IACTION_H
#define IACTION_H

#include "Events\IEventArgs.h"
#include "Entity.h"
#include <list>

class IAction
{
private:

	Entity* entity; 

public:

	IAction(Entity* entity)
	{
		this->entity = entity; 
	}

	Entity* GetEntity() { return this->entity; }

	virtual IEventArgs* Update(IEventArgs* events) = 0; 
};

#endif // IACTION_H
