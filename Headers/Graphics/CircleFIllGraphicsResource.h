//
// Created by Julian  on 22/11/15.
//

#ifndef CIRCLE_GRAPHICS_RESOURCE_H
#define CIRCLE_GRAPHICS_RESOURCE_H

#include "Graphics/IGraphicsResource.h"
#include "GraphicsUtility.h"

// CircleGraphicsResource
class CircleFillGraphicsResource : public IGraphicsResource
{
private:

    SDL_Texture* circleTexture; 
    SDL_Surface* circleSurface;
    uint16_t radius;

public:

    CircleFillGraphicsResource(float radius, uint8_t a, uint8_t r, uint8_t g, uint8_t b)
    {
        this->radius = static_cast<uint16_t>(floor(radius));
        this->circleTexture = nullptr; 

        circleSurface = SDL_CreateRGBSurface(0, 2 * this->radius, 2 * this->radius, 32, 0, 0, 0, 0);
        auto color = SDL_MapRGBA(this->circleSurface->format, r, g, b, a);
        GraphicsUtility::FillCircle(circleSurface, this->radius, color);
    }

    ~CircleFillGraphicsResource()
    {
        if (this->circleSurface) {
            SDL_FreeSurface(this->circleSurface);
        }
    }

	void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) override final
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

        auto dx = this->radius*transformComponent->scale.x; 
        auto dy = this->radius*transformComponent->scale.y; 

        auto x = static_cast<uint16_t>(transformComponent->position.x - dx);
        auto y = static_cast<uint16_t>(transformComponent->position.y - dy);
        auto w = static_cast<uint16_t>(2.0f*this->radius*transformComponent->scale.x);
        auto h = static_cast<uint16_t>(2.0f*this->radius*transformComponent->scale.y);

        SDL_Rect dstRect = {x, y, w, h};

        SDL_RenderCopy(sdlRenderer, circleTexture, nullptr, &dstRect);
    }
};

#endif //CIRCLE_GRAPHICS_RESOURCE_H
