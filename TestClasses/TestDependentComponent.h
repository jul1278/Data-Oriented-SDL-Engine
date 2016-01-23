//
// Created by Julian  on 20/12/15.
//

#ifndef TEST_DEPENDENT_COMPONENT_H
#define TEST_DEPENDENT_COMPONENT_H

#include "Components/ComponentRepository.h"
#include "Components/BaseComponent.h"
#include "Components/GraphicsComponent.h"
#include "Components/ClickableComponent.h"
#include "Components/TransformComponent.h"
#include "Components/CollisionComponent.h"

#include <chrono>
#include <random>
#include <iostream>

using namespace std;

class TestDependentComponent
{
public:

	TestDependentComponent()
	{
		cout << "TestDependentComponent" << endl;

		ComponentRepository componentRepository;

		int numComponents = 1000;

		cout << numComponents << " components." << endl;

		vector<int> seedVector = { static_cast<int>(time(nullptr)), static_cast<int>(time(nullptr)) };

		std::seed_seq seed(seedVector.begin(), seedVector.end());
		std::default_random_engine generator;
		generator.seed(seed);

		std::uniform_real_distribution<float> distribution(0.0f, 100.0f);
		std::uniform_real_distribution<float> radiusDistribution(1.0f, 5.0f);

		for (int i = 0; i < numComponents; i++) {

			float x = distribution(generator);
			float y = distribution(generator);
			float r = radiusDistribution(generator); 

			int lastTransformId = componentRepository.InsertComponent(TRANSFORM_COMPONENT, new TransformComponent(Vector2D(x, y)));
			auto transformComponent = componentRepository.Select<TransformComponent*>(lastTransformId);
			
			int lastCollisionId = componentRepository.InsertComponent(COLLISION_COMPONENT, new CollisionComponent(r, transformComponent));
			auto collisionComponent = componentRepository.Select<CollisionComponent*>(lastCollisionId);
			
		}

		long counter = 0; 

		auto start = chrono::steady_clock::now(); 

		vector<BaseComponent*>* collisionComponents = componentRepository.Select(COLLISION_COMPONENT); 

		for (auto component : *collisionComponents) {

			CollisionComponent* collisionComponent = component->As<CollisionComponent*>(); 
			TransformComponent* transformComponent = collisionComponent->transformComponent; 

			float x = transformComponent->position.x; 
			float y = transformComponent->position.y; 
			float r = collisionComponent->radius; 

			for (auto currComponent : *collisionComponents) {

				CollisionComponent* currCollisionComponent = currComponent->As<CollisionComponent*>();
				TransformComponent* currTransformComponent = currCollisionComponent->transformComponent; 

				if (collisionComponent->id != currComponent->id) {
					float currX = currTransformComponent->position.x;
					float currY = currTransformComponent->position.y;
					float currR = currCollisionComponent->radius;

					float diffX = currX - x;
					float diffY = currY - y;

					if ((diffX*diffX + diffY*diffY) < ((currR + r)*(currR + r))) {
						counter++;
					}
				}
			}
		}

		auto end = chrono::steady_clock::now();

		cout << "vector test: " << chrono::duration<double, std::milli>(end - start).count() << " ms" << std::endl;
		cout << counter << " Collision(s)" << std::endl;

		return;
	}
};

#endif