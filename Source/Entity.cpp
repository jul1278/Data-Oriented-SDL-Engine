//
// Created by Julian  on 17/11/15.
//

#include "../Headers/Entity.h"

//------------------------------------------------------------------------------------
// Name: ~Entity
// Desc:
//------------------------------------------------------------------------------------
Entity::Entity(int id)
{
    this->id = id;
}
//------------------------------------------------------------------------------------
// Name: ~Entity
// Desc:
//------------------------------------------------------------------------------------
Entity::~Entity()
{
    // do we delete all our own components?
}
//------------------------------------------------------------------------------------
// Name: AddComponent
// Desc:
//------------------------------------------------------------------------------------
int Entity::AddComponent(IComponent *component)
{
    if (component) {
        this->components.push_back(component);
        return (this->components.size() - 1);
    } else {
        return -1;
    }
}
//------------------------------------------------------------------------------------
// Name: Update
// Desc:
//------------------------------------------------------------------------------------
void Entity::Update()
{
    for ( IComponent* component : this->components) {
        component->Update();
    }
}
