//
// Created by Julian  on 24/02/2016.
//

#ifndef STAR_GRAPHICS_RESOURCE_H
#define STAR_GRAPHICS_RESOURCE_H

#include "Graphics\CircleOutlineGraphicsResource.h"
#include "Graphics\CircleFIllGraphicsResource.h"

// CircleGraphicsResource
class StarGraphicsResource : public IGraphicsResource
{
private:
	

	CircleOutlineGraphicsResource* starCircle;
	CircleFillGraphicsResource* starFill; 

	uint8_t a; 
	uint8_t r;
	uint8_t g;
	uint8_t b;

	uint8_t radiusInner;
	uint8_t radiusOuter; 

public:

	StarGraphicsResource(float radiusOuter, float radiusInner, uint8_t a, uint8_t r, uint8_t g, uint8_t b)
	{
		this->a = a; 
		this->r = r; 
		this->g = g;
		this->b = b; 

		this->radiusInner = static_cast<uint16_t>(floor(radiusInner));
		this->radiusOuter = static_cast<uint16_t>(floor(radiusOuter)); 

		starCircle = new CircleOutlineGraphicsResource(0.5f*radiusOuter, 1.0f, a, r, g, b); 
		starFill = new CircleFillGraphicsResource(0.5f*radiusInner, a, r, g, b); 
	};

	~StarGraphicsResource()
	{
		delete this->starCircle; 
		delete this->starFill; 
	}

	void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) override final
	{
		if (this->starCircle != nullptr) {
			//this->starCircle->Render(sdlRenderer, transformComponent); 
		}

		if (this->starFill != nullptr) {
			//this->starFill->Render(sdlRenderer, transformComponent); 
		}

		int vx1, vx2, vy1, vy2;
		int hx1, hx2, hy1, hy2; 

		vx1 = transformComponent->position.x; 
		vx2 = transformComponent->position.x; 

		vy1 = transformComponent->position.y - transformComponent->scale.y*this->radiusOuter; 
		vy2 = transformComponent->position.y + transformComponent->scale.y*this->radiusOuter;

		hx1 = transformComponent->position.x - transformComponent->scale.x*this->radiusOuter;
		hx2 = transformComponent->position.x + transformComponent->scale.x*this->radiusOuter;

		hy1 = transformComponent->position.y;
		hy2 = transformComponent->position.y;

		SDL_SetRenderDrawColor(sdlRenderer, this->r, this->g, this->b, this->a); 
		SDL_RenderDrawLine(sdlRenderer, vx1, vy1, vx2, vy2);
		SDL_RenderDrawLine(sdlRenderer, hx1, hy1, hx2, hy2);
	}
};


#endif // STAR_GRAPHICS_RESOURCE_H