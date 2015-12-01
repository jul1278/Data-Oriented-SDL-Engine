//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_TRIANGLEGRAPHICSRESOURCE_H
#define SDLRTS_TRIANGLEGRAPHICSRESOURCE_H

#include "GraphicsResources/IGraphicsResource.h"
#include "Graphics.h"

class IsoTriangleGraphicsResource : public IGraphicsResource
{
private:

    float width;
    float height;

    SDL_Surface* triangleSurface;

public:
    IsoTriangleGraphicsResource(int id, std::string resourceName, float width, float height, uint8_t a, uint8_t r, uint8_t g, uint8_t b)
            : IGraphicsResource(id, resourceName)
    {
        this->width = static_cast<float>(width);
        this->height = static_cast<float>(height);

        this->triangleSurface = SDL_CreateRGBSurface(0, this->width, this->height, 32, 0, 0, 0, 0);
        uint32_t color = SDL_MapRGBA(this->triangleSurface->format, r, g, b, a);
        GraphicsUtility::FillIsoTriangle(this->triangleSurface, this->width, this->height, color);
    }

    ~IsoTriangleGraphicsResource()
    {
        if (this->triangleSurface) {
            SDL_FreeSurface(this->triangleSurface);
        }
    }

    virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent)
    {
        uint8_t x = static_cast<int>(transformComponent->position.x - 0.5f*transformComponent->scale.x);
        uint8_t y = static_cast<int>(transformComponent->position.y - 0.5f*transformComponent->scale.y); 

        SDL_Rect rect = { x, y, this->width, this->height };
          
        SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, this->triangleSurface);

        if (texture == nullptr) {
            // TODO: error
            return;
        }

        SDL_RenderCopyEx(sdlRenderer, texture, nullptr, &rect, (180.0f/PI)*transformComponent->orientation.Angle(), nullptr, SDL_FLIP_NONE);
    }
};

#endif //SDLRTS_TRIANGLEGRAPHICSRESOURCE_H
