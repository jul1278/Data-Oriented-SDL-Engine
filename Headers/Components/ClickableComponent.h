//
// Created by Julian  on 28/11/15.
//

#ifndef SDLRTS_CLICKABLECOMPONENT_H
#define SDLRTS_CLICKABLECOMPONENT_H

#include "Vector.h"

struct ClickAbleComponent : public BaseComponent
{
    int transformId;
    int eventHandlerId; 
    Vector2D clickArea;

    ClickAbleComponent(int transformId, int eventHandlerId, Vector2D clickArea)
    {
        this->transformId = transformId;
        this->eventHandlerId = eventHandlerId; 
        this->clickArea = clickArea;
    }
};

#endif //SDLRTS_CLICKABLECOMPONENT_H

