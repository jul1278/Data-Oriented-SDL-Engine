//
// Created by Julian  on 25/11/15.
//

#ifndef SDLRTS_COLLISIONTRANSFORM_H
#define SDLRTS_COLLISIONTRANSFORM_H

#include "Transforms/IEntityTransform.h"
#include

class CollisionTransform : public IEntityTransform
{
private:

    ComponentSpecs* componentSpecs;

    std::string entityName;

public:
    CollisionTransform(ComponentSpecs* componentSpecs) : IEntityTransform(componentSpecs)
    {
        this->componentSpecs = componentSpecs;
        this->entityName = "CollisionEntity";
    }

    virtual std::vector<Entity*> Transform( std::vector<Entity*> entities, SDL_Event* event)
    {
        for (int i = 0; i < entities.size(); i++) {

            for (int j = 0; j < entities.size(); j++) {

            }
        }

        return entities;
    }

    virtual Entity* Transform(Entity* entity, SDL_Event* event)
    {
        return entity;
    }

};

#endif //SDLRTS_COLLISIONTRANSFORM_H
