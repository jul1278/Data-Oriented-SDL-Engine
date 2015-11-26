//
// Created by Julian  on 17/11/15.
//

#ifndef SDL_RTS_GRAPHICS_H
#define SDL_RTS_GRAPHICS_H

#include <iostream>
#include <vector>
#include <map>
#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#include "/Library/Frameworks/SDL2_image.framework/Headers/SDL_image.h"

#include "GraphicsResources/IGraphicsResource.h"
#include "Components/GraphicsComponent.h"
#include "Components/TransformComponent.h"
#include "Utility.h"

// Graphics
class Graphics
{
private:

    SDL_Renderer *renderer;
    SDL_Surface* sdlSurface;
    SDL_Window* window;

    int resourceId;
    int GetNextResourceId() { return resourceId++; }

    std::map<int, IGraphicsResource*> graphicsResourceMap;
    std::map<std::string, SDL_Surface*> resourceSurfaceMap;

    static SDL_Surface* LoadSurface(std::string filename, SDL_PixelFormat* format);

public:

    Graphics(int windowWidth, int windowHeight, std::string appName);
    ~Graphics();

    SDL_PixelFormat* GetPixelFormat() { return this->sdlSurface->format;}

    // Load a sprite resource and associate it with a string
    int LoadGraphicResource(std::string fileName, std::string resourceName);
    int AddGraphicsResource(IGraphicsResource* graphicsResource);

    void UpdateGraphics(std::vector<GraphicsComponent>* graphicsComponents, std::vector<TransformComponent>* transformComponents);
};


#endif //SDL_RTS_GRAPHICS_H
