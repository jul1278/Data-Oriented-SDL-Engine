#ifndef PHYSICS_H
#define PHYSICS_H

#include "Events\IEventArgs.h"
#include "Events\CollisionEventArgs.h"
#include "Components\SimplePhysicsComponent.h"
#include "Components\PhysicsComponent.h"
#include "Components\TransformComponent.h"
#include "ComponentCollectionRepository.h"
#include "Utility\MathUtility.h"

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
	// Name: SolveAsteroidPhysics
	// Desc: temp function to do logic/physics for the enemy asteroids 
	//-------------------------------------------------------------------------------
	void SolveAsteroidPhysics(ComponentCollectionRepository* componentCollectionRepository)
	{
		auto asteroidPhysicsComponents = componentCollectionRepository->SelectFromCollection<PhysicsComponent>("EnemyAsteroids"); 
		auto playerPhysicsComponents = componentCollectionRepository->SelectFromCollection<PhysicsComponent>("PlayerSpaceShip"); 

		if (asteroidPhysicsComponents == nullptr || asteroidPhysicsComponents->size() == 0) {
			return; 
		}

		if (playerPhysicsComponents == nullptr || playerPhysicsComponents->size() == 0) {
			return; 
		}

		auto playerPhysicsComponent = playerPhysicsComponents->front(); 

		for (auto physicsComponent : *asteroidPhysicsComponents) {

			if (physicsComponent.transformComponent->position.x > this->width || physicsComponent.transformComponent->position.x <= 0 ||
				physicsComponent.transformComponent->position.y > this->height || physicsComponent.transformComponent->position.y <= 0) {

				physicsComponent.transformComponent->position.x = MathUtility::RandomFloatUniformDist()*this->width; 
				physicsComponent.transformComponent->position.y = MathUtility::RandomFloatUniformDist()*this->height; 
				
				continue; 
			}

			// 
			auto distVector = playerPhysicsComponent.transformComponent->position - physicsComponent.transformComponent->position;

			// calculate acceleration on asteroids
			auto accel = 10000.0f * physicsComponent.mass / (distVector.Length()*distVector.Length()); 
			auto angle = distVector.Angle(); 

			physicsComponent.velocity.x += accel*cosf(angle); 
			physicsComponent.velocity.y += accel*sinf(angle); 

			physicsComponent.transformComponent->position.x += physicsComponent.velocity.x;
			physicsComponent.transformComponent->position.y += physicsComponent.velocity.y; 



		}
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