#ifndef COLLISION_PHYSICS_TASK_H
#define COLLISION_PHYSICS_TASK_H

#include "Physics/IPhysicsTask.h"
#include "Events/CollisionEventArgs.h"

class CollisionPhysicsTask : public IPhysicsTask
{
private:

	void Task(ComponentRepository* componentRepository, const string& collection1, const string& collection2, EventObservable* eventObservable) override
	{
		auto physCollection1 = componentRepository->Select<PhysicsComponent>(collection1);
		auto physCollection2 = componentRepository->Select<PhysicsComponent>(collection2);

		if (physCollection1.empty() || physCollection2.empty()) {
			return;
		}

		if (physCollection1.Size() == 0 && physCollection2.Size() == 0) {
			return; 
		}

		for (auto physComponent1 : physCollection1) {
			auto transformComponent1 = componentRepository->SelectId<TransformComponent>(physComponent1.transformComponentId); 
			
			if (transformComponent1 == nullptr) {
				continue; 
			}
			
			auto pos1 = transformComponent1->position;

			for (auto physComponent2 : physCollection2) {
				auto transformComponent2 = componentRepository->SelectId<TransformComponent>(physComponent2.transformComponentId); 

				if (transformComponent2 == nullptr) {
					continue; 
				}

				if (transformComponent1->id == transformComponent2->id) {
					continue; 
				}

				auto diff = pos1 - transformComponent2->position;
				auto rad = physComponent1.radius + physComponent2.radius;

				if (diff.Length() < rad) {
					eventObservable->Invoke(CollisionEventArgs(collection1, collection2, physComponent1.id, physComponent2.id, 
						physComponent1.entityId, physComponent2.entityId));
				}
			}
		}
	}

public:

	CollisionPhysicsTask(const string& collection1, const string& collection2) : IPhysicsTask(collection1, collection2) {}	
	~CollisionPhysicsTask() override { }
};

#endif // COLLISION_PHYSICS_TASK_H