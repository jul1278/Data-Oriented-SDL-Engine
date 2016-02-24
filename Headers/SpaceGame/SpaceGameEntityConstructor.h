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

const float defaultProjectileSpeed = 4.0f;

class EntityConstructor
{


	int static ConstructBasicGraphicEntity(ComponentCollectionRepository* componentCollectionRepository, int graphicResourceId, Vector2D position, float size)
	{

	}

};


#endif