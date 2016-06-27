#ifndef ASTEROID_ACTION_H
#define ASTEROID_ACTION_H

#include "Actions/IAction.h"
#include "Components/PhysicsComponent.h"
#include "Graphics/Graphics.h"
#include "SpaceGameEntityConstructor.h"
#include <Graphics/ProceduralAsteroidGraphicsResource.h>

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
	AsteroidAction(IStage* stage): IAction(stage)
	{
		this->width = stage->GetGameApp()->GetGraphics()->WindowWidth();
		this->height = stage->GetGameApp()->GetGraphics()->WindowHeight();

		auto numAsteroids = 2; 

		auto graphics = this->GetParentStage()->GetGameApp()->GetGraphics(); 
		auto componentCollectionRepository = this->GetParentStage()->GetComponentCollectionRepository(); 

		vector<int> asteroidGraphicsResIds;

		for (auto i = 0; i < numAsteroids; i++) {
			asteroidGraphicsResIds.push_back(graphics->AddGraphicsResource(new ProceduralAsteroidGraphicsResource(20.0f, 1.2f, 10)));
		}

		SpaceGameEntityConstructor::ConstructEnemyAsteroids(componentCollectionRepository, asteroidGraphicsResIds, this->width, this->height, numAsteroids);
	
		auto task = new CollisionPhysicsTask("EnemyAsteroids", "PlayerSpaceShipProjectiles"); 
		auto handler = [this](const CollisionEventArgs& collisionEventArgs) {this->OnProjectileCollision(collisionEventArgs); };

		task->RegisterListener<CollisionEventArgs>(handler); 
	}
	//-------------------------------------------------------------------------------
	// Name: Update
	// Desc: 
	//-------------------------------------------------------------------------------
	void Update() override final
	{
		auto componentCollectionRepository = this->GetParentStage()->GetComponentCollectionRepository();
		this->SolveAsteroidPhysics(componentCollectionRepository); 
	}
	//-------------------------------------------------------------------------------
	// Name: SolveAsteroidPhysics
	// Desc: do logic/physics for the enemy asteroids 
	//-------------------------------------------------------------------------------
	static void SolveAsteroidPhysics(ComponentCollectionRepository* componentCollectionRepository) 
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

		auto pPlayer = &playerPhysicsComponent; 

		for (auto& physicsComponent : *asteroidPhysicsComponents) {

			auto playerTransformComponent = componentCollectionRepository->Select<TransformComponent>(playerPhysicsComponent.transformComponentId);
			auto transformComponent = componentCollectionRepository->Select<TransformComponent>(physicsComponent.transformComponentId); 

			auto distVector = playerTransformComponent->position - transformComponent->position;

			// calculate acceleration on asteroids
			auto accel = 10000.0f * physicsComponent.mass / powf(distVector.Length(), 2.0f);
			auto angle = distVector.Angle();

			physicsComponent.velocity.x += accel*cosf(angle);
			physicsComponent.velocity.y += accel*sinf(angle);

			transformComponent->position.x += physicsComponent.velocity.x;
			transformComponent->position.y += physicsComponent.velocity.y;

			auto currentAngle = transformComponent->orientation.Angle();
			transformComponent->orientation = Vector2D(currentAngle + physicsComponent.angularVelocity);
		}
	}

	//-------------------------------------------------------------------------------
	// Name: OnProjectileCollision
	// Desc: 
	//-------------------------------------------------------------------------------
	void OnProjectileCollision(const CollisionEventArgs collisionEventArgs) const
	{
		// delete myself	
	}

};

#endif // ASTEROID_ACTION_H