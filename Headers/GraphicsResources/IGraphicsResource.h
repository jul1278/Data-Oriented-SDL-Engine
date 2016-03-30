//
// Created by Julian  on 22/11/15.
//

#ifndef IGRAPHICSRESOURCE_H
#define IGRAPHICSRESOURCE_H

#include <GraphicsUtility.h>
#include "Components/TransformComponent.h"
#include <SDL_ttf.h>

class IGraphicsResource
{
public:
	virtual ~IGraphicsResource()
	{
	}

    virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) = 0;
};

#endif //GRAPHICSRESOURCE_H
