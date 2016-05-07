#ifndef SNAKE_EAT_SELF_TASK_H
#define SNAKE_EAT_SELF_TASK_H

#include "Physics\IPhysicsTask.h"
#include "Components\TransformComponent.h"
#include "Events\IntersectionEventArgs.h"

class SnakeEatSelfTask : public IPhysicsTask
{
	void Task(ComponentCollectionRepository* componentCollectionRepository, const string& collection1, const string& collection2, EventObservable* eventObservable) override
	{
		auto snakeComponents = componentCollectionRepository->SelectFromCollection<TransformComponent>(collection1);
		auto snakeHead = snakeComponents->front(); 

		for (auto component : *snakeComponents) {

			if (component.id == snakeHead.id) {
				continue; 
			}

			if (snakeHead.position == component.position) {
				eventObservable->Invoke<IntersectionEventArgs>(IntersectionEventArgs(&snakeHead, &component)); 
				return; 
			}
		}
	}

public:
	SnakeEatSelfTask() : IPhysicsTask("Snake", "Snake")
	{
	}
};

#endif // SNAKE_EAT_SELF_TASK_H