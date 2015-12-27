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
#include "Events/IEventHandler.h"
#include "Utility.h"

// Graphics
class Graphics
{
private:

    SDL_Renderer* renderer;
    SDL_Surface* sdlSurface;
    SDL_Window* window;

    int resourceId;
    int GetNextResourceId() { return resourceId++; }

    map<int, IGraphicsResource*> graphicsResourceMap;
    map<string, SDL_Surface*> resourceSurfaceMap;

    static SDL_Surface* LoadSurface(string filename, SDL_PixelFormat* format);

public:

    Graphics(int windowWidth, int windowHeight, string appName);
    ~Graphics();

    // Load a sprite resource and associate it with a string
    int LoadGraphicResource(string fileName, string resourceName);
    int AddGraphicsResource(IGraphicsResource* graphicsResource);

    void UpdateGraphics(SDL_Event* event, map<int, IBaseComponent*> graphicsComponents, map<int, IBaseComponent*> transformComponents);
};


#endif //SDL_RTS_GRAPHICS_H
