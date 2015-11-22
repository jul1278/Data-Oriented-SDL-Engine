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

    std::string entityName;
    float moveIncrement;


public:

    PlayerMoveTransform(ComponentSpecs *componentSpecs) : IEntityTransform(componentSpecs)
    {
        entityName = "BasicPlayer";
        moveIncrement = 1.0f;
        this->componentSpecs = componentSpecs;
    }

    virtual Entity* Transform(Entity* entity, SDL_Event* event)
    {
        // Check if we can actually respond to this event
        if (event->type != SDL_KEYDOWN) {
            return entity;
        }

        // Check that our entity has the correct components to satisfy this transform
        if (!componentSpecs->CheckEntityMeetsSpec(entity, this->entityName)) {
            return entity;
        }

        TransformComponent* transformComponent = (TransformComponent*)entity->GetComponent(TRANSFORM_COMPONENT);

        switch(event->key.keysym.scancode) {

            case SDL_SCANCODE_LEFT: {
                transformComponent->position.x -= this->moveIncrement;
                break;
            }

            case SDL_SCANCODE_RIGHT: {
                transformComponent->position.x += this->moveIncrement;
                break;
            }

            case SDL_SCANCODE_UP: {
                transformComponent->position.y -= this->moveIncrement;
                break;
            }

            case SDL_SCANCODE_DOWN: {
                transformComponent->position.y += this->moveIncrement;
                break;
            }
        }

        return entity;
    }

};

#endif //SDLRTS_PLAYERMOVETRANSFORM_H
