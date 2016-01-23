//
// Created by Julian  on 28/11/15.
//

#ifndef CLICKABLECOMPONENT_H
#define CLICKABLECOMPONENT_H

#include "Vector.h"
#include "BaseComponent.h"

struct ClickAbleComponent : BaseComponent
{

    int eventHandlerId; 
    Vector2D clickArea;
	
	TransformComponent* transformComponent; 

	ClickAbleComponent(int eventHandlerId, Vector2D clickArea, TransformComponent* transformComponent = nullptr)
    {
		this->transformComponent = transformComponent; 
        this->eventHandlerId = eventHandlerId; 
        this->clickArea = clickArea;
    }
};

#endif //CLICKABLECOMPONENT_H

