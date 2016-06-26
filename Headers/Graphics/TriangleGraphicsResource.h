//
// Created by Julian  on 22/11/15.
//

#ifndef TRIANGLE_GRAPHICS_RESOURCE_H
#define TRIANGLE_GRAPHICS_RESOURCE_H

#include "Graphics/IGraphicsResource.h"
#include <SDL.h>
#include "GraphicsUtility.h"

class IsoTriangleGraphicsResource : public IGraphicsResource
{
private:

    float width;
    float height;

    struct SDL_Surface* triangleSurface;
    SDL_Texture* texture; 

public:

    IsoTriangleGraphicsResource(float width, float height, const Color& color)
    {
        this->texture = nullptr;

        this->width = static_cast<float>(width);
        this->height = static_cast<float>(height);

        this->triangleSurface = SDL_CreateRGBSurface(0, this->width, this->height, 32, 0, 0, 0, 0);
        GraphicsUtility::FillIsoTriangle(this->triangleSurface, this->width, this->height, color.Rgba());
    }

    ~IsoTriangleGraphicsResource()
    {
        if (this->triangleSurface) {
            SDL_FreeSurface(this->triangleSurface);
        }
    }

	void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) override final 
    {        
        if (texture == nullptr) {
            texture = SDL_CreateTextureFromSurface(sdlRenderer, this->triangleSurface);
        }

        auto x = static_cast<uint16_t >(transformComponent->position.x - 0.5f*transformComponent->scale.x);
        auto y = static_cast<uint16_t>(transformComponent->position.y - 0.5f*transformComponent->scale.y);
		
        auto w = this->width;
        auto h = this->height;

        SDL_Rect rect = { x, y, w, h};

        SDL_RenderCopyEx(sdlRenderer, texture, nullptr, &rect, (180.0f/M_PI)*transformComponent->orientation.Angle(), nullptr, SDL_FLIP_NONE);
    }
};

#endif // TRIANGLE_GRAPHICS_RESOURCE_H
