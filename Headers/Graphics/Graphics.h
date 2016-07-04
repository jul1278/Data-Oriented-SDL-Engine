//
// Created by Julian  on 17/11/15.
//
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Graphics/GraphicsUtility.h"
#include <vector>
#include <unordered_map>

const int NO_RENDER = 0; 

class Camera;
class IGraphicsResource; 
struct BaseComponent; 
struct TransformComponent; 
struct GraphicsComponent; 

// TODO: remove, use TextGraphicsResource for console
const int maxConsoleMessages = 10; 

using namespace std; 

// Graphics
class Graphics
{
private:

    SDL_Renderer* renderer;
    SDL_Surface* sdlSurface;
    SDL_Window* window;

	TTF_Font* consoleFont; 

    int resourceId;

	list<Camera*> cameras;

	int GetNextResourceId() { return ++resourceId; }

    unordered_map<int, IGraphicsResource*> graphicsResourceMap;
    unordered_map<string, SDL_Surface*> resourceSurfaceMap;

	list<string> consoleMessages; 

    static SDL_Surface* LoadSurface(string filename, SDL_PixelFormat* format);

public:

    Graphics(int windowWidth, int windowHeight, string appName);
    ~Graphics();

    // Load a sprite resource and associate it with a string
    int LoadGraphicResource(string fileName, string resourceName);
    int AddGraphicsResource(IGraphicsResource* graphicsResource);

	void Clear() const;
	void Present();

	void PrintConsoleText(const string& message); 

	void AddCamera(Camera* camera); 
	void RenderCameras();

	void UpdateGraphics(vector<GraphicsComponent>* graphicsComponents, vector<TransformComponent>* transformComponents);
	void UpdateGraphics(vector<GraphicsComponent>* graphicsComponents, vector<TransformComponent>* transformComponents, TransformComponent* parent); 
	
	int WindowHeight() const;
	int WindowWidth() const;
};


#endif //GRAPHICS_H
