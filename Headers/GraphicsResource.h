//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_GRAPHICSRESOURCE_H
#define SDLRTS_GRAPHICSRESOURCE_H

#include <iosfwd>
#include <string>

class GraphicsResource
{
    int id;
    std::string resourceName;

    GraphicsResource(int id, std::string resourceName)
    {
        this->id = id;
        this->resourceName = resourceName;
    }
};


#endif //SDLRTS_GRAPHICSRESOURCE_H
