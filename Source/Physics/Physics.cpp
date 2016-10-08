#include "Physics/Physics.h"
#include "Physics/IPhysicsTask.h"
#include <Utility/MathUtility.h>
#include <Components/VelocityComponent.h>
#include <Components/TransformComponent.h>
#include <Components/PhysicsComponent.h>

//-------------------------------------------------------------------------------
// Name: AddPhysicsTask
// Desc:
//-------------------------------------------------------------------------------
void Physics::AddPhysicsTask(IPhysicsTask* physicsTask)
{
	if (physicsTask) {
		this->tasks.push_back(physicsTask);
	}
}
//-------------------------------------------------------------------------------
// Name: AddPhysicsTask
// Desc:
//-------------------------------------------------------------------------------
Physics::~Physics()
{
	remove_if(this->tasks.begin(), this->tasks.end(), [] (IPhysicsTask* task) {delete task; return true; });
}
//-------------------------------------------------------------------------------
// Name: Exectute
// Desc:
//-------------------------------------------------------------------------------
void Physics::ExecuteTasks(ComponentRepository* componentRepository)
{
	for (auto task : tasks) {
		task->Execute(componentRepository);
	}
}
//-------------------------------------------------------------------------------
// Name: SolveAsteroidPhysics
// Desc: temp function to do logic/physics for the enemy asteroids 
//-------------------------------------------------------------------------------
void Physics::SolveAsteroidPhysics(ComponentRepository* componentRepository) const
{
#ifdef _WIN32
	#pragma message ("WARNING: "__FILE__ "  -  " __FUNCTION__" is deprecated.")
#endif
#ifdef __APPLE__
	#warning "Function is deprecated"	
#endif
	
	auto asteroidPhysicsComponents = componentRepository->Select<PhysicsComponent>("EnemyAsteroids");
	auto playerPhysicsComponents = componentRepository->Select<PhysicsComponent>("PlayerSpaceShip");

	if (asteroidPhysicsComponents.Size() == 0) {
		return;
	}

	if (playerPhysicsComponents.Size() == 0) {
		return;
	}

	auto playerPhysicsComponent = playerPhysicsComponents.front();
	auto playerTransformComponent = componentRepository->SelectId<TransformComponent>(playerPhysicsComponent.transformComponentId); 

	for (auto physicsComponent : asteroidPhysicsComponents) {

		if (playerTransformComponent->position.x > this->width || playerTransformComponent->position.x <= 0 ||
			playerTransformComponent->position.y > this->height || playerTransformComponent->position.y <= 0) {

			playerTransformComponent->position.x = MathUtility::RandomFloatUniformDist()*this->width;
			playerTransformComponent->position.y = MathUtility::RandomFloatUniformDist()*this->height;

			continue;
		}

		auto transformComponent = componentRepository->SelectId<TransformComponent>(physicsComponent.transformComponentId); 

		// 
		auto distVector = playerTransformComponent->position - transformComponent->position;

		// calculate acceleration on asteroids
		auto accel = 10000.0f * physicsComponent.mass / (distVector.Length()*distVector.Length());
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
// Name: SolvePhysics
// Desc: 
//-------------------------------------------------------------------------------
void Physics::SolvePhysics(ComponentRepository* componentRepository, const string& collectionName)
{
#ifdef _WIN32
	#pragma message ("WARNING: "__FILE__ "  -  " __FUNCTION__" is deprecated.")
#endif
#ifdef __APPLE__
	#warning "Function is deprecated"	
#endif
	auto physicsComponents = componentRepository->Select<PhysicsComponent>(collectionName);

	for (auto component : physicsComponents) {
		if (auto transformComponent = componentRepository->SelectId<TransformComponent>(component.transformComponentId)) {

			transformComponent->orientation = Vector2D(component.angularVelocity) + transformComponent->orientation;
			transformComponent->position.x += component.velocity.x;
			transformComponent->position.y += component.velocity.y;
		}
	}
}
//-------------------------------------------------------------------------------
// Name: SolveSimplePhysics
// Desc: 
//-------------------------------------------------------------------------------
void Physics::SolveSimplePhysics(ComponentRepository* componentRepository, const string& collectionName)
{
#ifdef _WIN32
	#pragma message ("WARNING: "__FILE__ "  -  " __FUNCTION__" is deprecated.")
#endif
#ifdef __APPLE__
	#warning "Function is deprecated"	
#endif
	auto physicsComponents = componentRepository->Select<VelocityComponent>(collectionName);

	for (auto component : physicsComponents) {

		auto transformComponent = componentRepository->SelectId<TransformComponent>(component.transformComponentId);

		transformComponent->position.x += component.velocity.x;
		transformComponent->position.y += component.velocity.y;
	}
}
