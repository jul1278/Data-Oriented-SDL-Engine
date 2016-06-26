//
// Created by Julian  on 22/11/15.
//

#ifndef IGRAPHICSRESOURCE_H
#define IGRAPHICSRESOURCE_H

#include "Components/TransformComponent.h"
#include "Graphics/Color.h"

struct SDL_Renderer; 

class IGraphicsResource
{
public:

	virtual ~IGraphicsResource() {}

	virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent, TransformComponent* parentTransform)
	{
		auto resultTransform = *transformComponent; 
		resultTransform.position += parentTransform->position; 

		// TODO: transform scale and orientation as well
		this->Render(sdlRenderer, &resultTransform); 
	}

    virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) = 0;
};

#endif //GRAPHICSRESOURCE_H
