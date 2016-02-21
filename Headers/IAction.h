#ifndef IACTION_H
#define IACTION_H

#include "Events\IEventArgs.h"
#include "Entity.h"
#include "ComponentRepository.h"
#include <list>

class IAction
{
private:

	Entity* entity; 
	ComponentRepository* componentRepository; 

public:

	IAction(Entity* entity, ComponentRepository* componentRepository)
	{
		this->entity = entity; 
		this->componentRepository = componentRepository; 
	}

	Entity* GetEntity() 
	{ 
		return this->entity; 
	}

	ComponentRepository* GetComponentRepository() 
	{ 
		return this->componentRepository; 
	}

	virtual IEventArgs* Update(IEventArgs* events) = 0; 
};

#endif // IACTION_H
