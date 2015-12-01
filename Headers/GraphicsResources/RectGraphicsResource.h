//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_RECTGRAPHICSRESOURCE_H
#define SDLRTS_RECTGRAPHICSRESOURCE_H

#include "GraphicsResources/IGraphicsResource.h"
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

    SDL_Surface* surface;

public:

    RectGraphicsResource(int id, std::string resourceName, float width, float height, uint8_t a, uint8_t r, uint8_t g, uint8_t b) : IGraphicsResource(id, resourceName)
    {
        this->width = width;
        this->height = height;
        this->a = a;
        this->r = r;
        this->g = g;
        this->b = b;

        this->surface = SDL_CreateRGBSurface(0, static_cast<int>(width), static_cast<int>(height), 32, 0, 0, 0, 0);

        if (surface == nullptr) {
            // TODO: error
        }
    };

    ~RectGraphicsResource()
    {
        if (this->surface) {
            SDL_FreeSurface(this->surface);
        }
    }

    virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent)
    {
        uint8_t x = static_cast<int>(transformComponent->position.x - 0.5f*transformComponent->scale.x);
        uint8_t y = static_cast<int>(transformComponent->position.y - 0.5*transformComponent->scale.y);

        SDL_Rect rect = { x, y, this->width, this->height}; 


        SDL_FillRect(surface, nullptr, SDL_MapRGBA(surface->format, this->r, this->g, this->b, this->a));
        SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);

        if (texture == nullptr) {
            // TODO: error
            return;
        }

        SDL_RenderCopyEx(sdlRenderer, texture, nullptr, &rect, (180.0f/PI)*transformComponent->orientation.Angle(), nullptr, SDL_FLIP_NONE);
    }
};


#endif //SDLRTS_RECTGRAPHICSRESOURCE_H
