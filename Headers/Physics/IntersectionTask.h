#ifndef INTERSECTION_TASK_H
#define INTERSECTION_TASK_H

#include "Physics/IPhysicsTask.h"
#include "Components/TransformComponent.h"
#include "Events/IntersectionEventArgs.h"

class IntersectionTask : public IPhysicsTask
{
	void Task(ComponentRepository* componentRepository, const string& collection1, const string& collection2, EventObservable* eventObservable) override
	{
		auto components1 = componentRepository->Select<TransformComponent>(collection1);
		auto components2 = componentRepository->Select<TransformComponent>(collection2);

		if (components1.Size() == 0 || components2.Size() == 0) {
			return; 
		}

		for (auto component1 : components1) {
			for (auto component2 : components2) {

				if (&component1 == &component2) {
					continue; 
				}

				if (component1.position == component2.position) {
					eventObservable->Invoke<IntersectionEventArgs>(IntersectionEventArgs(&component1, &component2)); 
				}
			}
		}
	}

public:

	IntersectionTask(const string& collection1, const string& collection2)
		: IPhysicsTask(collection1, collection2)
	{
	}
};

#endif // INTERSECTION_TASK_H