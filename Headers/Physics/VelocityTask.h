#ifndef VELOCITY_TASK_H
#define VELOCITY_TASK_H

#include "Physics/IPhysicsTask.h"
#include "Components/PhysicsComponent.h"

class VelocityTask : public IPhysicsTask
{
	void Task(ComponentCollectionRepository* componentCollectionRepository, 
		const string& collection1, const string& collection2, EventObservable* eventObservable) override final
	{
		auto physicsComponents = componentCollectionRepository->SelectFromCollection<PhysicsComponent>(collection1); 
		
		if (physicsComponents->size() == 0) {
			return; 
		}

		for (auto& component : *physicsComponents) {
			
			auto transformComponent = componentCollectionRepository->Select<TransformComponent>(component.transformComponentId); 

			// TODO: this should have a timestep and stuff
			component.velocity += component.acceleration; 
			transformComponent->position += component.velocity;

			component.angularVelocity += component.angularAcceleration; 
			transformComponent->orientation += component.angularVelocity;
		}
	}

public:

	explicit VelocityTask(const string& collection) : IPhysicsTask(collection, "") {}
};

#endif // VELOCITY_TASK_H