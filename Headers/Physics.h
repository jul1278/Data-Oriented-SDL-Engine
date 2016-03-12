#ifndef PHYSICS_H
#define PHYSICS_H

#include "Events\IEventArgs.h"
#include "Events\CollisionEventArgs.h"
#include "Components\SimplePhysicsComponent.h"
#include "Components\PhysicsComponent.h"
#include "Components\TransformComponent.h"
#include "ComponentCollectionRepository.h"

class Physics
{
private:

	int width; 
	int height; 

public:

	Physics(int width, int height) 
	{
		this->width = width; 
		this->height = height;
	}

	//-------------------------------------------------------------------------------
	// Name: SolvePhysics
	// Desc: 
	//-------------------------------------------------------------------------------
	void SolvePhysics(ComponentCollectionRepository* componentCollectionRepository, const string& collectionName)
	{
		auto physicsComponents = componentCollectionRepository->SelectFromCollection<PhysicsComponent>(collectionName); 

		if (physicsComponents == nullptr) {
			return; 
		}

		for (auto component : *physicsComponents) {
			component.transformComponent->orientation = Vector2D(component.angularVelocity) + component.transformComponent->orientation;
			component.transformComponent->position.x += component.velocity.x; 
			component.transformComponent->position.y += component.velocity.y; 
		}
	}
	//-------------------------------------------------------------------------------
	// Name: SolveSimplePhysics
	// Desc: 
	//-------------------------------------------------------------------------------
	void SolveSimplePhysics(ComponentCollectionRepository* componentCollectionRepository, const string& collectionName)
	{
		auto physicsComponents = componentCollectionRepository->SelectFromCollection<SimplePhysicsComponent>(collectionName);

		if (physicsComponents == nullptr) {
			return; 
		}

		for (auto component : *physicsComponents) {
			component.transformComponent->position.x += component.velocity.x;
			component.transformComponent->position.y += component.velocity.y;
		}
	}
};

#endif // PHYSICS_H