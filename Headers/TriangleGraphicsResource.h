//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_TRIANGLEGRAPHICSRESOURCE_H
#define SDLRTS_TRIANGLEGRAPHICSRESOURCE_H

#include "../Headers/IGraphicsResource.h"
#include "Graphics.h"

class TriangleGraphicsResource : public IGraphicsResource
{
private:

    float width;
    float height;

public:
    TriangleGraphicsResource(int id, std::string resourceName, float width, float height, uint8_t a, uint8_t r, uint8_t g, uint8_t b)
            : IGraphicsResource(id, resourceName)
    { }

    virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent)
    {

    }

};

#endif //SDLRTS_TRIANGLEGRAPHICSRESOURCE_H
