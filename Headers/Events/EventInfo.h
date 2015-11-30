//
// Created by Julian  on 26/11/15.
//

#ifndef SDLRTS_EVENTINFO_H
#define SDLRTS_EVENTINFO_H

#include <Vector.h>

struct IEventInfo {};

// MouseClickEvent
struct MouseClickEvent : public IEventInfo
{
    MouseClickEvent(Vector2D pos)
    {
        this->pos = pos;
    }

    Vector2D pos;
};

// MessageEvent
struct MessageEvent : public IEventInfo
{
    MessageEvent(std::string message) {this->message = message;}
    std::string message;
};

#endif //SDLRTS_EVENTINFO_H
