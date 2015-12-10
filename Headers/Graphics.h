//
// Created by Julian  on 17/11/15.
//

#ifndef SDL_RTS_GRAPHICS_H
#define SDL_RTS_GRAPHICS_H

#include <iostream>
#include <vector>
#include <map>
#include "SDL.h"


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

    // Load a sprite resource and associate it with a string
    int LoadGraphicResource(std::string fileName, std::string resourceName);
    int AddGraphicsResource(IGraphicsResource* graphicsResource);

    void UpdateGraphics(std::vector<BaseComponent*> graphicsComponents, std::vector<BaseComponent*> transformComponents);
};


#endif //SDL_RTS_GRAPHICS_H
