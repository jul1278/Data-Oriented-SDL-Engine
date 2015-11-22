//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_RECTGRAPHICSRESOURCE_H
#define SDLRTS_RECTGRAPHICSRESOURCE_H

#include "IGraphicsResource.h"
#include "Graphics.h"

// RectGraphicsResource
class RectGraphicsResource : public IGraphicsResource
{
private:

    float width;
    float height;
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;

public:

    RectGraphicsResource(int id, std::string resourceName, float width, float height, uint8_t a, uint8_t r, uint8_t g, uint8_t b) : IGraphicsResource(id, resourceName)
    {
        this->width = width;
        this->height = height;
        this->a = a;
        this->r = r;
        this->g = g;
        this->b = b;
    };

    ~RectGraphicsResource() {}

    virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent)
    {

        SDL_Rect rect = {
                (int)(transformComponent->position.x-0.5f*transformComponent->scale.x),
                (int)(transformComponent->position.y-0.5*transformComponent->scale.y),
                (int)this->width,
                (int)this->height
        };

        SDL_Surface* surface = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0);
        SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, this->r, this->g, this->b, this->a));
        SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);

        SDL_FreeSurface(surface);
        SDL_RenderCopyEx(sdlRenderer, texture, NULL, &rect, (180.0f/PI)*transformComponent->orientation.Angle(), NULL, SDL_FLIP_NONE);
    }
};


#endif //SDLRTS_RECTGRAPHICSRESOURCE_H
