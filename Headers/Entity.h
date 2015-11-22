//
// Created by Julian  on 17/11/15.
//

#ifndef SDL_RTS_ENTITY_H
#define SDL_RTS_ENTITY_H

#include "IComponent.h"
#include <vector>

struct Entity
{
    std::vector<IComponent*> components;
    int id;
};


#endif //SDL_RTS_ENTITY_H
