#ifndef PLAYER_ACTIONS_H
#define PLAYER_ACTIONS_H

#include "IAction.h"
#include "Events\IEventArgs.h"
#include "Events\ButtonEventArgs.h"
#include "Entity.h"
#include "Components\TransformComponent.h"
#include "Components\SimplePhysicsComponent.h"


class PlayerActions : public IAction
{
private:

	IEventArgs* HandleButtonEvent(ButtonEventArgs* buttonEventArgs, Entity* entity)
	{
		auto transform = entity->GetComponent<TransformComponent>(); 


		if (buttonEventArgs->Released()) {
			auto physics = entity->GetComponent<SimplePhysicsComponent>();
			physics->velocity = Vector2D(0.0f, 0.0f);
			return nullptr;
		}

		if (buttonEventArgs->Key() == LEFT_ARROW && transform->position.x > 20) {
			auto physics = entity->GetComponent<SimplePhysicsComponent>(); 
			physics->velocity = Vector2D(-2.0f, 0.0f); 
			return nullptr; 
		} 

		if (buttonEventArgs->Key() == RIGHT_ARROW && transform->position.x < 620) {
			auto physics = entity->GetComponent<SimplePhysicsComponent>();
			physics->velocity = Vector2D(2.0f, 0.0f);
			return nullptr;
		}

		return nullptr; 
	}
	
public:

	PlayerActions(Entity* entity) : IAction(entity) {}

	IEventArgs* Update(IEventArgs* event) 
	{
		ButtonEventArgs* buttonEventArgs = static_cast<ButtonEventArgs*>(event);

		if (buttonEventArgs != nullptr) {
			this->HandleButtonEvent(buttonEventArgs, this->GetEntity()); 
		}

		return nullptr; 
	}

};

#endif