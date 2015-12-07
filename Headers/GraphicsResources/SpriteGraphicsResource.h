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

        uint16_t x = static_cast<uint16_t>(transformComponent->position.x - 0.5f*this->w);
        uint16_t y = static_cast<uint16_t>(transformComponent->position.y - 0.5f*this->h);

        SDL_Rect dstRect = {x, y, this->w, this->h };

        // TODO: scale
//        dstRect.x -= 0.5f*dstRect.x*transformComponent->scale.x;
//        dstRect.y -= 0.5f*dstRect.y*transformComponent->scale.y;
//        dstRect.w *= transformComponent->scale.x;
//        dstRect.h *= transformComponent->scale.y;

        SDL_RenderCopyEx(sdlRenderer, this->spriteTexture, nullptr, &dstRect, transformComponent->orientation.Angle()*(180.0f/PI), NULL, SDL_FLIP_NONE);
    }
};

#endif //SDLRTS_SPRITEGRAPHICSRESOURCE_H
