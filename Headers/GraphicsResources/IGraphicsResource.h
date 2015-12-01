//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_IGRAPHICSRESOURCE_H
#define SDLRTS_IGRAPHICSRESOURCE_H

#include "Components/TransformComponent.h"

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

    int Id() const { return this->id; }
    std::string ResourceName() const { return this->resourceName;}

    virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) = 0;
};

#endif //SDLRTS_GRAPHICSRESOURCE_H
