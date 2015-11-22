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
 * These are the so-called 'EntitySystems' found in other component based designs
 *
 *
 *
 */


class IEntityTransform
{
public:

    IEntityTransform(ComponentSpecs* componentSpecs) {}

    virtual void Transform(std::vector<Entity*> entities, std::vector<IEvent*>) =0;
    virtual void Transform(std::vector<Entity*> entities, IEvent* event) =0;
    virtual void Transform(Entity* entity, IEvent event) =0;

};

#endif //SDLRTS_IENTITYTRANSFORM_H
