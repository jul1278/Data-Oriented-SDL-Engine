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
#include "Components/SimplePhysicsComponent.h"
#include "GraphicsResources/CircleFIllGraphicsResource.h"

const float defaultProjectileSpeed = 4.0f; 

class EntityConstructor
{
private:

	

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

	int static ConstructBasicPlayerEntity(ComponentRepository* componentRepository, int graphicResourceId, Vector2D position, float size)
	{
		int entityId = 0;

		auto newEntity = componentRepository->NewEntity();

		auto transformComponent = componentRepository->NewComponent<TransformComponent>();
		auto graphicsComponent = componentRepository->NewComponent<GraphicsComponent>();
		auto simplePhysicsComponent = componentRepository->NewComponent<SimplePhysicsComponent>(); 

		transformComponent->position = position;
		transformComponent->orientation = Vector2D(0.0f);
		transformComponent->scale = Vector2D(1.0f, 1.0f);

		graphicsComponent->transformComponent = transformComponent;
		graphicsComponent->resourceId = graphicResourceId;

		simplePhysicsComponent->transformComponent = transformComponent; 
		simplePhysicsComponent->velocity = Vector2D(0.0f, 0.0f); 

		newEntity->AddComponent<SimplePhysicsComponent>(simplePhysicsComponent); 
		newEntity->AddComponent<TransformComponent>(transformComponent);
		newEntity->AddComponent<GraphicsComponent>(graphicsComponent);

		return newEntity->Id();
	}

	int static ConstructBasicProjectile(ComponentRepository* componentRepository, int graphicResourceId, Vector2D initalPosition, Vector2D direction)
	{
		int entityId = 0; 
		auto newEntity = componentRepository->NewEntity();

		auto transformComponent = componentRepository->NewComponent<TransformComponent>();
		auto graphicsComponent = componentRepository->NewComponent<GraphicsComponent>();
		auto simplePhysicsComponent = componentRepository->NewComponent<SimplePhysicsComponent>();

		transformComponent->position = initalPosition; 
		transformComponent->orientation = Vector2D(0.0f);
		transformComponent->scale = Vector2D(1.0f, 1.0f);

		graphicsComponent->resourceId = graphicResourceId; 
		graphicsComponent->transformComponent = transformComponent; 
		
		simplePhysicsComponent->transformComponent = transformComponent; 
		simplePhysicsComponent->velocity = direction; 
		simplePhysicsComponent->velocity.y *= defaultProjectileSpeed; 

		newEntity->AddComponent<TransformComponent>(transformComponent); 
		newEntity->AddComponent<GraphicsComponent>(graphicsComponent);
		newEntity->AddComponent<SimplePhysicsComponent>(simplePhysicsComponent);

		return newEntity->Id(); 
	}


};

#endif // ENTITY_CONSTRUCTOR_H