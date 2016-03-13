//
// Created by Julian  on 12/03/16.
//

#ifndef BUBBLE_GRAPHICS_RESOURCE_H
#define BUBBLE_GRAPHICS_RESOURCE_H

#include "IGraphicsResource.h"
#include "CircleOutlineGraphicsResource.h"
#include "CircleFIllGraphicsResource.h"

class BubbleGraphicsResource : public IGraphicsResource
{
private:

	CircleOutlineGraphicsResource* bubbleCircle; 
	CircleFillGraphicsResource* bubbleHighlight; 

	unsigned int radius; 

public:

	BubbleGraphicsResource(float radius)
	{
		this->radius = radius; 

		bubbleCircle = new CircleOutlineGraphicsResource(radius, 1.0f, 0xff, 0xff, 0xff, 0xff); 
		bubbleHighlight = new CircleFillGraphicsResource(radius / 5.0f, 0xff, 0x8f, 0x8f, 0x8f);
	}

	~BubbleGraphicsResource()
	{
		delete this->bubbleCircle; 
		delete this->bubbleHighlight; 
	}

	virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) final
	{
		bubbleCircle->Render(sdlRenderer, transformComponent);

		TransformComponent highlightTransformComponent = *transformComponent; 

		highlightTransformComponent.position.x += 0.4f*this->radius; 
		highlightTransformComponent.position.y -= 0.4f*this->radius; 

		bubbleHighlight->Render(sdlRenderer, &highlightTransformComponent);
	}
};

#endif // BUBBLE_GRAPHICS_RESOURCE_H