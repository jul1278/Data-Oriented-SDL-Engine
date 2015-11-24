//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_CIRCLEGRAPHICSRESOURCE_H
#define SDLRTS_CIRCLEGRAPHICSRESOURCE_H

#include "GraphicsResources/IGraphicsResource.h"
#include "Graphics.h"

// CircleGraphicsResource
class CircleGraphicsResource : public IGraphicsResource
{
private:

    uint8_t radius;
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;

    SDL_Surface* circleSurface;

public:

    CircleGraphicsResource(int id, std::string resourceName, float radius, uint8_t a, uint8_t r, uint8_t g, uint8_t b) : IGraphicsResource(id, resourceName)
    {
        this->radius = (uint8_t) floor(radius);
        this->a = a;
        this->r = r;
        this->g = g;
        this->b = b;

        circleSurface = SDL_CreateRGBSurface(0, 2*this->radius, 2*this->radius, 32, 0, 0, 0, 0);

        Uint8* pixels = (Uint8*) circleSurface->pixels;
        SDL_LockSurface(circleSurface);

        for (int x = 0; x < this->radius; x++) {

            float yTop = sqrtf(this->radius*this->radius - x*x);

            for (int y = 0; y < yTop; y++) {

                Uint32 index = (y + this->radius - 1)*circleSurface->pitch - 4*(x + this->radius);

                if (index >= 0) {

                    uint32_t* addr = (uint32_t*)(pixels + index);
                    *addr = SDL_MapRGBA(circleSurface->format, this->r, this->g, this->b, this->a);
                }


                index = (y + this->radius -2)*circleSurface->pitch + 4*(x + this->radius);

                if (index >= 0) {

                    uint32_t* addr = (uint32_t*)(pixels + index);
                    *addr = SDL_MapRGBA(circleSurface->format, this->r, this->g, this->b, this->a);
                }

                index = (-y + this->radius - 1)*circleSurface->pitch + 4*(x + this->radius);

                if (index >= 0) {

                    uint32_t* addr = (uint32_t*)(pixels + index);
                    *addr = SDL_MapRGBA(circleSurface->format, this->r, this->g, this->b, this->a);
                }

                index = (-y + this->radius)*circleSurface->pitch - 4*(x + this->radius);

                if (index >= 0) {

                    uint32_t* addr = (uint32_t*) (pixels + index);
                    *addr = SDL_MapRGBA(circleSurface->format, this->r, this->g, this->b, this->a);
                }


            }
        }

        SDL_UnlockSurface(circleSurface);

    };

    ~CircleGraphicsResource()
    {
        if (this->circleSurface) {
            SDL_FreeSurface(this->circleSurface);
        }
    }

    virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent)
    {
        if (this->circleSurface == NULL) {
            // TODO: how do error/warnings? be nice to be able to print them somewhere, std::cout though lol
            return;
        }

        if (transformComponent == NULL) {
            return;
        }

        if (sdlRenderer == NULL) {
            return; 
        }

        SDL_Texture* circleTexture = SDL_CreateTextureFromSurface(sdlRenderer, this->circleSurface);

        SDL_Rect dstRect = {(int)transformComponent->position.x - this->radius,
                            (int)transformComponent->position.y - this->radius,
                            2*this->radius,
                            2*this->radius};

        SDL_RenderCopy(sdlRenderer, circleTexture, NULL, &dstRect);
    }
};

#endif //SDLRTS_CIRCLEGRAPHICSRESOURCE_H
