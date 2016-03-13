//
// Created by Julian  on 24/02/2016
//

#ifndef SPACE_GAME_ENTITY_CONSTRUCTOR_H
#define SPACE_GAME_ENTITY_CONSTRUCTOR_H

#include "Entity.h"
#include "ComponentCollectionRepository.h"
#include "Vector.h"
#include "Components/TransformComponent.h"
#include "Components/GraphicsComponent.h"
#include "Components/SimplePhysicsComponent.h"
#include "Components/PhysicsComponent.h"
#include "GraphicsResources/CircleFIllGraphicsResource.h"

#include <Utility\MathUtility.h>

#include <random>

class SpaceGameEntityConstructor
{
public:

	//---------------------------------------------------------------------------
	// Name: ConstructPlayerSpaceShip
	// Desc:
	//---------------------------------------------------------------------------
	static void ConstructPlayerSpaceShip(ComponentCollectionRepository* componentCollectionRepository, int graphicResourceId, Vector2D position)
	{
		const string playerSpaceShipCollectionName = "PlayerSpaceShip"; 
		componentCollectionRepository->NewCollection(playerSpaceShipCollectionName); 

		auto transformComponent = componentCollectionRepository->NewComponent<TransformComponent>(playerSpaceShipCollectionName);
		auto graphicsComponent = componentCollectionRepository->NewComponent<GraphicsComponent>(playerSpaceShipCollectionName);
		auto physicsComponent = componentCollectionRepository->NewComponent<PhysicsComponent>(playerSpaceShipCollectionName);

		transformComponent->position = position; 
		transformComponent->scale = Vector2D(0.5f, 0.5f); 

		physicsComponent->transformComponent = transformComponent; 
		physicsComponent->velocity = Vector2D(0.0f, 0.0f);

		graphicsComponent->transformComponent = transformComponent; 
		graphicsComponent->resourceId = graphicResourceId; 
	}
	//--------------------------------------------------------------------------------
	// Name: ConstructBackgroundStars
	// Desc:
	//--------------------------------------------------------------------------------
	static void ConstructBackgroundStars(ComponentCollectionRepository* componentCollectionRepository, int graphicResourceId, int width, int height, int num)
	{
		default_random_engine defaultRandomEngine; 
		uniform_int_distribution<int> yUniformIntDistribution(0, height); 
		uniform_real_distribution<float> scaleUniformDist(1.0f, 2.0f); 

		const string collectionName = "ScrollingBackgroundStars";
		const float starScrollVelocity = 1.0f; 

		componentCollectionRepository->NewCollection(collectionName); 

		for (auto i = 0; i < num; i++) {

			auto transformComponent = componentCollectionRepository->NewComponent<TransformComponent>(collectionName);
			auto graphicsComponent = componentCollectionRepository->NewComponent<GraphicsComponent>(collectionName); 
			auto physicsComponent = componentCollectionRepository->NewComponent<SimplePhysicsComponent>(collectionName); 

			float scale = scaleUniformDist(defaultRandomEngine); 
			transformComponent->scale = Vector2D(scale, scale); 
			transformComponent->position.x = (i+1)*(width / num); 
			transformComponent->position.y = 2.0f*yUniformIntDistribution(defaultRandomEngine); 

			graphicsComponent->resourceId = graphicResourceId; 
			graphicsComponent->transformComponent = transformComponent;
			
			physicsComponent->velocity.y = 0.5f*starScrollVelocity*scale;
			physicsComponent->transformComponent = transformComponent;  
		}
	}
	//---------------------------------------------------------------------------
	// Name: ConstructEnemyAsteroids
	// Desc:
	//---------------------------------------------------------------------------
	static void ConstructEnemyAsteroids(ComponentCollectionRepository* componentCollectionRepository, vector<int>& graphicResourceIds, int width, int height, int num)
	{
		const string collectionName = "EnemyAsteroids"; 

		componentCollectionRepository->NewCollection(collectionName); 

		for (auto i = 0; i < num; i++) {

			auto transformComponent = componentCollectionRepository->NewComponent<TransformComponent>(collectionName);
			auto graphicsComponent = componentCollectionRepository->NewComponent<GraphicsComponent>(collectionName);
			auto physicsComponent = componentCollectionRepository->NewComponent<PhysicsComponent>(collectionName);

			//physicsComponent->velocity.y = 2.0f*(MathUtility::RandomFloatUniformDist() - 0.5f);
			//physicsComponent->velocity.x = 2.0f*(MathUtility::RandomFloatUniformDist() - 0.5f); 
			
			//physicsComponent->angularVelocity = 0.25f*MathUtility::RandomFloatUniformDist(); 
			physicsComponent->mass = MathUtility::RandomFloatUniformDist(); 
			physicsComponent->transformComponent = transformComponent;

			transformComponent->position.x = height*MathUtility::RandomFloatUniformDist(); 
			transformComponent->position.y = width*MathUtility::RandomFloatUniformDist(); 
			transformComponent->scale = Vector2D(1.0f, 1.0f);

			graphicsComponent->resourceId = graphicResourceIds[i];
			graphicsComponent->transformComponent = transformComponent;
		}
	}
};


#endif