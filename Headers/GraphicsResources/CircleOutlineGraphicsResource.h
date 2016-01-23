//
// Created by Julian  on 25/11/15.
//

#ifndef CIRCLEOUTLINEGRAPHICSRESOURCE_H
#define CIRCLEOUTLINEGRAPHICSRESOURCE_H

#include "GraphicsResources/IGraphicsResource.h"
#include "Graphics.h"

// CircleGraphicsResource
class CircleOutlineGraphicsResource : public IGraphicsResource
{
private:

    uint16_t radius;
    uint8_t thickness;

    SDL_Surface* circleSurface;
    SDL_Texture* circleTexture; 

public:

    CircleOutlineGraphicsResource(int id, std::string resourceName, float radius, float thickness, uint8_t a, uint8_t r, uint8_t g, uint8_t b) : IGraphicsResource(id, resourceName)
    {
        this->radius = static_cast<uint16_t>(floor(radius));

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
            this->circleTexture = SDL_CreateTextureFromSurface(sdlRenderer, this->circleSurface);
        }

        if (transformComponent == nullptr) {
            return;
        }

        if (sdlRenderer == nullptr) {
            return;
        }

        float dx = this->radius*transformComponent->scale.x - this->radius;
        float dy = this->radius*transformComponent->scale.y - this->radius;

        uint16_t x = static_cast<uint8_t >(transformComponent->position.x - 0.5f*dx);
        uint16_t y = static_cast<uint8_t>(transformComponent->position.y - 0.5f*dy);
        uint16_t w = static_cast<uint8_t>(2.0f*this->radius*transformComponent->scale.x);
        uint16_t h = static_cast<uint8_t>(2.0f*this->radius*transformComponent->scale.y);

        SDL_Rect dstRect = { x, y, w, h };

        SDL_RenderCopy(sdlRenderer, circleTexture, nullptr, &dstRect);
    }
};

#endif //CIRCLEOUTLINEGRAPHICSRESOURCE_H
