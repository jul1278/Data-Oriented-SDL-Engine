#ifndef SIMPLE_PROJECTILE_ACTIONS_H
#define SIMPLE_PROJECTILE_ACTIONS_H

#include "IAction.h"
#include "Events\IEventArgs.h"
#include "Events\ButtonEventArgs.h"
#include "Entity.h"
#include "Components\TransformComponent.h"
#include "Components\SimplePhysicsComponent.h"

class SimpleProjectileActions : public IAction
{
public:

	SimpleProjectileActions(Entity* entity, ComponentRepository* componentRepository)
		: IAction(entity, componentRepository) {}

	IEventArgs* Update(IEventArgs* event)
	{
		return nullptr; 
	}
};

#endif // SIMPLE_PROJECTILE_ACTIONS_H