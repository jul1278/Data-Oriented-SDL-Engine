//
// Created by Julian  on 24/02/2016
//

#ifndef SPACE_GAME_ENTITY_CONSTRUCTOR_H
#define SPACE_GAME_ENTITY_CONSTRUCTOR_H

#include "Components/Repository/ComponentRepository.h"
#include "Utility/Vector.h"
#include "Components/TransformComponent.h"
#include "Components/GraphicsComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/PhysicsComponent.h"
#include "Utility/MathUtility.h"

#include <random>

class SpaceGameEntityConstructor
{
public:

	//---------------------------------------------------------------------------
	// Name: ConstructPlayerSpaceShip
	// Desc:
	//---------------------------------------------------------------------------
	static void ConstructPlayerSpaceShip(ComponentRepository* componentRepository, int graphicResourceId, Vector2D position)
	{
		const auto playerSpaceShipCollectionName = "PlayerSpaceShip"; 
		componentRepository->NewCollection(playerSpaceShipCollectionName); 

		auto transformComponent = componentRepository->NewComponent<TransformComponent>(playerSpaceShipCollectionName);
		auto graphicsComponent = componentRepository->NewComponent<GraphicsComponent>(playerSpaceShipCollectionName);
		auto physicsComponent = componentRepository->NewComponent<PhysicsComponent>(playerSpaceShipCollectionName);

		transformComponent->position = position; 
		transformComponent->scale = Vector2D(0.5f, 0.5f); 

		physicsComponent->transformComponentId = transformComponent->id; 
		physicsComponent->velocity = Vector2D(0.0f, 0.0f);

		graphicsComponent->transformComponentId = transformComponent->id; 
		graphicsComponent->resourceId = graphicResourceId; 
	}
	//--------------------------------------------------------------------------------
	// Name: ConstructBackgroundStars
	// Desc:
	//--------------------------------------------------------------------------------
	static void ConstructBackgroundStars(ComponentRepository* componentRepository, int graphicResourceId, int width, int height, int num)
	{
		default_random_engine defaultRandomEngine; 
		uniform_int_distribution<int> yUniformIntDistribution(0, height); 
		uniform_real_distribution<float> scaleUniformDist(1.0f, 2.0f); 

		const auto collectionName = "ScrollingBackgroundStars";
		const auto starScrollVelocity = 0.5f; 

		componentRepository->NewCollection(collectionName); 

		for (auto i = 0; i < num; i++) {

			auto transformComponent = componentRepository->NewComponent<TransformComponent>(collectionName);
			auto graphicsComponent = componentRepository->NewComponent<GraphicsComponent>(collectionName); 
			auto physicsComponent = componentRepository->NewComponent<VelocityComponent>(collectionName); 

			auto scale = scaleUniformDist(defaultRandomEngine); 

			transformComponent->scale = Vector2D(scale, scale); 
			transformComponent->position.x = (i+1)*(width / num); 
			transformComponent->position.y = 2.0f*yUniformIntDistribution(defaultRandomEngine); 

			graphicsComponent->resourceId = graphicResourceId; 
			graphicsComponent->transformComponentId = transformComponent->id;
			
			physicsComponent->velocity.y = 0.5f*starScrollVelocity*scale;
			physicsComponent->transformComponentId = transformComponent->id;  
		}
	}
	//---------------------------------------------------------------------------
	// Name: ConstructEnemyAsteroids
	// Desc:
	//---------------------------------------------------------------------------
	static void ConstructEnemyAsteroids(ComponentRepository* componentRepository, vector<int>& graphicResourceIds, int width, int height, int num)
	{
		const auto collectionName = "EnemyAsteroids"; 

		componentRepository->NewCollection(collectionName); 

		for (auto i = 0; i < num; i++) {
			auto entityId = componentRepository->GenerateId();

			auto transformComponent = componentRepository->NewComponent<TransformComponent>(collectionName, entityId);
			auto graphicsComponent = componentRepository->NewComponent<GraphicsComponent>(collectionName, entityId);
			auto physicsComponent = componentRepository->NewComponent<PhysicsComponent>(collectionName, entityId);

			physicsComponent->mass = MathUtility::RandomFloatUniformDist(); 
			physicsComponent->transformComponentId = transformComponent->id;
			physicsComponent->angularVelocity = 0.01f;
			physicsComponent->radius = 30.0f; 

			physicsComponent->acceleration = Vector2D(0.001f*(0.5f - MathUtility::RandomFloatUniformDist()), 0.0f);
			physicsComponent->velocity = Vector2D((0.5f - MathUtility::RandomFloatUniformDist()), 1.0f); 

			transformComponent->position.x = height*MathUtility::RandomFloatUniformDist(); 
			transformComponent->position.y = 0.0f;			
			transformComponent->scale = Vector2D(1.0f, 1.0f);

			graphicsComponent->resourceId = graphicResourceIds[MathUtility::RandomIntUniformDist() % graphicResourceIds.size()];
			graphicsComponent->transformComponentId = transformComponent->id;
		}
	}
	//---------------------------------------------------------------------------
	// Name: ConstructPlayerWeapons
	// Desc:
	//---------------------------------------------------------------------------
	static void ConstructPlayerWeapons(ComponentRepository* componentRepository)
	{
		const auto collectionName = "PlayerSpaceShipProjectiles"; 
		const auto maxNumProjectiles = 40; 

		componentRepository->NewCollection(collectionName); 
		
		for (auto i = 0; i < maxNumProjectiles; i++) {

			auto entityId = componentRepository->GenerateId();

			auto transformComponent = componentRepository->NewComponent<TransformComponent>(collectionName, entityId); 
			auto graphicsComponent = componentRepository->NewComponent<GraphicsComponent>(collectionName, entityId);
			auto physicsComponent = componentRepository->NewComponent<PhysicsComponent>(collectionName, entityId);

			physicsComponent->radius = 1.0f; 

			graphicsComponent->transformComponentId = transformComponent->id; 
			physicsComponent->transformComponentId = transformComponent->id; 

			graphicsComponent->resourceId = NO_RENDER; 
		}
	}
};


#endif