#include "Physics/Physics.h"
#include "Physics/IPhysicsTask.h"
#include <Utility/MathUtility.h>
#include <Components/VelocityComponent.h>

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
void Physics::ExecuteTasks(ComponentCollectionRepository* componentCollectionRepository)
{
	for (auto task : tasks) {
		task->Execute(componentCollectionRepository);
	}
}
//-------------------------------------------------------------------------------
// Name: SolveAsteroidPhysics
// Desc: temp function to do logic/physics for the enemy asteroids 
//-------------------------------------------------------------------------------
void Physics::SolveAsteroidPhysics(ComponentCollectionRepository* componentCollectionRepository) const
{
#pragma message ("WARNING: "__FUNCTION__" is deprecated.")

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
void Physics::SolvePhysics(ComponentCollectionRepository* componentCollectionRepository, const string& collectionName)
{
#pragma message ("WARNING: "__FUNCTION__" is deprecated.")

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
void Physics::SolveSimplePhysics(ComponentCollectionRepository* componentCollectionRepository, const string& collectionName)
{
#pragma message ("WARNING: "__FUNCTION__" is deprecated.")

	auto physicsComponents = componentCollectionRepository->SelectFromCollection<VelocityComponent>(collectionName);

	if (physicsComponents == nullptr) {
		return;
	}

	for (auto component : *physicsComponents) {
		component.transformComponent->position.x += component.velocity.x;
		component.transformComponent->position.y += component.velocity.y;
	}
}
