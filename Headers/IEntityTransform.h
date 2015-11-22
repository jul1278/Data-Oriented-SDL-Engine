//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_IENTITYTRANSFORM_H
#define SDLRTS_IENTITYTRANSFORM_H

#include <vector>
#include "BaseComponent.h"
#include "Entity.h"
#include "IEvent.h"
#include "ComponentSpec.h"
/*
 * This class provides an interface which allows a generic transform to be applied to a bunch of components
 * These are the so-called 'EntitySystems' found in other component based designs.
 *
 * TODO: IEntityTransform should be able to advertise which entity classes it operates on and what events it can respond to
 * that way a user can call this more generically.
 */

class IEntityTransform
{
public:

    IEntityTransform(ComponentSpecs* componentSpecs) {}

    virtual std::vector<Entity*> Transform(std::vector<Entity*> entities, std::vector<SDL_Event*> events)
    {
        for ( SDL_Event* event : events) {
            Transform(entities, event);
        }

        return entities;
    }

    virtual std::vector<Entity*> Transform( std::vector<Entity*> entities, SDL_Event* event)
    {
        for ( Entity* entity : entities) {
            Transform(entity, event);
        }

        return entities;
    }


    virtual Entity* Transform(Entity* entity, SDL_Event* event) =0;

};

#endif //SDLRTS_IENTITYTRANSFORM_H
