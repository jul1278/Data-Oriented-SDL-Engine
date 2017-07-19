#ifndef TEXT_GRAPHICS_RESOURCE_H
#define TEXT_GRAPHICS_RESOURCE_H

#include "SDL_ttf.h"
#include "Graphics/IGraphicsResource.h"
#include "Components/TransformComponent.h"
#include "Utility/ProcessUtility.h"

//------------------------------------------------------------------------------------------
// Name: TextGraphicsResource
// Desc: 
//------------------------------------------------------------------------------------------
class TextGraphicsResource : public IGraphicsResource
{

private:

	unsigned char a; 
	unsigned char r;
	unsigned char g;
	unsigned char b; 

	string text; 
	string fontName; 
	_TTF_Font* font; 

	SDL_Texture* fontTexture; 
	SDL_Surface* fontSurface; 

	//------------------------------------------------------------------------------------------
	// Name: UpdateFontSurface
	// Desc: 
	//------------------------------------------------------------------------------------------
	void UpdateFontSurface()
	{
		SDL_Color textColor = { this->r, this->g, this->b};

		if (this->font != nullptr) {
            this->fontSurface = TTF_RenderText_Solid(this->font, this->text.c_str(), textColor);
        }
	}
	
public:

	TextGraphicsResource(string text, unsigned short fontSize, const Color& color, string fontPath = "")
	{
		this->a = color.A();
		this->r = color.R(); 
		this->g = color.G();
		this->b = color.B(); 

		if (fontPath.empty()) {
            //auto currentDir = ProcessUtility::CurrentApplicationDirectory();
			//auto fileExists = FileUtility::FileExists("..\\Resources\\Anonymous_Pro.ttf"); 

			this->font = TTF_OpenFont("..\\Resources\\Anonymous_Pro.ttf", fontSize);
		} else {

			auto font = fontPath;//"Resources//" + fontName + ".ttf";
			this->font = TTF_OpenFont(font.c_str(), fontSize);
		}

		
		this->fontName = fontPath;
		this->text = text; 

		this->UpdateFontSurface(); 
	}

	//------------------------------------------------------------------------------------------
	// Name: SetText
	// Desc: 
	//------------------------------------------------------------------------------------------
	// NOTE: this is a bit bad, consider a RenderText(SDL_Renderer*, TransformComponent*, string&) function?
	//   
	void SetText(string text)
	{
		this->text = text;
		this->UpdateFontSurface(); 
	}

	//------------------------------------------------------------------------------------------
	// Name: GetText
	// Desc: 
	//------------------------------------------------------------------------------------------
	string GetText(string text) const
	{
		return this->text; 
	}

	//------------------------------------------------------------------------------------------
	// Name: GetSize
	// Desc: 
	//------------------------------------------------------------------------------------------
	Vector2D GetSize()
	{
		if (this->fontSurface == nullptr) {
			return Vector2D(0.0f, 0.0f);
		}

		return Vector2D(this->fontSurface->w, this->fontSurface->h); 
	}

	//------------------------------------------------------------------------------------------
	// Name: Render
	// Desc: 
	//------------------------------------------------------------------------------------------
	void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) override final
	{
		if (this->fontSurface == nullptr) {
			this->UpdateFontSurface(); 
		}

		this->fontTexture = SDL_CreateTextureFromSurface(sdlRenderer, this->fontSurface);

        if (this->fontTexture == nullptr) {
            return;
        }

		auto width = static_cast<uint16_t>(transformComponent->scale.x * this->fontSurface->w); 
		auto height = static_cast<uint16_t>(transformComponent->scale.y * this->fontSurface->h);
		
		auto x = static_cast<uint16_t>(transformComponent->position.x - width / 2);
		auto y = static_cast<uint16_t>(transformComponent->position.y - height / 2); 

		SDL_Rect textRect = { x, y, width, height };

		auto angleDeg = (180.0f / M_PI)*transformComponent->orientation.Angle(); 

		SDL_RenderCopyEx(sdlRenderer, this->fontTexture, nullptr, &textRect, angleDeg, nullptr, SDL_FLIP_NONE);
	}

	//------------------------------------------------------------------------------------------
	// Name: ~TextGraphicsResource
	// Desc: 
	//------------------------------------------------------------------------------------------
	~TextGraphicsResource() override
	{
		SDL_DestroyTexture(this->fontTexture); 
		SDL_FreeSurface(this->fontSurface); 
	}
};

#endif // TEXT_GRAPHICS_RESOURCE_H