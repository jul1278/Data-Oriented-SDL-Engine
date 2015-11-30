//
// Created by Julian  on 28/11/15.
//

#ifndef SDLRTS_CLICKABLECOMPONENT_H
#define SDLRTS_CLICKABLECOMPONENT_H

struct ClickAbleComponent : public BaseComponent
{
    int transformId;
    Vector2D clickArea;

    ClickAbleComponent(int transformId, Vector2D clickArea)
    {
        this->transformId = transformId;
        this->clickArea = clickArea;
    }
};

#endif //SDLRTS_CLICKABLECOMPONENT_H

