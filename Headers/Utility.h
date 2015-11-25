//
// Created by Julian  on 23/11/15.
//

#ifndef SDLRTS_UTILITY_H
#define SDLRTS_UTILITY_H

#pragma once

class GraphicsUtility
{
public:

    //----------------------------------------------------------------------------------
    // Name: FillCircle
    // Desc:
    //----------------------------------------------------------------------------------
    static void OutlineCircle(SDL_Surface *surface, uint8_t radius, uint8_t thickness, uint32_t color)
    {
        if (surface == NULL) {
            return;
        }

        if (!surface->locked) {
            SDL_LockSurface(surface);
        }

        Uint8* pixels = (Uint8*) surface->pixels;

        for (int x = 0; x < radius; x++) {

            float yTop = sqrtf(radius*radius - x*x);

            for (int y = 0; y < yTop; y++) {

                int innerRadiusSqr = (radius - thickness)*(radius - thickness);

                if ((x*x + y*y ) < innerRadiusSqr ) {
                    continue;
                }

                Uint32 index = (y + radius - 1)* surface->pitch - 4*(x + radius);

                if (index >= 0) {

                    uint32_t* addr = (uint32_t*)(pixels + index);
                    *addr = color;
                }

                // TODO: why -2?
                index = (y + radius -2)* surface->pitch + 4*(x + radius);

                if (index >= 0) {

                    uint32_t* addr = (uint32_t*)(pixels + index);
                    *addr = color;
                }

                index = (-y + radius - 1)* surface->pitch + 4*(x + radius);

                if (index >= 0) {

                    uint32_t* addr = (uint32_t*)(pixels + index);
                    *addr = color;
                }

                index = (-y + radius)* surface->pitch - 4*(x + radius);

                if (index >= 0) {

                    uint32_t* addr = (uint32_t*) (pixels + index);
                    *addr = color;
                }
            }
        }

        SDL_UnlockSurface(surface);
    };
    //----------------------------------------------------------------------------------
    // Name: FillCircle
    // Desc:
    //----------------------------------------------------------------------------------
    static void FillCircle(SDL_Surface *surface, uint8_t radius, uint32_t color)
    {
        if (surface == NULL) {
            return;
        }

        if (!surface->locked) {
            SDL_LockSurface(surface);
        }

        Uint8* pixels = (Uint8*) surface->pixels;

        for (int x = 0; x < radius; x++) {

            float yTop = sqrtf(radius*radius - x*x);

            for (int y = 0; y < yTop; y++) {

                Uint32 index = (y + radius - 1)* surface->pitch - 4*(x + radius);
                if (index >= 0) {

                    uint32_t* addr = (uint32_t*)(pixels + index);
                    *addr = color;
                }

                // TODO: why -2?
                index = (y + radius -2)* surface->pitch + 4*(x + radius);
                if (index >= 0) {

                    uint32_t* addr = (uint32_t*)(pixels + index);
                    *addr = color;
                }

                index = (-y + radius - 1)* surface->pitch + 4*(x + radius);
                if (index >= 0) {

                    uint32_t* addr = (uint32_t*)(pixels + index);
                    *addr = color;
                }

                index = (-y + radius)* surface->pitch - 4*(x + radius);
                if (index >= 0) {

                    uint32_t* addr = (uint32_t*) (pixels + index);
                    *addr = color;
                }
            }
        }

        SDL_UnlockSurface(surface);
    };
};

const float PI = 3.1415927;



#endif //SDLRTS_UTILITY_H
