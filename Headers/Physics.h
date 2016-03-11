#ifndef PHYSICS_H
#define PHYSICS_H

#include "Events\IEventArgs.h"
#include "Events\CollisionEventArgs.h"
#include "Components\SimplePhysicsComponent.h"
#include "Components\TransformComponent.h"
#include "ComponentCollectionRepository.h"

class Physics
{
private:

	unsigned int width; 
	unsigned int height; 
	unsigned int quadFactor = 10; 

	list<IEventArgs> events; 

public:

	Physics(unsigned int width, unsigned int height)
	{
		this->width = width; 
		this->height = height;
	}

	void Update(ComponentCollectionRepository* componentCollectionRepository)
	{
		auto physicsComponents = componentCollectionRepository->Select<SimplePhysicsComponent>();

		for (auto physicsComponentList : *physicsComponents) {
			for (auto physicsComponent : *physicsComponentList) {

				float x = physicsComponent.transformComponent->position.x; 
				float y = physicsComponent.transformComponent->position.y;
				float r = physicsComponent.radius; 

				for (auto currentPhysicsComponentList : *physicsComponents) {
					for (auto currentPhysicsComponent : *currentPhysicsComponentList) {

						if (currentPhysicsComponent.id == physicsComponent.id) {
							continue; 
						}

						float dx = x - currentPhysicsComponent.transformComponent->position.x;	
						float dy = y - currentPhysicsComponent.transformComponent->position.y;

						float dr = r + currentPhysicsComponent.radius; 
						
						if ((dx*dx + dy*dy) < (dr*dr)) {
							this->events.push_back(CollisionEventArgs(&physicsComponent, &currentPhysicsComponent));
						}
					}
				}
			}
		}
	}

	list<IEventArgs>* GetEvents()
	{
		return &this->events; 
	}

};

#endif // PHYSICS_H