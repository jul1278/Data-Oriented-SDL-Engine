#ifndef ASTEROID_ACTION_H
#define ASTEROID_ACTION_H

#include "IAction.h"
#include <Vector.h>
#include <Utility/MathUtility.h>
#include <Components/PhysicsComponent.h>
#include <functional>

class AsteroidAction : public IAction
{
private:

	unsigned int width; 
	unsigned int height; 

public:

	//-------------------------------------------------------------------------------
	// Name: AsteroidAction
	// Desc: 
	//-------------------------------------------------------------------------------
	AsteroidAction(unsigned int width, unsigned int height)
	{
		this->width = width; 
		this->height = height; 
	}
	//-------------------------------------------------------------------------------
	// Name: Update
	// Desc: 
	//-------------------------------------------------------------------------------
	void Update(ComponentCollectionRepository* componentCollectionRepository) override final
	{
		this->SolveAsteroidPhysics(componentCollectionRepository); 
	}
	//-------------------------------------------------------------------------------
	// Name: SolveAsteroidPhysics
	// Desc: do logic/physics for the enemy asteroids 
	//-------------------------------------------------------------------------------
	void SolveAsteroidPhysics(ComponentCollectionRepository* componentCollectionRepository) const
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

			// 
			auto distVector = playerPhysicsComponent.transformComponent->position - physicsComponent.transformComponent->position;

			// calculate acceleration on asteroids
			auto accel = 10000.0f * physicsComponent.mass / powf(distVector.Length(), 2.0f);
			auto angle = distVector.Angle();

			physicsComponent.velocity.x += accel*cosf(angle);
			physicsComponent.velocity.y += accel*sinf(angle);

			physicsComponent.transformComponent->position.x += physicsComponent.velocity.x;
			physicsComponent.transformComponent->position.y += physicsComponent.velocity.y;

			auto currentAngle = physicsComponent.transformComponent->orientation.Angle();
			physicsComponent.transformComponent->orientation = Vector2D(currentAngle + physicsComponent.angularVelocity);
		}
	}
};

#endif // ASTEROID_ACTION_H