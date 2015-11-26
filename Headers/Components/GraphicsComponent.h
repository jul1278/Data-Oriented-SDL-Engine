//
// Created by Julian  on 17/11/15.
//

#ifndef SDL_RTS_GRAPHICSCOMPONENT_H
#define SDL_RTS_GRAPHICSCOMPONENT_H

#include <string>
#include "Components/BaseComponent.h"
#include "Graphics.h"

// GraphicsComponent
struct GraphicsComponent : BaseComponent
{
    int resourceId;
    int transformId;

    GraphicsComponent(int resourceId, int transformId)
    {
        this->resourceId = resourceId;
        this->transformId = transformId;
    }
};




#endif //SDL_RTS_GRAPHICSCOMPONENT_H
