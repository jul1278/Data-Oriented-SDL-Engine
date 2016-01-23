//
// Created by Julian  on 17/11/15.
//

#include <time.h>
#include <stdlib.h>
#include <GameApp.h>
#include <GraphicsResources/CircleFIllGraphicsResource.h>

//------------------------------------------------------------------------------------
// Name: GameApp
// Desc:
//------------------------------------------------------------------------------------
GameApp::GameApp()
{
    this->windowHeight = 480;
    this->windowWidth = 640;
    this->appName = "Game";

    this->graphics = new Graphics(this->windowWidth, this->windowHeight, this->appName);
	this->componentRepository = new ComponentRepository; 

	auto transformId = this->componentRepository->InsertComponent(TRANSFORM_COMPONENT, new TransformComponent(Vector2D(315.0, 235.0)));
	auto transformComponent = this->componentRepository->Select<TransformComponent*>(transformId);
	this->componentRepository->InsertComponent(GRAPHICS_COMPONENT, new GraphicsComponent(0, transformComponent)); 	
	this->graphics->AddGraphicsResource(new CircleFillGraphicsResource(0, "", 10.0f, 0xff, 0x8f, 0x0, 0x8f)); 
}
//------------------------------------------------------------------------------------
// Name: ~GameApp
// Desc:
//------------------------------------------------------------------------------------
GameApp::~GameApp()
{
}
//------------------------------------------------------------------------------------
// Name: Run
// Desc:
//------------------------------------------------------------------------------------
bool GameApp::Run()
{

	while (1)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT) {
			break;
		}

		auto graphicsComponents = this->componentRepository->Select(GRAPHICS_COMPONENT); 
		auto transformComponents = this->componentRepository->Select(GRAPHICS_COMPONENT); 

		this->graphics->UpdateGraphics(&event, graphicsComponents, transformComponents);
	}

	return false; 
}
