#ifndef PLAYER_ACTIONS_H
#define PLAYER_ACTIONS_H

#include "GameEntityConstructor.h"
#include "IAction.h"
#include "Events\IEventArgs.h"
#include "Events\ButtonEventArgs.h"
#include "Entity.h"
#include "Components\TransformComponent.h"
#include "Components\SimplePhysicsComponent.h"


class PlayerActions : public IAction
{
private:

	IEventArgs* HandleButtonEvent(ButtonEventArgs* buttonEventArgs)
	{
		Entity* entity = this->GetEntity(); 
		auto transform = entity->GetComponent<TransformComponent>(); 
		
		if ((buttonEventArgs->Key() == LEFT_ARROW || buttonEventArgs->Key() == RIGHT_ARROW) 
			&& buttonEventArgs->Released()) {
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

		if (buttonEventArgs->Key() == UP_ARROW && buttonEventArgs->Released()) {

			auto componentRepository = this->GetComponentRepository();
			auto physics = entity->GetComponent<SimplePhysicsComponent>();
			auto xVel = physics->velocity.x; 

			EntityConstructor::ConstructBasicProjectile(componentRepository, 1, transform->position, Vector2D(xVel, -1.0f));
		}

		return nullptr; 
	}
	
public:

	PlayerActions(Entity* entity, ComponentRepository* componentRepository) 
		: IAction(entity, componentRepository) {}

	IEventArgs* Update(IEventArgs* event) 
	{
		ButtonEventArgs* buttonEventArgs = static_cast<ButtonEventArgs*>(event);
		
		if (event != nullptr) {
			this->HandleButtonEvent(buttonEventArgs);
			return nullptr; 

		}

		return nullptr; 
	}

};

#endif