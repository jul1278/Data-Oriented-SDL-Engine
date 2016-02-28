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
#include "GraphicsResources/CircleFIllGraphicsResource.h"

#include <random>

//const float defaultProjectileSpeed = 4.0f;

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
		auto physicsComponent = componentCollectionRepository->NewComponent<SimplePhysicsComponent>(playerSpaceShipCollectionName);

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

};


#endif