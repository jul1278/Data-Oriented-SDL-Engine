//
// Created by Julian  on 17/11/15.
//

#ifndef SDL_RTS_ICOMPONENT_H
#define SDL_RTS_ICOMPONENT_H

#include "Vector.h"

// NOTE: BaseComponent not IComponent

struct BaseComponent
{
    int id;
    int entityId;

    BaseComponent()
    {
        this->id = 0;
        this->entityId = 0;
    }

};


#endif //SDL_RTS_ICOMPONENT_H
