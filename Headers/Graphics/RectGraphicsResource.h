//
// Created by Julian  on 22/11/15.
//

#ifndef RECT_GRAPHICS_RESOURCE_H
#define RECT_GRAPHICS_RESOURCE_H

#include "Graphics/IGraphicsResource.h"

struct SDL_Surface; 
struct SDL_Texture; 

// RectGraphicsResource
class RectGraphicsResource : public IGraphicsResource
{
private:

    float width;
    float height;
    char a;
    char r;
    char g;
    char b;

    SDL_Surface* surface;
    SDL_Texture* texture;

public:

	RectGraphicsResource(float width, float height, char a, char r, char g, char b);

	~RectGraphicsResource();

	void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) override final;
};


#endif //RECTGRAPHICSRESOURCE_H
