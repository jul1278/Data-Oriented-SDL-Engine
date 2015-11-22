//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_ENTITYLIST_H
#define SDLRTS_ENTITYLIST_H

#include <map>
#include <vector>
#include "IComponent.h"

class EntityList
{
private:

    std::map<int, std::vector<IComponent*>> entityComponentMap;

public:

    EntityList();

    void Update()

};


#endif //SDLRTS_ENTITYLIST_H
