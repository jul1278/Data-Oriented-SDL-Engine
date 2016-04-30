//
// Created by Julian  on 12/03/16.
//

#ifndef BUBBLE_GRAPHICS_RESOURCE_H
#define BUBBLE_GRAPHICS_RESOURCE_H

#include "IGraphicsResource.h"

class CircleOutlineGraphicsResource;
class CircleFillGraphicsResource; 

class BubbleGraphicsResource : public IGraphicsResource
{
private:

	CircleOutlineGraphicsResource* bubbleCircle; 
	CircleFillGraphicsResource* bubbleHighlight; 

	unsigned int radius; 

public:

	BubbleGraphicsResource(float radius); 
	
	~BubbleGraphicsResource();

	void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) override final; 
};

#endif // BUBBLE_GRAPHICS_RESOURCE_H