#ifndef TEXT_GRAPHICS_RESOURCE_H
#define TEXT_GRAPHICS_RESOURCE_H

#include "IGraphicsResource.h"
#include <string>

class TextGraphicsResource : public IGraphicsResource
{

private:

	string text; 
	string fontName; 
	_TTF_Font* font; 

	SDL_Texture* fontTexture; 
	SDL_Surface* fontSurface; 

public:

	TextGraphicsResource(string text, string fontName)
	{
		this->font = TTF_OpenFont("Resources//Anonymous_Pro.ttf", 10);
		this->fontName = fontName; 


	}
	
	// NOTE: this is a bit bad, consider a RenderText(SDL_Renderer*, TransformComponent*, string&) function?
	//   
	void SetText(string text)
	{
		this->text = text; 
	}

	string GetText(string text) const
	{
		return this->text; 
	}

	void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) override final
	{
		if (this->fontTexture == nullptr || this->fontSurface == nullptr) {
			// NOTE: don't need to do this e
			SDL_Color textColor = { 255, 255, 255 };
			this->fontSurface = TTF_RenderText_Solid(this->font, this->text.c_str(), textColor);

			if (this->fontSurface == nullptr) {
				return; 
			}

			this->fontTexture = SDL_CreateTextureFromSurface(sdlRenderer, this->fontSurface);
		}
		
		SDL_Rect textRect = { transformComponent->position.x, transformComponent->position.y, this->fontSurface->w, this->fontSurface->h };
		SDL_RenderCopy(sdlRenderer, this->fontTexture, nullptr, &textRect);
	}

	~TextGraphicsResource() override
	{
		SDL_DestroyTexture(this->fontTexture); 
		SDL_FreeSurface(this->fontSurface); 
	}
};

#endif // TEXT_GRAPHICS_RESOURCE_H