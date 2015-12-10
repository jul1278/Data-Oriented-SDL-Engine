//
// Created by Julian  on 10/12/15.
//

#ifndef SDL_RTS_EVENTS_H
#define SDL_RTS_EVENTS_H

#include <vector>
#include "Events/Event.h"
#include "Components/BaseComponent.h"

class Events
{
private:

public:
    Events() {}
    ~Events() {}

    void Update(Event* event, std::vector<BaseComponent*> transformComponents, std::vector<BaseComponent*> clickableComponents)
    {
        
    }
};

#endif //SDL_RTS_EVENTS_H