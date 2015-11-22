//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_IGRAPHICSRESOURCE_H
#define SDLRTS_IGRAPHICSRESOURCE_H

#include <iosfwd>
#include <string>
#include "../Headers/TransformComponent.h"

class IGraphicsResource
{
private:

    int id;
    std::string resourceName;

public:


    IGraphicsResource(int id, std::string resourceName)
    {
        this->id = id;
        this->resourceName = resourceName;
    }

    int Id() {return this->id;}
    std::string ResourceName() { return this->resourceName;}

    virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) = 0;
};

// TriangleGraphicsResource





#endif //SDLRTS_GRAPHICSRESOURCE_H
