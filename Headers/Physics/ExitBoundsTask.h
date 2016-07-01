#ifndef EXIT_BOUNDS_TASK_H
#define EXIT_BOUNDS_TASK_H

#include "Physics/IPhysicsTask.h"
#include "Components/TransformComponent.h"
#include "Events/ExitBoundsEventArgs.h"

class ExitBoundsTask : public IPhysicsTask
{
	Vector2D min;
	Vector2D max; 

	void Task(ComponentCollectionRepository* componentCollectionRepository, const string& collection1, const string& collection2, EventObservable* eventObservable) override
	{
		auto transformComponents = componentCollectionRepository->SelectFromCollection<TransformComponent>(collection1); 
		auto physicsComponents = componentCollectionRepository->SelectFromCollection<PhysicsComponent>(collection1); 

		for (auto component : *transformComponents) {
			if (component.position.x < this->min.x || 
				component.position.y < this->min.y || 
				component.position.x > this->max.x || 
				component.position.y > this->max.y) {

				auto id = component.id; 
				auto physicsComponent = find_if(physicsComponents->begin(), physicsComponents->end(), [id](const PhysicsComponent& p) {return p.transformComponentId == id; });
				
				eventObservable->Invoke<ExitBoundsEventArgs>(ExitBoundsEventArgs(component.id, physicsComponent->id, collection1, component.position)); 
			}
		}
	}

public:

	ExitBoundsTask(const string& collection1, const Vector2D& min, const Vector2D& max)
		: IPhysicsTask(collection1, "")
	{
		this->min = min;
		this->max = max; 
	}
};

#endif // EXIT_BOUNDS_TASK_H