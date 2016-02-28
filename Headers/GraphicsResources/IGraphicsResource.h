//
// Created by Julian  on 22/11/15.
//

#ifndef IGRAPHICSRESOURCE_H
#define IGRAPHICSRESOURCE_H

#include <GraphicsUtility.h>
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

#endif //GRAPHICSRESOURCE_H
