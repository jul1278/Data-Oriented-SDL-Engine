//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_RESOURCES_H
#define SDLRTS_RESOURCES_H

#include <iostream>
#include <vector>
#include <map>
#include "SDL.h"
#include "SDL_image.h"
#include "GraphicsResources/IGraphicsResource.h"

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
