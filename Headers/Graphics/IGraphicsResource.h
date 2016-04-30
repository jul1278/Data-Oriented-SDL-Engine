//
// Created by Julian  on 22/11/15.
//

#ifndef IGRAPHICSRESOURCE_H
#define IGRAPHICSRESOURCE_H

struct SDL_Renderer; 
struct TransformComponent;

class IGraphicsResource
{
public:

	virtual ~IGraphicsResource() {}
    virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) = 0;
};

#endif //GRAPHICSRESOURCE_H
