//
// Created by Julian  on 17/11/15.
//

#ifndef SDL_RTS_ENTITY_H
#define SDL_RTS_ENTITY_H

#include "Components/BaseComponent.h"
#include <map>
#include "ComponentType.h"

struct Entity
{
    std::map<ComponentType, BaseComponent*> componentMap;
    int id;

    void AddComponent(ComponentType componentType, BaseComponent* component)
    {
        this->componentMap.insert(std::pair<ComponentType , BaseComponent*>(componentType, component));
    }

    // Returns null if doesn't exist
    BaseComponent* GetComponent(ComponentType componentType)
    {
        if (this->componentMap.find(componentType) == this->componentMap.end() ) {
            return nullptr;
        }
        return this->componentMap[componentType];
    }
};


#endif //SDL_RTS_ENTITY_H
