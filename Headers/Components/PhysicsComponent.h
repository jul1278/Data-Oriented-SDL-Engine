//
// Created by Julian  on 18/12/15.
//

#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "BaseComponent.h"
#include "TransformComponent.h"

struct PhysicsComponent : BaseComponent
{
	float mass;
	float radius;

	float angularAcceleration; 
	float angularVelocity; 

	Vector2D velocity;
	Vector2D acceleration;

	TransformComponent* transformComponent;

	PhysicsComponent()
	{
		this->mass = 0.0f;
		this->radius = 0.0f;

		this->angularAcceleration = 0.0f; 
		this->angularVelocity = 0.0f; 

		this->transformComponent = nullptr;
	}
};

#endif // PHYSICS_COMPONENT_H