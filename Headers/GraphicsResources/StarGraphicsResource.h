//
// Created by Julian  on 24/02/2016.
//

#ifndef STAR_GRAPHICS_RESOURCE_H
#define STAR_GRAPHICS_RESOURCE_H

#include <GraphicsResources\CircleOutlineGraphicsResource.h>
#include <GraphicsResources\CircleFIllGraphicsResource.h>
#include <Graphics.h>

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

	StarGraphicsResource(int id, string resourceName, float radiusOuter, float radiusInner, uint8_t a, uint8_t r, uint8_t g, uint8_t b) : IGraphicsResource(id, resourceName)
	{
		this->a = a; 
		this->r = r; 
		this->g = g;
		this->b = b; 

		this->radiusInner = static_cast<uint16_t>(floor(radiusInner));
		this->radiusOuter = static_cast<uint16_t>(floor(radiusOuter)); 

		starCircle = new CircleOutlineGraphicsResource(0, "", 0.5f*radiusOuter, 1.0f, a, r, g, b); 
		starFill = new CircleFillGraphicsResource(0, "", 0.5f*radiusInner, a, r, g, b); 
	};

	~StarGraphicsResource()
	{
		delete this->starCircle; 
		delete this->starFill; 
	}

	virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent)
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

		vy1 = transformComponent->scale.y*(transformComponent->position.y - this->radiusOuter); 
		vy2 = transformComponent->scale.y*transformComponent->position.y + this->radiusOuter;

		hx1 = transformComponent->scale.x*(transformComponent->position.x - this->radiusOuter);
		hx2 = transformComponent->scale.x*(transformComponent->position.x + this->radiusOuter);

		hy1 = transformComponent->position.y;
		hy2 = transformComponent->position.y;

		SDL_SetRenderDrawColor(sdlRenderer, this->r, this->g, this->b, this->a); 
		SDL_RenderDrawLine(sdlRenderer, vx1, vy1, vx2, vy2);
		SDL_RenderDrawLine(sdlRenderer, hx1, hy1, hx2, hy2);
	}
};


#endif // STAR_GRAPHICS_RESOURCE_H