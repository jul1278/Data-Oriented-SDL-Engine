#ifndef GRID_GRAPHICS_RESOURCE_H
#define GRID_GRAPHICS_RESOURCE_H

#include "Graphics/IGraphicsResource.h"
#include "SDL.h"

class GridGraphicsResource : public IGraphicsResource
{
private:

	float interval; 
	unsigned int xCount;
	unsigned int yCount; 

	char a;
	char r;
	char g;
	char b; 

public:

	GridGraphicsResource(float interval, unsigned int xCount, unsigned int yCount, const Color& color)
		: interval(interval), xCount(xCount), yCount(yCount)
	{
		this->a = color.A();
		this->r = color.R(); 
		this->g = color.G(); 
		this->b = color.B(); 
	}

	void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) override final
	{
		// NOTE: this doesn't take into account scaling or orientation! TODO: 

		SDL_SetRenderDrawColor(sdlRenderer, this->r, this->g, this->b, this->a); 

		for (auto x = 0; x < this->xCount; x++) {
			auto xCoord = transformComponent->position.x + x*interval;
			auto y1Coord = transformComponent->position.y; 
			auto y2Coord = transformComponent->position.y + yCount*interval; 

			SDL_RenderDrawLine(sdlRenderer, xCoord, y1Coord, xCoord, y2Coord); 
		}

		for (auto y = 0; y < this->yCount; y++) {
			auto yCoord = transformComponent->position.y + y*interval; 
			auto x1Coord = transformComponent->position.x; 
			auto x2Coord = transformComponent->position.x + xCount*interval; 

			SDL_RenderDrawLine(sdlRenderer, x1Coord, yCoord, x2Coord, yCoord); 
		}
	}
};

#endif // GRID_GRAPHICS_RESOURCE_H