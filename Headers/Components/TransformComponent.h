//
// Created by Julian  on 22/11/15.
//

#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "BaseComponent.h"
#include "Utility/Vector.h"

struct TransformComponent : BaseComponent
{
    Vector2D position;
    Vector2D scale;
    Vector2D orientation;

	TransformComponent()
	{
		this->position = Vector2D(0.0f, 0.0f); 
		this->scale = Vector2D(1.0f, 1.0f); 
		this->orientation = Vector2D(0.0f, 0.0f);
	}

	TransformComponent(Vector2D position)
	{
		this->position = position; 
		this->orientation = Vector2D(0.0f); 
		this->scale = Vector2D(1.0f, 1.0f); 
	}

    TransformComponent(Vector2D position, Vector2D orientation, Vector2D scale)
    {
        this->position = position;
        this->orientation = orientation;
        this->scale = scale;
    }

	float Angle() const
	{
		return atan2f(this->orientation.y, this->orientation.x); 
	}
};


#endif //TRANSFORMCOMPONENT_H
