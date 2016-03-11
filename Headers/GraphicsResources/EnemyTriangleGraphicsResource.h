//
// Created by Julian  on 1/03/16.
//

#ifndef ENEMY_TRIANGLE_GRAPHICS_RESOURCE_H
#define ENEMY_TRIANGLE_GRAPHICS_RESOURCE_H

#include "IGraphicsResource.h"

class EnemyTriangleGraphicsResource : public IGraphicsResource
{
private:

	float width;
	float height; 

	uint8_t a;
	uint8_t r;
	uint8_t g;
	uint8_t b;
public:

	EnemyTriangleGraphicsResource(float width, float height, uint8_t a, uint8_t r, uint8_t g, uint8_t b)
	{
		this->width = width; 
		this->height = height; 

		this->a = a;
		this->r = r; 
		this->g = g; 
		this->b = b; 
	}

	virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent)
	{
		int topX = transformComponent->position.x;
		int topY = transformComponent->position.y - 0.5f*this->height;

		int leftX = transformComponent->position.x - 0.5f*this->width; 
		int leftY = transformComponent->position.y + 0.5f*this->height;

		int rightX = transformComponent->position.x + 0.5f*this->width; 
		int rightY = transformComponent->position.y + 0.5f*this->height; 

		SDL_SetRenderDrawColor(sdlRenderer, this->r, this->g, this->b, this->a); 
		SDL_RenderDrawLine(sdlRenderer, topX, topY, rightX, rightY); 
		SDL_RenderDrawLine(sdlRenderer, rightX, rightY, leftX, leftY); 
		SDL_RenderDrawLine(sdlRenderer, leftX, leftY, topX, topY);
	}

};

#endif // ENEMY_TRIANGLE_GRAPHICS_RESOURCE_H