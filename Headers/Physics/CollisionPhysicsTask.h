#ifndef COLLISION_PHYSICS_TASK_H
#define COLLISION_PHYSICS_TASK_H

#include "Physics/IPhysicsTask.h"
#include <Events/CollisionEventArgs.h>

class CollisionPhysicsTask : public IPhysicsTask
{
private:

	void Task(ComponentCollectionRepository* componentCollectionRepository, const string& collection1, const string& collection2, EventObservable* eventObservable) override
	{
		auto physCollection1 = componentCollectionRepository->SelectFromCollection<PhysicsComponent>(collection1);
		auto physCollection2 = componentCollectionRepository->SelectFromCollection<PhysicsComponent>(collection2);

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
					eventObservable->Invoke(CollisionEventArgs(&physComponent1, &physComponent2));
				}
			}
		}
	}

public:

	CollisionPhysicsTask(const string& collection1, const string& collection2) : IPhysicsTask(collection1, collection2) {}	
	~CollisionPhysicsTask() override { }
};

#endif // COLLISION_PHYSICS_TASK_H