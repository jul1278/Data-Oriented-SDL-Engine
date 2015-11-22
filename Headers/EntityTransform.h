//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_ICOMPONENTTRANSFORM_H
#define SDLRTS_ICOMPONENTTRANSFORM_H

#include <vector>
#include "BaseComponent.h"
#include "Entity.h"
#include "IEvent.h"
/*
 * This class provides an interface which allows a generic transform to be applied to a bunch of components
 * These are the so-called 'EntitySystems' found in other component based designs
 *
 *
 *
 */


class EntityTransform
{
public:

    EntityTransform();

    virtual void Transform(std::vector<Entity*> entities, std::vector<IEvent*>) =0;
};

#endif //SDLRTS_ICOMPONENTTRANSFORM_H
