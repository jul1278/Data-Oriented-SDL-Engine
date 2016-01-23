//
// Created by Julian  on 17/11/15.
//

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "SDL.h"
#include "GraphicsResources/IGraphicsResource.h"
#include "Components/GraphicsComponent.h"
#include "Components/TransformComponent.h"
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

    unordered_map<int, IGraphicsResource*> graphicsResourceMap;
    unordered_map<string, SDL_Surface*> resourceSurfaceMap;

    static SDL_Surface* LoadSurface(string filename, SDL_PixelFormat* format);

public:

    Graphics(int windowWidth, int windowHeight, string appName);
    ~Graphics();

    // Load a sprite resource and associate it with a string
    int LoadGraphicResource(string fileName, string resourceName);
    int AddGraphicsResource(IGraphicsResource* graphicsResource);

    void UpdateGraphics(SDL_Event* event, vector<BaseComponent*>* graphicsComponents, vector<BaseComponent*>* transformComponents);
};


#endif //GRAPHICS_H
