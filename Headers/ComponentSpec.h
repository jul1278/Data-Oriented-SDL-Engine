//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_COMPONENTSPEC_H
#define SDLRTS_COMPONENTSPEC_H

#include <vector>
#include <string>
#include <map>
#include "ComponentType.h"
#include "Entity.h"


class ComponentSpecs
{
private:

    std::map<std::string, std::vector<ComponentType>> componentTypeMap;

public:

    ComponentSpecs();

    void RegisterEntitySpec(std::string entityName, std::vector<ComponentType> componentTypes);

    bool EntitySpecExists(std::string entityName);
    bool CheckEntityMeetsSpec(Entity* entity, std::string EntityName);
};

#endif //SDLRTS_COMPONENTSPEC_H
