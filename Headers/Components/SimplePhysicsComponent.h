//
// Created by Julian  on 18/12/15.
//

#ifndef SIMPLE_PHYSICS_COMPONENT_H
#define SIMPLE_PHYSICS_COMPONENT_H

#include "BaseComponent.h"
#include "TransformComponent.h"

struct SimplePhysicsComponent : BaseComponent
{
	float mass;
	float radius;

	Vector2D velocity; 
	Vector2D acceleration; 

	TransformComponent* transformComponent;

	SimplePhysicsComponent()
	{
		this->mass = 0.0f; 
		this->radius = 0.0f; 
		this->transformComponent = nullptr; 
	}

	SimplePhysicsComponent(float mass, float radius, Vector2D velocity, Vector2D acceleration, TransformComponent* transformComponent = nullptr)
	{
		this->transformComponent = transformComponent;
		this->mass = mass;
		this->radius = radius; 

		this->acceleration = acceleration; 
		this->velocity = velocity; 
	}
};

#endif //SIMPLE_PHYSICS_COMPONENT