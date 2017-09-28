//
// Created by Julian  on 23/11/15.
//
#ifndef GRAPHICS_UTILITY_H
#define GRAPHICS_UTILITY_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <string.h>
#include <cstdint>
#include <math.h>

namespace GraphicsUtility
{
    //----------------------------------------------------------------------------------
    // Name: FillCircle
    // Desc:
    //----------------------------------------------------------------------------------
    static void OutlineCircle(SDL_Surface* surface, const uint16_t radius, const uint16_t thickness, const uint32_t color)
    {
        if (surface == nullptr) {
            return;
        }

		// should report error or something?
		if (thickness > radius) {
			return; 
		}

        if (!surface->locked) {
            SDL_LockSurface(surface);
        }

        auto pixels = static_cast<uint8_t*>(surface->pixels);

        // set all the pixels to have 0x00 alpha channel
        memset((void*)pixels, 0x00, sizeof(uint32_t)*surface->w*surface->h);
			
		uint32_t diff = radius - thickness; 
		uint32_t diffSqr = diff * diff; 

        for (auto x = 0U; x < radius; x++) {

			auto arg = radius*radius - x*x; 
            auto yTop = sqrtf(arg);

            for (auto y = 0U; y < yTop; y++) {

				auto innerRadiusSqr = diffSqr; //(radius - thickness)*(radius - thickness);

                if ((x*x + y*y) < innerRadiusSqr ) {
                    continue;
                }

                uint32_t index = (y + radius - 1)* surface->pitch - 4*(x + radius);

                auto addr = (uint32_t*)(pixels + index);
                *addr = color;

                // TODO: why -2?
                index = (y + radius -2)* surface->pitch + 4*(x + radius);

                addr = (uint32_t*)(pixels + index);
                *addr = color;
                index = ((-1 * y) + radius - 1) * surface->pitch + 4*(x + radius);

                addr = (uint32_t*)(pixels + index);
                *addr = color;
                index = ((-1 * y) + radius)* surface->pitch - 4*(x + radius);

                addr = (uint32_t*)(pixels + index);
                *addr = color;        
            }
        }

        SDL_UnlockSurface(surface);
    };
    //----------------------------------------------------------------------------------
    // Name: FillCircle
    // Desc:
    //----------------------------------------------------------------------------------
    static void FillCircle(SDL_Surface *surface, const uint16_t radius, const uint32_t color)
    {
        if (surface == nullptr) {
            return;
        }

        if (!surface->locked) {
            SDL_LockSurface(surface);
        }

        auto pixels = static_cast<uint8_t*>(surface->pixels);

        // set all the pixels to have 0x00 alpha channel
		memset(static_cast<void*>(pixels), 0x00, sizeof(uint32_t)*surface->w*surface->h);

        for (auto x = 0U; x < radius; x++) {

			auto arg = radius*radius - x*x;

			if (arg < 0) {
				// error
				break; 
			}

	        auto yTop = sqrtf(arg);

            for (auto y = 0U; y < yTop; y++) {

                uint32_t index = (y + radius - 1)* surface->pitch - 4*(x + radius);

                auto addr = (uint32_t*)(pixels + index);
                *addr = color;

                // TODO: why -2?
                index = (y + radius -2)* surface->pitch + 4*(x + radius);
                addr = (uint32_t*)(pixels + index);
                *addr = color;

                index = ((-1 * y) + radius - 1)* surface->pitch + 4*(x + radius);    
                addr = (uint32_t*)(pixels + index);
                *addr = color;
            
                index = ((-1 * y) + radius)* surface->pitch - 4*(x + radius);
                addr = (uint32_t*)(pixels + index);
                *addr = color;
            }
        }

        SDL_UnlockSurface(surface);
    };

	//----------------------------------------------------------------------------------
	// Name: FillIsoTriangle
	// Desc:
	//----------------------------------------------------------------------------------
    static void FillIsoTriangle(SDL_Surface* surface, uint32_t width, uint32_t height, uint32_t color)
    {
        if (surface == nullptr) {
            return;
        }

        if (!surface->locked) {
            SDL_LockSurface(surface);
        }

	    auto pixels = static_cast<uint8_t*>(surface->pixels);
        
        // set all the pixels to have 0x00 alpha channel
        memset(static_cast<void*>(pixels), 0xff000000, surface->w*surface->h);
        
        uint32_t index = 0;
	    auto error = 0.0f;

        if (width/2 > height) {

	        auto x = 0;
	        auto slope = static_cast<float>(height)/(0.5f*width);

            for (auto y = 0U; y < height; y++) {

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

	        auto y = 0U;
	        auto slope = (0.5f*width) / height;

            for (uint32_t x = floor(0.5f*width); x < width; x++) {

                while ( error < 0.5f ) { // TODO: should there be another condition here to exit the loop? what if we run out of pixels before reaching error == 0.5?

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

#endif // GRAPHICS_UTILITY_H

