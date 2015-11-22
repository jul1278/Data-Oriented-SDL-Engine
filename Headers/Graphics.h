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
#include "IGraphicsResource.h"
#include "GraphicsComponent.h"
#include "TransformComponent.h"


// Graphics
class Graphics
{
private:

    SDL_Renderer *renderer;
    SDL_Surface* sdlSurface;
    SDL_Window* window;

    SDL_Surface* LoadSurface(std::string filename, SDL_PixelFormat* format);

    std::map<int, IGraphicsResource*> graphicsResourceMap;

public:

    Graphics(int windowWidth, int windowHeight, std::string appName);
    ~Graphics();

    void AddGraphicsResource(int resourceId, IGraphicsResource* graphicsResource);
    void UpdateGraphics(std::vector<GraphicsComponent> graphicsComponents, std::vector<TransformComponent> transformComponents);
};


#endif //SDL_RTS_GRAPHICS_H
