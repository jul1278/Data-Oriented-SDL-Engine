//
// Created by Julian  on 17/11/15.
//

#include "Graphics.h"
#include "GraphicsResources/SpriteGraphicsResource.h"
#include "SDL_image.h"
#include <algorithm>

//------------------------------------------------------------------------------------
// Name: LoadSurface
// Desc:
//------------------------------------------------------------------------------------
Graphics::Graphics(int windowWidth, int windowHeight, std::string appName)
{
	this->resourceId = 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return;
    }

    // Create window
    this->window = SDL_CreateWindow(appName.c_str(), 100, 100, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

    if ( this->window == nullptr) {
        SDL_Quit();
        return;
    }

    // Create renderer
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (this->renderer == nullptr) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    Uint32 rmask, gmask, bmask, amask;

    // SDL interprets each pixel as a 32-bit number, so our masks must depend
    //  on the endianness (byte order) of the machine 
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif


    // Create surface
    this->sdlSurface = SDL_CreateRGBSurface(0, 20, 20, 32, rmask, gmask, bmask, amask);

    if (sdlSurface == nullptr) {

        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();

        return;
    }

    // Create texture
    SDL_Texture* sdlTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 20, 20);

    if (sdlTexture == nullptr) {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();

        return;
    }

    // init sdl image
    int imgFlags = IMG_INIT_PNG;
    if ( !(IMG_Init(imgFlags) & imgFlags) ) {
		std::cout << IMG_GetError() << std::endl; 
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();

        return;
    }  
}
//------------------------------------------------------------------------------------
// Name: LoadSurface
// Desc:
//------------------------------------------------------------------------------------
Graphics::~Graphics()
{
    // Free the surfaces
    for (std::pair<std::string, SDL_Surface*> resourceSurfaceMapElement : this->resourceSurfaceMap ) {
        SDL_FreeSurface(resourceSurfaceMapElement.second);
    }

    for (std::pair<int, IGraphicsResource*> graphicsResourcePair : this->graphicsResourceMap) {
        delete graphicsResourcePair.second; 
    }

    SDL_DestroyWindow(this->window);
    SDL_FreeSurface(this->sdlSurface);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
}
//------------------------------------------------------------------------------------
// Name: LoadSurface
// Desc:
//------------------------------------------------------------------------------------
SDL_Surface* Graphics::LoadSurface(std::string filename, SDL_PixelFormat* format)
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(filename.c_str());
    if( loadedSurface == NULL )
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", filename.c_str(), IMG_GetError());
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, format, NULL);
        if( optimizedSurface == NULL )
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", filename.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    return optimizedSurface;
}
//------------------------------------------------------------------------------------
// Name: LoadGraphicResource
// Desc:
//------------------------------------------------------------------------------------
int Graphics::LoadGraphicResource(std::string fileName, std::string resourceName)
{
    SDL_Surface* surface = this->LoadSurface(fileName, this->sdlSurface->format);

    if (surface != nullptr) {

        int id = GetNextResourceId();

        IGraphicsResource* spriteGraphicsResource = new SpriteGraphicsResource(id, resourceName, surface);
        this->graphicsResourceMap.insert(std::pair<int, IGraphicsResource*>(id, spriteGraphicsResource));
        return id;

    } else {

        return -1;
    }
}
//------------------------------------------------------------------------------------
// Name: AddGraphicsResource
// Desc:
//------------------------------------------------------------------------------------
int Graphics::AddGraphicsResource(IGraphicsResource* graphicsResource)
{
    int resourceId = this->GetNextResourceId();
    this->graphicsResourceMap.insert(std::pair<int, IGraphicsResource*>(resourceId, graphicsResource));
    return resourceId;
}
//------------------------------------------------------------------------------------
// Name: UpdateGraphics
// Desc:
//------------------------------------------------------------------------------------
void Graphics::UpdateGraphics(SDL_Event* event, map<int, IBaseComponent*> graphicsComponents, map<int, IBaseComponent*> transformComponents)
{
	SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0xff); 
    SDL_RenderClear(this->renderer);

    for (auto component : graphicsComponents) {

		GraphicsComponent* graphicsComponent = static_cast<GraphicsComponent*>(component.second); 

		int transformId = static_cast<GraphicsComponent*>(graphicsComponent)->transformId; 
        TransformComponent* transformComponent =  static_cast<TransformComponent*>(transformComponents[transformId]);

        IGraphicsResource* graphicsResource;
		int graphicsResourceId = static_cast<GraphicsComponent*>(graphicsComponent)->resourceId;

        graphicsResource = this->graphicsResourceMap[graphicsResourceId];
        graphicsResource->Render(this->renderer, transformComponent);
    }

	// Mouse debug stuff
	if (event->type == SDL_MOUSEMOTION) {

		SDL_Rect lastRect = {event->motion.x - 8, event->motion.y - 8, 16, 16};
		SDL_Rect currRect = { event->motion.x + event->motion.xrel - 8, event->motion.y + event->motion.yrel - 8, 16, 16 }; 
		SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0xff, 0xff); 
		SDL_RenderDrawRect(this->renderer, &lastRect); 
		SDL_RenderDrawRect(this->renderer, &currRect); 

		SDL_SetRenderDrawColor(this->renderer, 0x00, 0xff, 0x00, 0xff); 
		SDL_RenderDrawLine(this->renderer, lastRect.x + 8, lastRect.y + 8, currRect.x + 8, currRect.y + 8); 
	}

    SDL_RenderPresent(this->renderer);
}
