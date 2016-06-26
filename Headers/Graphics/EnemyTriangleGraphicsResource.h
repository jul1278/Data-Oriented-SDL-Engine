//
// Created by Julian  on 1/03/16.
//

#ifndef ENEMY_TRIANGLE_GRAPHICS_RESOURCE_H
#define ENEMY_TRIANGLE_GRAPHICS_RESOURCE_H

#include "IGraphicsResource.h"
#include "SDL.h"

class EnemyTriangleGraphicsResource : public IGraphicsResource
{
private:

	float width;
	float height; 

	unsigned char a;
	unsigned char r;
	unsigned char g;
	unsigned char b;
public:

	EnemyTriangleGraphicsResource(float width, float height, const Color& color) :
		width(width), height(height), a(color.A()), r(color.R()), g(color.G()), b(color.B())
	{}

	void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) override final
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