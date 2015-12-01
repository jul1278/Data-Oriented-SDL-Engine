//
// Created by Julian  on 25/11/15.
//

#ifndef SDLRTS_CIRCLEOUTLINEGRAPHICSRESOURCE_H
#define SDLRTS_CIRCLEOUTLINEGRAPHICSRESOURCE_H

#include "GraphicsResources/IGraphicsResource.h"
#include "Graphics.h"

// CircleGraphicsResource
class CircleOutlineGraphicsResource : public IGraphicsResource
{
private:

    uint8_t radius;
    uint8_t thickness;

    SDL_Surface* circleSurface;

public:

    CircleOutlineGraphicsResource(int id, std::string resourceName, float radius, float thickness, uint8_t a, uint8_t r, uint8_t g, uint8_t b) : IGraphicsResource(id, resourceName)
    {
        this->radius = static_cast<uint8_t>(floor(radius));

        if ((thickness < radius) && (thickness > 0.0f)) {
            this->thickness = static_cast<uint8_t>(floor(thickness));
        } else {
            this->thickness = 1;
        }

        circleSurface = SDL_CreateRGBSurface(0, 2*this->radius, 2*this->radius, 32, 0, 0, 0, 0);

        uint32_t color = SDL_MapRGBA(this->circleSurface->format, r, g, b, a);
        GraphicsUtility::OutlineCircle(circleSurface, this->radius, this->thickness, color);

    };

    ~CircleOutlineGraphicsResource()
    {
        if (this->circleSurface) {
            SDL_FreeSurface(this->circleSurface);
        }
    }

    virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent)
    {
        if (this->circleSurface == nullptr) {
            // TODO: how do error/warnings? be nice to be able to print them somewhere, std::cout though lol
            return;
        }

        if (transformComponent == nullptr) {
            return;
        }

        if (sdlRenderer == nullptr) {
            return;
        }

        SDL_Texture* circleTexture = SDL_CreateTextureFromSurface(sdlRenderer, this->circleSurface);

        uint8_t x = static_cast<int>(transformComponent->position.y) - this->radius;
        uint8_t y = static_cast<int>(transformComponent->position.x) - this->radius;

        SDL_Rect dstRect = {x, y, 2*this->radius, 2*this->radius};

        SDL_RenderCopy(sdlRenderer, circleTexture, nullptr, &dstRect);
    }
};

#endif //SDLRTS_CIRCLEOUTLINEGRAPHICSRESOURCE_H
