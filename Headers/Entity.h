//
// Created by Julian  on 17/11/15.
//

#ifndef SDL_RTS_ENTITY_H
#define SDL_RTS_ENTITY_H

#include "IComponent.h"
#include <vector>

class Entity
{
private:

    std::vector<IComponent*> components;
    int id;

public:

    Entity(int id);
    ~Entity();


    int AddComponent(IComponent* component);

    void Update();
    int Id() { return this->id;}
};


#endif //SDL_RTS_ENTITY_H
