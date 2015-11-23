//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_CIRCLEGRAPHICSRESOURCE_H
#define SDLRTS_CIRCLEGRAPHICSRESOURCE_H

#include "GraphicsResources/IGraphicsResource.h"
#include "Graphics.h"

// CircleGraphicsResource
class CircleGraphicsResource : public IGraphicsResource
{
private:

    float radius;
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;

public:

    CircleGraphicsResource(int id, std::string resourceName, float radius, uint8_t a, uint8_t r, uint8_t g, uint8_t b) : IGraphicsResource(id, resourceName)
    {
        this->radius = radius;
        this->a = a;
        this->r = r;
        this->g = g;
        this->b = b;
    };

    ~CircleGraphicsResource() {}

    virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent)
    {
    }
};

#endif //SDLRTS_CIRCLEGRAPHICSRESOURCE_H
