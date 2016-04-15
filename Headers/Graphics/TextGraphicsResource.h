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

	void UpdateFontSurface()
	{
		SDL_Color textColor = { 255, 255, 255 };
		this->fontSurface = TTF_RenderText_Solid(this->font, this->text.c_str(), textColor);
	}
	
public:

	TextGraphicsResource(string text, string fontName, unsigned short fontSize)
	{
		this->font = TTF_OpenFont("Resources//Anonymous_Pro.ttf", fontSize);
		this->fontName = fontName; 
		this->text = text; 

		this->UpdateFontSurface(); 
	}
	
	// NOTE: this is a bit bad, consider a RenderText(SDL_Renderer*, TransformComponent*, string&) function?
	//   
	void SetText(string text)
	{
		this->text = text;
		this->UpdateFontSurface(); 
	}

	string GetText(string text) const
	{
		return this->text; 
	}

	Vector2D GetSize()
	{
		if (this->fontSurface == nullptr) {
			return Vector2D(0.0f, 0.0f);
		}

		return Vector2D(this->fontSurface->w, this->fontSurface->h); 
	}

	void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) override final
	{
		if (this->fontSurface == nullptr) {
			this->UpdateFontSurface(); 
		}

		this->fontTexture = SDL_CreateTextureFromSurface(sdlRenderer, this->fontSurface);
		
		auto width = transformComponent->scale.x * this->fontSurface->w; 
		auto height = transformComponent->scale.y * this->fontSurface->h;
		
		auto x = transformComponent->position.x - width / 2;
		auto y = transformComponent->position.y - height / 2; 

		SDL_Rect textRect = { x, y, width, height };

		auto angleDeg = (180.0f / M_PI)*transformComponent->orientation.Angle(); 

		SDL_RenderCopyEx(sdlRenderer, this->fontTexture, nullptr, &textRect, angleDeg, nullptr, SDL_FLIP_NONE);
	}

	~TextGraphicsResource() override
	{
		SDL_DestroyTexture(this->fontTexture); 
		SDL_FreeSurface(this->fontSurface); 
	}
};

#endif // TEXT_GRAPHICS_RESOURCE_H