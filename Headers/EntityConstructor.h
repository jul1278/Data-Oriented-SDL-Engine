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

		TransformComponent* transformComponent = componentRepository->NewComponent<TransformComponent*>(TRANSFORM_COMPONENT);
		GraphicsComponent* graphicsComponent = componentRepository->NewComponent<GraphicsComponent*>(GRAPHICS_COMPONENT); 
		
		transformComponent->position = position; 
		graphicsComponent->transformComponent = transformComponent; 
		graphicsComponent->resourceId = graphicResourceId; 

		newEntity->AddComponent(TRANSFORM_COMPONENT, transformComponent);
		newEntity->AddComponent(GRAPHICS_COMPONENT, graphicsComponent); 
		
		return newEntity->Id();
	}


};

#endif // ENTITY_CONSTRUCTOR_H