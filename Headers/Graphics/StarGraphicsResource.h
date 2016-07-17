//
// Created by Julian  on 24/02/2016.
//

#ifndef STAR_GRAPHICS_RESOURCE_H
#define STAR_GRAPHICS_RESOURCE_H

#include "Graphics/CircleOutlineGraphicsResource.h"
#include "Graphics/CircleFIllGraphicsResource.h"

// CircleGraphicsResource
class StarGraphicsResource : public IGraphicsResource
{
private:

	uint8_t a; 
	uint8_t r;
	uint8_t g;
	uint8_t b;

	uint8_t radiusInner;
	uint8_t radiusOuter; 

public:

	StarGraphicsResource(float radiusOuter, float radiusInner, const Color& color)
	{
		this->a = color.A();
		this->r = color.R();
		this->g = color.G();
		this->b = color.B(); 

		this->radiusInner = static_cast<uint16_t>(floor(radiusInner));
		this->radiusOuter = static_cast<uint16_t>(floor(radiusOuter));
	};

	~StarGraphicsResource()
	{
	}

	void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) override final
	{
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