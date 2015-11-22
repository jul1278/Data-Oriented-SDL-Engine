//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_PLAYERMOVETRANSFORM_H
#define SDLRTS_PLAYERMOVETRANSFORM_H

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

    virtual void Transform(std::vector<Entity*> entities, std::vector<IEvent*> events)
    {
        for ( IEvent* event : events) {
            Transform(entities, event);
        }
    }

    virtual void Transform( std::vector<Entity*> entities, IEvent* event)
    {
        for ( Entity* entity : entities) {
            Transform(entity, event);
        }
    }

    virtual void Transform(Entity* entity, IEvent* event)
    {
        // Check that our entity has the correct components to satisfy this transform
        if (!componentSpecs->CheckEntityMeetsSpec(entity, this->entiyName)) {
            return;
        }

        TransformComponent* transformComponent = (TransformComponent*)entity->GetComponent(TRANSFORM_COMPONENT);

        switch(event->eventType) {

        }
    }

};

#endif //SDLRTS_PLAYERMOVETRANSFORM_H
