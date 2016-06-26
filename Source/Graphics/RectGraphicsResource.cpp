#include "Graphics/RectGraphicsResource.h"
#include "Components/TransformComponent.h"
#include <SDL.h>

//------------------------------------------------------------------------------------------
// Name: constructor
// Desc: 
//------------------------------------------------------------------------------------------
RectGraphicsResource::RectGraphicsResource(float width, float height, const Color& color) 
	: width(width), height(height), texture(nullptr)
{
	this->a = color.A();
	this->r = color.R(); 
	this->g = color.G(); 
	this->b = color.B(); 

	this->surface = SDL_CreateRGBSurface(0, static_cast<int>(width), static_cast<int>(height), 32, 0, 0, 0, 0);

	if (surface == nullptr) {
		// TODO: error
		return;
	}

	SDL_FillRect(surface, nullptr, SDL_MapRGBA(surface->format, this->r, this->g, this->b, this->a));
};
//------------------------------------------------------------------------------------------
// Name: destructor
// Desc: 
//------------------------------------------------------------------------------------------
RectGraphicsResource::~RectGraphicsResource()
{
	if (this->surface) {
		SDL_FreeSurface(this->surface);
	}
}
//------------------------------------------------------------------------------------------
// Name: Render
// Desc: 
//------------------------------------------------------------------------------------------
void RectGraphicsResource::Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent)
{
	auto scaleX = transformComponent->scale.x;
	auto scaleY = transformComponent->scale.y;

	auto dx = scaleX*this->width - this->width;
	auto dy = scaleY*this->height - this->height;

	auto  x = static_cast<uint16_t>(transformComponent->position.x - 0.5f*dx);
	auto  y = static_cast<uint16_t>(transformComponent->position.y - 0.5f*dy);
	auto  w = this->width*scaleX;
	auto  h = this->height*scaleY;

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