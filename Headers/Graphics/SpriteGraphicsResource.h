//
// Created by Julian  on 22/11/15.
//

#ifndef SPRITE_GRAPHICS_RESOURCE_H
#define SPRITE_GRAPHICS_RESOURCE_H

#include "Graphics/IGraphicsResource.h"

class SpriteGraphicsResource : public IGraphicsResource
{
private:

    int w;
    int h;

    SDL_Surface* spriteSurface;
    SDL_Texture* spriteTexture;

public:

    SpriteGraphicsResource(SDL_Surface* surface)
    {
        this->spriteSurface = surface;
        this->spriteTexture = nullptr;

        this->w = surface->w;
        this->h = surface->h;
    }

    ~SpriteGraphicsResource()
    {
        SDL_FreeSurface(this->spriteSurface);
    }

	void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) override final
    {
        if (this->spriteTexture == nullptr) {
            this->spriteTexture = SDL_CreateTextureFromSurface(sdlRenderer, this->spriteSurface);
            SDL_SetTextureBlendMode(this->spriteTexture, SDL_BLENDMODE_BLEND);
        }

        auto dx = transformComponent->scale.x*this->w - this->w; 
        auto dy = transformComponent->scale.x*this->h - this->h;

        auto x = static_cast<uint16_t>(transformComponent->position.x - 0.5f*dx);
        auto y = static_cast<uint16_t>(transformComponent->position.y - 0.5f*dy);
        auto w = static_cast<uint16_t>(this->w*transformComponent->scale.x);
        auto h = static_cast<uint16_t>(this->h*transformComponent->scale.y);

        SDL_Rect dstRect = { x - 0.5f*w, y - 0.5f*h, w, h};

        SDL_RenderCopyEx(sdlRenderer, this->spriteTexture, nullptr, &dstRect, transformComponent->orientation.Angle()*(180.0f/M_PI), NULL, SDL_FLIP_NONE);
    }
};

#endif // SPRITE_GRAPHICS_RESOURCE_H
