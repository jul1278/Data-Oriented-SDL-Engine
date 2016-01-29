//
// Created by Julian  on 23/02/2016
//

#ifndef ENTITY_CONSTRUCTOR_H
#define ENTITY_CONSTRUCTOR_H

#include "Entity.h"
#include "ComponentRepository.h"
#include "Vector.h"
#include "Components/TransformComponent.h"
#include "Components/GraphicsComponent.h"
#include "GraphicsResources/CircleFIllGraphicsResource.h"

class EntityConstructor
{
public:

	EntityConstructor()
	{
			
	}

	int static ConstructBasicGraphicEntity(ComponentRepository* componentRepository, int graphicResourceId, Vector2D position, float size)
	{
		int entityId = 0; 

		auto newEntity = componentRepository->NewEntity(); 

		auto transformComponent = componentRepository->NewComponent<TransformComponent>();
		auto graphicsComponent = componentRepository->NewComponent<GraphicsComponent>();
		
		transformComponent->position = position;
		transformComponent->orientation = Vector2D(0.0f); 
		transformComponent->scale = Vector2D(1.0f, 1.0f); 

		graphicsComponent->transformComponent = transformComponent;  
		graphicsComponent->resourceId = graphicResourceId; 

		newEntity->AddComponent<TransformComponent>(transformComponent);
		newEntity->AddComponent<GraphicsComponent>(graphicsComponent); 
		
		return newEntity->Id();
	}


};

#endif // ENTITY_CONSTRUCTOR_H