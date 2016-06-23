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

		auto graphics = this->GetParentStage()->GetGameApp()->GetGraphics(); 
		auto componentCollectionRepository = this->GetParentStage()->GetComponentCollectionRepository(); 

		vector<int> asteroidGraphicsResIds;

		for (auto i = 0; i < 5; i++) {
			asteroidGraphicsResIds.push_back(graphics->AddGraphicsResource(new ProceduralAsteroidGraphicsResource(20.0f, 1.2f, 10)));
		}

		SpaceGameEntityConstructor::ConstructEnemyAsteroids(componentCollectionRepository, asteroidGraphicsResIds, this->width, this->height, 4);
	
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

		for (auto physicsComponent : *asteroidPhysicsComponents) {

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