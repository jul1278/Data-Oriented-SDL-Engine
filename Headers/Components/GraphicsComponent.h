//
// Created by Julian  on 17/11/15.
//
#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H

#include "TransformComponent.h"

// GraphicsComponent
struct GraphicsComponent : public BaseComponent
{
    int resourceId;
	TransformComponent* transformComponent; 

    GraphicsComponent(int resourceId, TransformComponent* transformComponent = nullptr)
    {
		this->transformComponent = transformComponent; 
        this->resourceId = resourceId;
    }
};




#endif //GRAPHICS_COMPONENT_H
