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
        if (surface == nullptr) {
            return;
        }

        if (!surface->locked) {
            SDL_LockSurface(surface);
        }

        Uint8* pixels = static_cast<Uint8*>(surface->pixels);

        for (int x = 0; x < radius; x++) {

            float yTop = sqrtf(radius*radius - x*x);

            for (int y = 0; y < yTop; y++) {

                int innerRadiusSqr = (radius - thickness)*(radius - thickness);

                if ((x*x + y*y ) < innerRadiusSqr ) {
                    continue;
                }

                Uint32 index = (y + radius - 1)* surface->pitch - 4*(x + radius);

                if (index >= 0) {

                    uint32_t* addr = reinterpret_cast<uint32_t*>(pixels + index);
                    *addr = color;
                }

                // TODO: why -2?
                index = (y + radius -2)* surface->pitch + 4*(x + radius);

                if (index >= 0) {

                    uint32_t* addr = reinterpret_cast<uint32_t*>(pixels + index);
                    *addr = color;
                }

                index = (-y + radius - 1)* surface->pitch + 4*(x + radius);

                if (index >= 0) {

                    uint32_t* addr = reinterpret_cast<uint32_t*>(pixels + index);
                    *addr = color;
                }

                index = (-y + radius)* surface->pitch - 4*(x + radius);

                if (index >= 0) {

                    uint32_t* addr = reinterpret_cast<uint32_t*>(pixels + index);
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
        if (surface == nullptr) {
            return;
        }

        if (!surface->locked) {
            SDL_LockSurface(surface);
        }

        Uint8* pixels = static_cast<Uint8*>(surface->pixels);

        for (int x = 0; x < radius; x++) {

            float yTop = sqrtf(radius*radius - x*x);

            for (int y = 0; y < yTop; y++) {

                Uint32 index = (y + radius - 1)* surface->pitch - 4*(x + radius);
                if (index >= 0) {

                    uint32_t* addr = reinterpret_cast<uint32_t*>(pixels + index);
                    *addr = color;
                }

                // TODO: why -2?
                index = (y + radius -2)* surface->pitch + 4*(x + radius);
                if (index >= 0) {

                    uint32_t* addr = reinterpret_cast<uint32_t*>(pixels + index);
                    *addr = color;
                }

                index = (-y + radius - 1)* surface->pitch + 4*(x + radius);
                if (index >= 0) {

                    uint32_t* addr = reinterpret_cast<uint32_t*>(pixels + index);
                    *addr = color;
                }

                index = (-y + radius)* surface->pitch - 4*(x + radius);
                if (index >= 0) {

                    uint32_t* addr = reinterpret_cast<uint32_t*>(pixels + index);
                    *addr = color;
                }
            }
        }

        SDL_UnlockSurface(surface);
    };

    static void FillIsoTriangle(SDL_Surface* surface, int width, int height, uint32_t color)
    {
        if (surface == NULL) {
            return;
        }

        if (!surface->locked) {
            SDL_LockSurface(surface);
        }

        Uint8* pixels = static_cast<Uint8*>(surface->pixels);
        uint32_t index = 0;
        float error = 0.0f;

        if (width/2 > height) {

            int x;
            float slope = (float) height/(0.5f*width);

            for ( int y = 0; y < height; y++) {

                while ( error < 0.5f ) {

                    // accumulate error
                    float dy = fabsf(static_cast<float>(y) - x*slope);
                    error += dy;

                    for (int j = 0; j < y; j++) {

                        index = (height - j - 1)*surface->pitch + x*4;

                        // draw pixels
                        uint32_t* addr = reinterpret_cast<uint32_t*>(pixels + index);
                        *(addr) = color;

                        index = (height - j - 1)*surface->pitch + (width - x)*4;

                        // draw pixels
                        addr = reinterpret_cast<uint32_t*>(pixels + index);
                        *(addr) = color;
                    }

                    // increment x;
                    x++;
                }
                error = 0.0f;
            }

        } else {

            int y = 0;
            float slope = (0.5f*width) / height;

            for ( int x = floor(0.5f*width); x < width; x++) {

                while ( error < 0.5f ) {

                    // accumulate error
                    float dx = fabsf( (float)( x - floor(0.5f*width) ) - y*slope);
                    error += dx;

                    for (int j = floor(0.5f*width); j < x; j++) {

                        index = y*surface->pitch + (x - j)*4;

                        // draw pixels
                        uint32_t* addr = (uint32_t*) (pixels + index);
                        *(addr) = color;

//                        index = y*surface->pitch - (x - j)*4;
//
//                        // draw pixels
//                        addr = (uint32_t*) (pixels + index);
//                        *(addr) = color;
                    }

                    // decrement y;
                    y++;
                }
                error = 0.0f;
            }
        }

        SDL_UnlockSurface(surface);
    }
};

const float PI = 3.1415927;



#endif //SDLRTS_UTILITY_H

