//
// Created by Julian  on 23/11/15.
//
#ifndef GRAPHICS_UTILITY_H
#define GRAPHICS_UTILITY_H

#include <SDL.h>
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <cstring>
#include <cmath>

namespace GraphicsUtility
{
    //----------------------------------------------------------------------------------
    // Name: FillCircle
    // Desc:
    //----------------------------------------------------------------------------------
    static void OutlineCircle(SDL_Surface *surface, uint16_t radius, uint16_t thickness, uint32_t color)
    {
        if (surface == nullptr) {
            return;
        }

        if (!surface->locked) {
            SDL_LockSurface(surface);
        }

        auto pixels = static_cast<Uint8*>(surface->pixels);

        // set all the pixels to have 0x00 alpha channel
        memset(static_cast<void*>(pixels), 0x00, sizeof(Uint32)*surface->w*surface->h);

        for (auto x = 0; x < radius; x++) {

            auto yTop = sqrtf(radius*radius - x*x);

            for (auto y = 0; y < yTop; y++) {

                auto innerRadiusSqr = (radius - thickness)*(radius - thickness);

                if ((x*x + y*y ) < innerRadiusSqr ) {
                    continue;
                }

                Uint32 index = (y + radius - 1)* surface->pitch - 4*(x + radius);

                if (index >= 0) {

                    auto addr = reinterpret_cast<uint32_t*>(pixels + index);
                    *addr = color;
                }

                // TODO: why -2?
                index = (y + radius -2)* surface->pitch + 4*(x + radius);

                if (index >= 0) {

                    auto addr = reinterpret_cast<uint32_t*>(pixels + index);
                    *addr = color;
                }

                index = (-y + radius - 1)* surface->pitch + 4*(x + radius);

                if (index >= 0) {

                    auto addr = reinterpret_cast<uint32_t*>(pixels + index);
                    *addr = color;
                }

                index = (-y + radius)* surface->pitch - 4*(x + radius);

                if (index >= 0) {

                    auto addr = reinterpret_cast<uint32_t*>(pixels + index);
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
    static void FillCircle(SDL_Surface *surface, uint16_t radius, uint32_t color)
    {
        if (surface == nullptr) {
            return;
        }

        if (!surface->locked) {
            SDL_LockSurface(surface);
        }

        auto pixels = static_cast<Uint8*>(surface->pixels);

        // set all the pixels to have 0x00 alpha channel
		memset(static_cast<void*>(pixels), 0x00, sizeof(Uint32)*surface->w*surface->h);

        for (auto x = 0; x < radius; x++) {

	        auto yTop = sqrtf(radius*radius - x*x);

            for (auto y = 0; y < yTop; y++) {

                Uint32 index = (y + radius - 1)* surface->pitch - 4*(x + radius);
                if (index >= 0) {

	                auto addr = reinterpret_cast<uint32_t*>(pixels + index);
                    *addr = color;
                }

                // TODO: why -2?
                index = (y + radius -2)* surface->pitch + 4*(x + radius);
                if (index >= 0) {

	                auto addr = reinterpret_cast<uint32_t*>(pixels + index);
                    *addr = color;
                }

                index = (-y + radius - 1)* surface->pitch + 4*(x + radius);
                if (index >= 0) {

	                auto addr = reinterpret_cast<uint32_t*>(pixels + index);
                    *addr = color;
                }

                index = (-y + radius)* surface->pitch - 4*(x + radius);
                if (index >= 0) {

	                auto addr = reinterpret_cast<uint32_t*>(pixels + index);
                    *addr = color;
                }
            }
        }

        SDL_UnlockSurface(surface);
    };

    static void FillIsoTriangle(SDL_Surface* surface, int width, int height, uint32_t color)
    {
        if (surface == nullptr) {
            return;
        }

        if (!surface->locked) {
            SDL_LockSurface(surface);
        }

	    auto pixels = static_cast<Uint8*>(surface->pixels);
        
        // set all the pixels to have 0x00 alpha channel
        memset(static_cast<void*>(pixels), 0xff000000, surface->w*surface->h);
        
        uint32_t index = 0;
	    auto error = 0.0f;

        if (width/2 > height) {

	        auto x = 0;
	        auto slope = static_cast<float>(height)/(0.5f*width);

            for (auto y = 0; y < height; y++) {

                while ( error < 0.5f ) {

                    // accumulate error
	                auto dy = fabsf(static_cast<float>(y) - x*slope);
                    error += dy;

                    for (auto j = 0; j < y; j++) {

                        index = (height - j - 1)*surface->pitch + x*4;

                        // draw pixels
	                    auto addr = reinterpret_cast<uint32_t*>(pixels + index);
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

	        auto y = 0;
	        auto slope = (0.5f*width) / height;

            for ( int x = floor(0.5f*width); x < width; x++) {

                while ( error < 0.5f ) {

                    // accumulate error
	                auto dx = fabsf( static_cast<float>(x - floor(0.5f*width)) - y*slope);
                    error += dx;

                    for (int j = floor(0.5f*width); j < x; j++) {

                        index = y*surface->pitch + (x - j)*4;

                        // draw pixels
	                    auto addr = reinterpret_cast<uint32_t*>(pixels + index);
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

//const float PI = 3.1415927;



#endif //GRAPHICS_UTILITY_H

