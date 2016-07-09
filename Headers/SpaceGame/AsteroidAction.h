#ifndef ASTEROID_ACTION_H
#define ASTEROID_ACTION_H

#include "Actions/IAction.h"
#include "Components/PhysicsComponent.h"
#include "Graphics/Graphics.h"
#include "SpaceGameEntityConstructor.h"
#include <Graphics/ProceduralAsteroidGraphicsResource.h>
#include <Physics/ExitBoundsTask.h>
#include <Physics/VelocityTask.h>

class AsteroidAction : public IAction
{
private:

	unsigned int width; 
	unsigned int height; 

	vector<int> asteroidGraphicsResIds;

public:


	//-------------------------------------------------------------------------------
	// Name: AsteroidAction
	// Desc: 
	//-------------------------------------------------------------------------------
	AsteroidAction(IStage* stage) : IAction(stage)
	{
		this->width = stage->GetGameApp()->GetGraphics()->WindowWidth();
		this->height = stage->GetGameApp()->GetGraphics()->WindowHeight();
		
		auto initNumAsteroids = 1; 

		auto graphics = this->GetParentStage()->GetGameApp()->GetGraphics(); 
		auto componentCollectionRepository = this->GetParentStage()->GetComponentCollectionRepository(); 

		for (auto i = 0; i < 4*initNumAsteroids; i++) {
			this->asteroidGraphicsResIds.push_back(graphics->AddGraphicsResource(new ProceduralAsteroidGraphicsResource(20.0f, 1.2f, 10)));
		}

		// SpaceGameEntityConstructor::ConstructEnemyAsteroids(componentCollectionRepository, asteroidGraphicsResIds, this->width, this->height, initNumAsteroids);
	
		auto projectileCollisionTask = new CollisionPhysicsTask("EnemyAsteroids", "PlayerSpaceShipProjectiles"); 
		auto projectileCollisionTaskHandler = [=](const CollisionEventArgs& collisionEventArgs) {this->OnProjectileCollision(collisionEventArgs); };

		auto exitBoundsTask = new ExitBoundsTask("EnemyAsteroids", Vector2D(0.0f, 0.0f), Vector2D(width, height)); 
		auto exitBoundsHandler = [=](const ExitBoundsEventArgs& exitBoundsEventArgs) {this->OnAsteroidExitBounds(exitBoundsEventArgs); };

		projectileCollisionTask->RegisterListener<CollisionEventArgs>(projectileCollisionTaskHandler);
		exitBoundsTask->RegisterListener<ExitBoundsEventArgs>(exitBoundsHandler); 

		this->GetParentStage()->GetPhysics()->AddPhysicsTask(projectileCollisionTask);
		this->GetParentStage()->GetPhysics()->AddPhysicsTask(exitBoundsTask); 
		this->GetParentStage()->GetPhysics()->AddPhysicsTask(new VelocityTask("EnemyAsteroids")); 
	}
	//-------------------------------------------------------------------------------
	// Name: Update
	// Desc: 
	//-------------------------------------------------------------------------------
	void Update() override final
	{
		// NOTE: a more 'elegant way of doing this would be a 'spawnAsteroidOnTimerElapse' or something'
		if (1 == MathUtility::RandomIntUniformDist() % 100) {
			auto componentCollectionRepository = this->GetParentStage()->GetComponentCollectionRepository();
			auto graphics = this->GetParentStage()->GetGameApp()->GetGraphics();
			SpaceGameEntityConstructor::ConstructEnemyAsteroids(componentCollectionRepository, asteroidGraphicsResIds, this->width, this->height, 1); 
		}
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

		for (auto& physicsComponent : *asteroidPhysicsComponents) {

			auto playerTransformComponent = componentCollectionRepository->Select<TransformComponent>(playerPhysicsComponent.transformComponentId);
			auto transformComponent = componentCollectionRepository->Select<TransformComponent>(physicsComponent.transformComponentId); 

			auto distVector = playerTransformComponent->position - transformComponent->position;

			// calculate acceleration on asteroids
			auto accel = 2500.0f * physicsComponent.mass / powf(distVector.Length(), 2.0f);
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
	void OnProjectileCollision(const CollisionEventArgs& collisionEventArgs) const
	{
		auto componentCollectionRepository = this->GetParentStage()->GetComponentCollectionRepository(); 

		componentCollectionRepository->RemoveEntity(collisionEventArgs.entityId1);
		componentCollectionRepository->RemoveEntity(collisionEventArgs.entityId2);
	}
	//-------------------------------------------------------------------------------
	// Name: OnAsteroidExitBounds
	// Desc: 
	//-------------------------------------------------------------------------------
	void OnAsteroidExitBounds(const ExitBoundsEventArgs& exitBoundsEventArgs) const
	{
		auto componentCollectionRepository = this->GetParentStage()->GetComponentCollectionRepository();
		auto height = this->GetParentStage()->GetGameApp()->GetGraphics()->WindowHeight();
		auto width = this->GetParentStage()->GetGameApp()->GetGraphics()->WindowWidth(); 
		
		// if we left the bottom of the screen
		if (exitBoundsEventArgs.exitPoint.y > height) {
			componentCollectionRepository->RemoveEntity(exitBoundsEventArgs.entityId);

		} else if (exitBoundsEventArgs.exitPoint.y > 0.0f) {

			auto transformComponent = componentCollectionRepository->Select<TransformComponent>(exitBoundsEventArgs.transformComponentId); 
			auto physicsComponent = componentCollectionRepository->Select<PhysicsComponent>(exitBoundsEventArgs.physicsComponentId); 

			physicsComponent->velocity.x = 0.0f; 
			physicsComponent->velocity.y = 2.5f; 

			transformComponent->position.x = (width / 2) + (MathUtility::RandomIntUniformDist() % (width / 2)); 
			transformComponent->position.y = -10.0f; 
		}
	}
};

#endif // ASTEROID_ACTION_H