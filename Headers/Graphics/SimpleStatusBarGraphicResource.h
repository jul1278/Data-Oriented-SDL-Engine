//
// Created by Julian  on 22/11/15.
//

#ifndef SIMPLE_STATUS_BAR_GRAPHICS_RESOURCE_H
#define SIMPLE_STATUS_BAR_GRAPHICS_RESOURCE_H

#include "Graphics/IGraphicsResource.h"
#include "SDL.h"

struct SDL_Surface;
struct SDL_Texture;

// SimpleStatusBarGraphicResource
class SimpleStatusBarGraphicResource : public IGraphicsResource
{
private:

	float width;
	float height;

	unsigned char a;
	unsigned char r;
	unsigned char g;
	unsigned char b;

	SDL_Surface* surface;
	SDL_Texture* texture;

public:

	SimpleStatusBarGraphicResource(float width, float height, const Color& color)
	{

	}

	~SimpleStatusBarGraphicResource()
	{

	}

	void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) override final
	{
		auto scaleX = transformComponent->scale.x;
		auto scaleY = transformComponent->scale.y;

		auto dx = scaleX*this->width - this->width;
		auto dy = scaleY*this->height - this->height;

		auto  x = static_cast<uint16_t>(transformComponent->position.x - 0.5f*dx);
		auto  y = static_cast<uint16_t>(transformComponent->position.y - 0.5f*dy);
		auto  w = static_cast<uint16_t>(this->width*scaleX);
		auto  h = static_cast<uint16_t>(this->height*scaleY);

		SDL_Rect rect = { x, y, w, h };

		if (this->texture == nullptr) {
			this->texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
		}

		if (texture == nullptr) {
			// TODO: error
			return;
		}

		SDL_RenderCopyEx(sdlRenderer, texture, nullptr, &rect, 0.25f*M_PI/*(180.0f/PI)*transformComponent->orientation.Angle()*/, nullptr, SDL_FLIP_NONE);
	}
};


#endif //RECTGRAPHICSRESOURCE_H