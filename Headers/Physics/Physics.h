#ifndef PHYSICS_H
#define PHYSICS_H

#include "Events\CollisionEventArgs.h"
#include "Components\VelocityComponent.h"
#include "Components\PhysicsComponent.h"
#include "Components\TransformComponent.h"
#include "Components\ComponentCollectionRepository.h"
#include "Utility\MathUtility.h"
#include "Events\TaskEvent.h"

struct PhysicsTask
{
	PhysicsTask(string collection1, string collection2)
		: collection1(collection1), collection2(collection2) {}

	string collection1; 
	string collection2; 
	TaskEvent<CollisionEventArgs> taskEvent; 
};

class Physics
{
private:

	list<PhysicsTask> tasks; 

	int width; 
	int height;

	static void ExecuteTask(PhysicsTask task, ComponentCollectionRepository* componentCollectionRepository)
	{
		auto physCollection1 = componentCollectionRepository->SelectFromCollection<PhysicsComponent>(task.collection1); 
		auto physCollection2 = componentCollectionRepository->SelectFromCollection<PhysicsComponent>(task.collection2); 

		if (physCollection1 == nullptr || physCollection2 == nullptr) {
			return; 
		}

		if (physCollection1->empty() || physCollection2->empty()) {
			return; 
		}

		for (auto physComponent1 : *physCollection1) {
			
			auto pos1 = physComponent1.transformComponent->position; 
			
			for (auto physComponent2 : *physCollection2) {
				
				auto diff = pos1 - physComponent2.transformComponent->position;
				auto rad = physComponent1.radius + physComponent2.radius; 

				if (diff.Length() < rad) {
					task.taskEvent.Invoke(CollisionEventArgs(&physComponent1, &physComponent2)); 
				}
			}
		}
	}

public:

	Physics(int width, int height) 
	{
		this->width = width; 
		this->height = height;
	}
	//-------------------------------------------------------------------------------
	// Name: AddSolveCollsionTask
	// Desc:
	//-------------------------------------------------------------------------------
	TaskEvent<CollisionEventArgs>* AddSolveCollisionTask(string collection1, string collection2)
	{
		// TODO: check if we already have this task

		this->tasks.push_back(PhysicsTask(collection1, collection2));
		return &(this->tasks.front().taskEvent); 
	}
	//-------------------------------------------------------------------------------
	// Name: Exectute
	// Desc:
	//-------------------------------------------------------------------------------
	void ExecuteTasks(ComponentCollectionRepository* componentCollectionRepository)
	{
		for (auto task : tasks) {
			this->ExecuteTask(task, componentCollectionRepository); 
		}
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

			auto currentAngle = physicsComponent.transformComponent->orientation.Angle(); 
			physicsComponent.transformComponent->orientation = Vector2D(currentAngle + physicsComponent.angularVelocity); 
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
		auto physicsComponents = componentCollectionRepository->SelectFromCollection<VelocityComponent>(collectionName);

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