//
// Created by Julian  on 22/11/15.
//

#ifndef SDL_RTS_TRANSFORMCOMPONENT_H
#define SDL_RTS_TRANSFORMCOMPONENT_H

#include "Vector.h"

class TransformComponent
{
public:

    int id;

    Vector2D position;
    Vector2D scale;
    Vector2D orientation;

    TransformComponent()
    {
        this->id = 0;
    }
    TransformComponent(int id, Vector2D position, Vector2D orientation, Vector2D scale)
    {
        this->id = id;
        this->position = position;
        this->orientation = orientation;
        this->scale = scale;
    }
};


#endif //SDL_RTS_TRANSFORMCOMPONENT_H
