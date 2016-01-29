//
// Created by Julian  on 17/11/15.
//

#include <time.h>
#include <stdlib.h>
#include <GameApp.h>
#include <GraphicsResources/CircleFIllGraphicsResource.h>
#include <ComponentRepository.h>
#include <EntityConstructor.h>
#include <Components/SimplePhysicsComponent.h>

//------------------------------------------------------------------------------------
// Name: GameApp
// Desc:
//------------------------------------------------------------------------------------
GameApp::GameApp()
{
    this->windowHeight = 480;
    this->windowWidth = 640;
    this->appName = "Game";
	
	this->componentRepository = new ComponentRepository; 
	this->graphics = new Graphics(this->windowWidth, this->windowHeight, this->appName); 

	this->componentRepository->RegisterComponentType<TransformComponent>();
	this->componentRepository->RegisterComponentType<GraphicsComponent>(); 
	this->componentRepository->RegisterComponentType<SimplePhysicsComponent>(); 

	EntityConstructor::ConstructBasicGraphicEntity(this->componentRepository, 0, Vector2D(315.0, 235.0), 10.0f); 
	this->graphics->AddGraphicsResource(new CircleFillGraphicsResource(0, "", 10.0f, 0xff, 0x8f, 0x0, 0x8f)); 


	EntityConstructor::ConstructBasicGraphicEntity(this->componentRepository, 1, Vector2D(100.0, 235.0), 10.0f);
	this->graphics->AddGraphicsResource(new CircleFillGraphicsResource(1, "", 10.0f, 0xff, 0x8f, 0x0, 0x8f));


	EntityConstructor::ConstructBasicGraphicEntity(this->componentRepository, 2, Vector2D(200.0, 420.0), 10.0f);
	this->graphics->AddGraphicsResource(new CircleFillGraphicsResource(2, "", 10.0f, 0xff, 0x8f, 0x8f, 0x00));
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

		auto graphicsComponents = this->componentRepository->Select<GraphicsComponent>(); 
		auto transformComponents = this->componentRepository->Select<TransformComponent>(); 

		this->graphics->UpdateGraphics(&event, graphicsComponents, transformComponents);
	}

	return false; 
}
