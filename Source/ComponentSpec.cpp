//
// Created by Julian  on 22/11/15.
//

#include "ComponentSpec.h"
//------------------------------------------------------------------------------
// Name: ComponentSpecs
// Desc:
//------------------------------------------------------------------------------
ComponentSpecs::ComponentSpecs()
{
}
//------------------------------------------------------------------------------
// Name: RegisterEntitySpec
// Desc:
//------------------------------------------------------------------------------
void ComponentSpecs::RegisterEntitySpec(std::string entityName, std::vector<ComponentType> componentTypes)
{
    if (this->EntitySpecExists(entityName)) {
        return;
    }

    this->componentTypeMap.insert(std::pair<std::string, std::vector<ComponentType >>(entityName, componentTypes));
}
//------------------------------------------------------------------------------
// Name: EntitySpecExists
// Desc:
//------------------------------------------------------------------------------
bool ComponentSpecs::EntitySpecExists(std::string entityName)
{
    if (this->componentTypeMap.find(entityName) == this->componentTypeMap.end()) {
        return false;
    }

    return true;
}
//------------------------------------------------------------------------------
// Name: CheckEntityMeetsSpec
// Desc:
//------------------------------------------------------------------------------
bool ComponentSpecs::CheckEntityMeetsSpec(Entity *entity, std::string entityName)
{
    if (this->EntitySpecExists(entityName) == false) {
        return false;
    }

    std::vector<ComponentType> spec = this->componentTypeMap[entityName];

    // if we can find all the spec components then return true
    for(ComponentType componentType : spec) {

        if (entity->componentMap.find(componentType) == entity->componentMap.end()) {
            return false;
        }
    }

    return true;
}

