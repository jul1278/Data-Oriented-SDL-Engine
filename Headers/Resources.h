//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_RESOURCES_H
#define SDLRTS_RESOURCES_H

#include <iostream>
#include <vector>
#include <map>
#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#include "/Library/Frameworks/SDL2_image.framework/Headers/SDL_image.h"
#include "IGraphicsResource.h"

// Resources
class Resources
{
private:

    std::map<std::string, IGraphicsResource*> graphicsResourceMap;

public:

    Resources();
    ~Resources();

};


#endif //SDLRTS_RESOURCES_H
