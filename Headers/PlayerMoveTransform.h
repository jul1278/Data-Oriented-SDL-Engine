//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_PLAYERMOVETRANSFORM_H
#define SDLRTS_PLAYERMOVETRANSFORM_H

#include <SDL2/SDL_events.h>
#include "IEntityTransform.h"
#include "ComponentSpec.h"
#include "TransformComponent.h"

class PlayerMoveTransform : public IEntityTransform
{
private:

    ComponentSpecs* componentSpecs;

    std::string entiyName;
    float moveIncrement;


public:

    PlayerMoveTransform(ComponentSpecs *componentSpecs) : IEntityTransform(componentSpecs)
    {
        this->componentSpecs = componentSpecs;
    }

    virtual void Transform(std::vector<Entity*> entities, std::vector<SDL_Event*> events)
    {
        for ( SDL_Event* event : events) {
            Transform(entities, event);
        }
    }

    virtual void Transform( std::vector<Entity*> entities, SDL_Event* event)
    {
        for ( Entity* entity : entities) {
            Transform(entity, event);
        }
    }

    virtual void Transform(Entity* entity, SDL_Event* event)
    {
        // Check that our entity has the correct components to satisfy this transform
        if (!componentSpecs->CheckEntityMeetsSpec(entity, this->entiyName)) {
            return;
        }

        TransformComponent* transformComponent = (TransformComponent*)entity->GetComponent(TRANSFORM_COMPONENT);

        switch() {

            case

        }
    }

};

#endif //SDLRTS_PLAYERMOVETRANSFORM_H
