//
// Created by Julian  on 22/12/15.
//

#ifndef SDLRTS_TEST_COMPONENT_RELATION_H
#define SDLRTS_TEST_COMPONENT_RELATION_H

#include "../Headers/Components/ComponentRepository.h"
#include "../Headers/Components/ComponentRelation.h"
#include "../Headers/Components/BaseComponent.h"
#include "../Headers/Components/CollisionComponent.h"
#include "../Headers/Components/TransformComponent.h"

#include <ctime>
#include <random>
#include <iostream>

using namespace std; 

class TestComponentRelation
{
public:

	TestComponentRelation()
	{
		ComponentRepository componentRepository;

		long numComponents = 15000; 

		vector<int> seedVector = { (int) time(0), (int) time(0) }; 

		std::seed_seq seed(seedVector.begin(), seedVector.end());
		std::default_random_engine generator;
		generator.seed(seed); 
		std::uniform_real_distribution<float> distribution(1.0f, 1000.0f);
		std::uniform_real_distribution<float> radiusDistribution(1.0f, 5.0f);
		
		vector<ComponentPairRelation> componentRelations; 
		 
		for (int i = 0; i < numComponents; i++) {

			float x = distribution(generator);
			float y = distribution(generator);
			float r = radiusDistribution(generator); 

			int lastTransformId = componentRepository.InsertComponent(TRANSFORM_COMPONENT, new TransformComponent(Vector2D(x, y)));
			int lastCollisionId = componentRepository.InsertComponent(COLLISION_COMPONENT, new CollisionComponent(lastTransformId, r));

			auto collisionComponent = componentRepository.Select<CollisionComponent*>(lastCollisionId);
			auto transformComponent = componentRepository.Select<TransformComponent*>(lastTransformId);

			componentRelations.push_back(ComponentPairRelation(collisionComponent, transformComponent)); 
		}

		std::time_t currTime = std::time(nullptr);
		vector<IBaseComponent*>* transformComponents = componentRepository.Select(TRANSFORM_COMPONENT);

		long counter = 0; 

		for (auto componentRelation : componentRelations) {

			float x = componentRelation.Child<TransformComponent*>()->position.x; 
			float y = componentRelation.Child<TransformComponent*>()->position.y; 

			float r = componentRelation.Parent<CollisionComponent*>()->radius; 

			for (auto currComponentRelation : componentRelations) {

				if (componentRelation.Parent<CollisionComponent*>()->id != currComponentRelation.Parent<CollisionComponent*>()->id) {
					float currX = currComponentRelation.Child<TransformComponent*>()->position.x; 
					float currY = currComponentRelation.Child<TransformComponent*>()->position.y; 
					float currR = currComponentRelation.Parent<CollisionComponent*>()->radius; 

					float diffX = currX - x; 
					float diffY = currY - y; 

					if ((diffX*diffX + diffY*diffY) < ((currR + r)*(currR + r))) {

						// collision happen
						//cout << componentRelation.Parent<CollisionComponent*>()->id << std::endl;
						counter++; 
					}
				}
			}
		}

		std::time_t diffTime = std::time(nullptr) - currTime;

		long diffTimeSec = static_cast<long>(diffTime); 

		cout << "vector test: " << diffTimeSec << " sec" << std::endl;

		if (diffTimeSec != 0) {
			cout << "vectors/sec : " << (static_cast<float>(numComponents / diffTimeSec)) << std::endl;
		}
		
		cout << counter << " Collision(s)" << std::endl;
		currTime = std::time(nullptr);

		system("pause");

		return;
	}
};

#endif