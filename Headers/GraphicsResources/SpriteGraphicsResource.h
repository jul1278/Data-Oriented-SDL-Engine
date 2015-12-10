//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_SPRITEGRAPHICSRESOURCE_H
#define SDLRTS_SPRITEGRAPHICSRESOURCE_H

#include "GraphicsResources/IGraphicsResource.h"
#include "Graphics.h"
#include "GameApp.h"

class SpriteGraphicsResource : public IGraphicsResource
{
private:

    int w;
    int h;

    SDL_Surface* spriteSurface;
    SDL_Texture* spriteTexture;

public:

    SpriteGraphicsResource(int id, std::string resourceName, SDL_Surface* surface) : IGraphicsResource(id, resourceName)
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

    virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent)
    {
        if (this->spriteTexture == nullptr) {
            this->spriteTexture = SDL_CreateTextureFromSurface(sdlRenderer, this->spriteSurface);
            SDL_SetTextureBlendMode(this->spriteTexture, SDL_BLENDMODE_BLEND);
        }

        float dx = transformComponent->scale.x*this->w - this->w; 
        float dy = transformComponent->scale.x*this->h - this->h;

        uint16_t x = static_cast<uint16_t>(transformComponent->position.x - 0.5f*dx);
        uint16_t y = static_cast<uint16_t>(transformComponent->position.y - 0.5f*dy);
        uint16_t w = static_cast<uint16_t>(this->w*transformComponent->scale.x);
        uint16_t h = static_cast<uint16_t>(this->h*transformComponent->scale.y);

        SDL_Rect dstRect = { x, y, w, h};

        SDL_RenderCopyEx(sdlRenderer, this->spriteTexture, nullptr, &dstRect, transformComponent->orientation.Angle()*(180.0f/PI), NULL, SDL_FLIP_NONE);
    }
};

#endif //SDLRTS_SPRITEGRAPHICSRESOURCE_H
