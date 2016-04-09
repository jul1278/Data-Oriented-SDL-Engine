//
// Created by Julian  on 22/11/15.
//

#ifndef RECT_GRAPHICS_RESOURCE_H
#define RECT_GRAPHICS_RESOURCE_H

#include "Graphics/IGraphicsResource.h"

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

	void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) override final
    {
        auto scaleX = transformComponent->scale.x; 
        auto scaleY = transformComponent->scale.y; 
		
        auto dx = scaleX*this->width - this->width; 
        auto dy = scaleY*this->height - this->height; 
		
        auto  x = static_cast<uint16_t>(transformComponent->position.x - 0.5f*dx);
        auto  y = static_cast<uint16_t>(transformComponent->position.y - 0.5f*dy);
        auto  w = this->width*scaleX;
        auto  h = this->height*scaleY;

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
