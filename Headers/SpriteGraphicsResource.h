//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_SPRITEGRAPHICSRESOURCE_H
#define SDLRTS_SPRITEGRAPHICSRESOURCE_H

#include "../Headers/IGraphicsResource.h"
#include "Graphics.h"

class SpriteGraphicsResource : public IGraphicsResource
{
private:

    std::string fileName;

    int w;
    int h;

    SDL_Surface* spriteSurface;
    SDL_Texture* spriteTexture;

public:

    SpriteGraphicsResource(int id, std::string resourceName, SDL_Surface* surface)
            : IGraphicsResource(id, resourceName)
    {
        this->spriteSurface = surface;
        this->spriteTexture = NULL;

        this->w = surface->w;
        this->h = surface->h;
    }

    ~SpriteGraphicsResource()
    {
        SDL_FreeSurface(this->spriteSurface);
    }

    virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent)
    {
        if (this->spriteTexture == NULL) {
            this->spriteTexture = SDL_CreateTextureFromSurface(sdlRenderer, this->spriteSurface);
            SDL_SetTextureBlendMode(this->spriteTexture, SDL_BLENDMODE_BLEND);
        }

        SDL_Rect srcRect = {(int) (transformComponent->position.x - 0.5f*this->w),
                            (int) (transformComponent->position.y - 0.5f*this->h),
                            (this->w),
                            (this->h) };
        SDL_Rect dstRect = srcRect;


        dstRect.x -= 0.5f*dstRect.x*transformComponent->scale.x;
        dstRect.y -= 0.5f*dstRect.y*transformComponent->scale.y;
        dstRect.w *= transformComponent->scale.x;
        dstRect.h *= transformComponent->scale.y;

        SDL_RenderCopyEx(sdlRenderer, this->spriteTexture, &srcRect, &dstRect, transformComponent->orientation.Angle(), NULL, SDL_FLIP_NONE);
    }


};

#endif //SDLRTS_SPRITEGRAPHICSRESOURCE_H
