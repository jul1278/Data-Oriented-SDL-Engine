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

//const float defaultProjectileSpeed = 4.0f;

class SpaceGameEntityConstructor
{
public:

	int static ConstructBasicGraphicEntity(ComponentCollectionRepository* componentCollectionRepository, int graphicResourceId, Vector2D position, float size)
	{

	}

	void static ConstructBackgroundStars(ComponentCollectionRepository* componentCollectionRepository, int graphicResourceId, int width, int height, int num)
	{
		const string collectionName = "ScrollingBackgroundStars";
		const float starScrollVelocity = 1.0f; 

		componentCollectionRepository->NewCollection(collectionName); 

		for (auto i = 0; i < num; i++) {
			auto transformComponent = componentCollectionRepository->NewComponent<TransformComponent>(collectionName);
			auto graphicsComponent = componentCollectionRepository->NewComponent<GraphicsComponent>(collectionName); 
			auto physicsComponent = componentCollectionRepository->NewComponent<SimplePhysicsComponent>(collectionName); 

			transformComponent->scale = Vector2D(1.0f, 1.0f); 
			transformComponent->position.x = i*(width / num); 
			transformComponent->position.y = ((int)expf(i)) % height; 

			graphicsComponent->resourceId = graphicResourceId; 
			graphicsComponent->transformComponent = transformComponent;

			physicsComponent->transformComponent = transformComponent; 
			physicsComponent->velocity.y = starScrollVelocity; 
		}
	}

};


#endif