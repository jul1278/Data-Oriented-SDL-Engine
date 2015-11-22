//
// Created by Julian  on 17/11/15.
//

#ifndef SDL_RTS_GRAPHICSCOMPONENT_H
#define SDL_RTS_GRAPHICSCOMPONENT_H

#include <string>
#include "Vector.h"
#include "Graphics.h"

// GraphicsComponent
struct GraphicsComponent
{
    int id;
    int resourceId;
    int transformId;

    GraphicsComponent(int id, int resourceId, int transformId)
    {
        this->id = id;
        this->resourceId = resourceId;
        this->transformId = transformId;
    }
};




#endif //SDL_RTS_GRAPHICSCOMPONENT_H
