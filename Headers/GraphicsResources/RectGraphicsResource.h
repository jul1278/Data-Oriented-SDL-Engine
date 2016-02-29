//
// Created by Julian  on 22/11/15.
//

#ifndef RECTGRAPHICSRESOURCE_H
#define RECTGRAPHICSRESOURCE_H

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
    SDL_Texture* texture;

public:

    RectGraphicsResource(float width, float height, uint8_t a, uint8_t r, uint8_t g, uint8_t b)
    {
        this->width = width;
        this->height = height;
        this->a = a;
        this->r = r;
        this->g = g;
        this->b = b;

        this->texture = nullptr;

        this->surface = SDL_CreateRGBSurface(0, static_cast<int>(width), static_cast<int>(height), 32, 0, 0, 0, 0);

        if (surface == nullptr) {
            // TODO: error
            return; 
        }

        SDL_FillRect(surface, nullptr, SDL_MapRGBA(surface->format, this->r, this->g, this->b, this->a));
    };

    ~RectGraphicsResource()
    {
        if (this->surface) {
            SDL_FreeSurface(this->surface);
        }
    }

    virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent)
    {
        float scaleX = transformComponent->scale.x; 
        float scaleY = transformComponent->scale.y; 

        float dx = scaleX*this->width - this->width; 
        float dy = scaleY*this->height - this->height; 

        uint16_t x = static_cast<uint16_t>(transformComponent->position.x - 0.5f*dx);
        uint16_t y = static_cast<uint16_t>(transformComponent->position.y - 0.5f*dy);
        uint16_t w = this->width*scaleX;
        uint16_t h = this->height*scaleY;

        SDL_Rect rect = { x, y, w, h};

        if (this->texture == nullptr) {
           this->texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
        }

        if (texture == nullptr) {
            // TODO: error
            return;
        }

        SDL_RenderCopyEx(sdlRenderer, texture, nullptr, &rect, 0.25f*M_PI/*(180.0f/PI)*transformComponent->orientation.Angle()*/, nullptr, SDL_FLIP_NONE);
    }
};


#endif //RECTGRAPHICSRESOURCE_H
