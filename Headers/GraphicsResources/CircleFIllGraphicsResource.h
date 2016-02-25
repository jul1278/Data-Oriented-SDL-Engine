//
// Created by Julian  on 22/11/15.
//

#ifndef CIRCLEGRAPHICSRESOURCE_H
#define CIRCLEGRAPHICSRESOURCE_H

#include "GraphicsResources/IGraphicsResource.h"
#include "Graphics.h"
#include "Utility.h"

// CircleGraphicsResource
class CircleFillGraphicsResource : public IGraphicsResource
{
private:

    SDL_Texture* circleTexture; 
    SDL_Surface* circleSurface;
    uint16_t radius;

public:

    CircleFillGraphicsResource(int id, std::string resourceName, float radius, uint8_t a, uint8_t r, uint8_t g, uint8_t b) : IGraphicsResource(id, resourceName)
    {
        this->radius = static_cast<uint16_t>(floor(radius));
        this->circleTexture = nullptr; 

        circleSurface = SDL_CreateRGBSurface(0, 2 * this->radius, 2 * this->radius, 32, 0, 0, 0, 0);
        uint32_t color = SDL_MapRGBA(this->circleSurface->format, r, g, b, a);
        GraphicsUtility::FillCircle(circleSurface, this->radius, color);
    }

    ~CircleFillGraphicsResource()
    {
        if (this->circleSurface) {
            SDL_FreeSurface(this->circleSurface);
        }
    }

    virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent)
    {
        if (this->circleTexture == nullptr) {
            this->circleTexture = SDL_CreateTextureFromSurface(sdlRenderer, this->circleSurface);
        }

        if (transformComponent == nullptr) {
            return;
        }

        if (sdlRenderer == nullptr) {
            return; 
        }

        float dx = this->radius*transformComponent->scale.x; 
        float dy = this->radius*transformComponent->scale.y; 

        uint16_t x = static_cast<uint16_t>(transformComponent->position.x - dx);
        uint16_t y = static_cast<uint16_t>(transformComponent->position.y - dy);
        uint16_t w = static_cast<uint16_t>(2.0f*this->radius*transformComponent->scale.x);
        uint16_t h = static_cast<uint16_t>(2.0f*this->radius*transformComponent->scale.y);

        SDL_Rect dstRect = {x, y, w, h};

        SDL_RenderCopy(sdlRenderer, circleTexture, nullptr, &dstRect);
    }
};

#endif //CIRCLEGRAPHICSRESOURCE_H
