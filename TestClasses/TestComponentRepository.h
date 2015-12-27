//
// Created by Julian  on 20/12/15.
//

#ifndef SDL_RTS_TEST_COMPONENT_REPOSITORY_H
#define SDL_RTS_TEST_COMPONENT_REPOSITORY_H

#include "Components/ComponentRepository.h"
#include "Components/BaseComponent.h"
#include "Components/GraphicsComponent.h"
#include "Components/ClickableComponent.h"
#include "Components/TransformComponent.h"
#include "Components/CollisionComponent.h"

#include <ctime>
#include <random>

using namespace std; 

class TestComponentRepository
{
private:

public:

	TestComponentRepository()
	{
		ComponentRepository componentRepository; 

		std::default_random_engine generator; 
		std::uniform_real_distribution<float> distribution(1.0f, 100.0f); 

		for (int i = 0; i < 5000; i++) {

			float x = distribution(generator); 
			float y = distribution(generator); 

			int lastTransformId = componentRepository.InsertComponent(TRANSFORM_COMPONENT, new TransformComponent(Vector2D(x, y)));
			int lastCollisionId = componentRepository.InsertComponent(COLLISION_COMPONENT, new CollisionComponent(lastTransformId, 1.0f));

			auto collisionComponent = componentRepository.Select<CollisionComponent*>(lastCollisionId); 
			auto transformComponent = componentRepository.Select<TransformComponent*>(lastTransformId); 
		}

		std::time_t currTime = std::time(nullptr); 
		vector<IBaseComponent*>* transformComponents = componentRepository.Select(TRANSFORM_COMPONENT); 

		for (auto* component : *transformComponents) {

			TransformComponent* transformComponent = static_cast<TransformComponent*>(component); 
			for (auto* currComponent : *transformComponents) {

				TransformComponent* currTransformComponent = static_cast<TransformComponent*>(currComponent);

				transformComponent->position.x += currTransformComponent->position.x; 
				transformComponent->position.y += currTransformComponent->position.x; 
			}
		}

		std::time_t diffTime = std::time(nullptr) - currTime; 

		cout << "vector test: "<< diffTime << " sec" << std::endl; 
		currTime = std::time(nullptr); 

		return; 
	}
};

#endif