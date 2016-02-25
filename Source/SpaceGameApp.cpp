//
// Created by Julian  on 17/11/15.
//

#include <time.h>
#include <stdlib.h>
#include <memory>
#include <SpaceGame\SpaceGameApp.h>
#include <typeinfo>
#include <typeindex>
#include <GraphicsResources\CircleFIllGraphicsResource.h>
#include <GraphicsResources\RectGraphicsResource.h>
#include <GraphicsResources\TriangleGraphicsResource.h>
#include <GraphicsResources\StarGraphicsResource.h>
#include <ComponentCollectionRepository.h>
#include <Components\SimplePhysicsComponent.h>
#include <Events\ButtonEventArgs.h>
#include <PlayerActions.h>
#include <SpaceGame\SpaceGameEntityConstructor.h>

//------------------------------------------------------------------------------------
// Name: SpaceGameApp
// Desc:
//------------------------------------------------------------------------------------
SpaceGameApp::SpaceGameApp()
{
	this->windowHeight = 480;
	this->windowWidth = 640;
	this->appName = "Space Game";

	this->componentCollectionRepository = new ComponentCollectionRepository; 
	this->graphics = new Graphics(this->windowWidth, this->windowHeight, this->appName);

	this->sdlEventCollector = new SDLEventCollector();

	auto spaceShipGraphicResId = this->graphics->LoadGraphicResource("Resources//space_ship.png", "spaceShip");
	this->graphics->AddGraphicsResource(new RectGraphicsResource(1, "", 2.0f, 12.0f, 0xff, 0xff, 0x00, 0x00));
	auto skullGraphicResId = this->graphics->LoadGraphicResource("Resources//skull_1.png", "skull1");

	auto starGraphicResId = this->graphics->AddGraphicsResource(new StarGraphicsResource(3, "", 10.0f, 5.0f, 0xff, 0xff, 0xff, 0xff)); 

	SpaceGameEntityConstructor::ConstructBackgroundStars(this->componentCollectionRepository, starGraphicResId, this->windowWidth, this->windowHeight, 10); 
}
//------------------------------------------------------------------------------------
// Name: ~SpaceGameApp
// Desc:
//------------------------------------------------------------------------------------
SpaceGameApp::~SpaceGameApp()
{
	// delet
}
//------------------------------------------------------------------------------------
// Name: SpaceGameApp
// Desc:
//------------------------------------------------------------------------------------
bool SpaceGameApp::Run()
{
	while (1)
	{
		auto transformComponents = this->componentCollectionRepository->SelectFromCollection<TransformComponent>("ScrollingBackgroundStars");
		auto graphicsComponents = this->componentCollectionRepository->SelectFromCollection<GraphicsComponent>("ScrollingBackgroundStars");
		auto physicsComponents = this->componentCollectionRepository->SelectFromCollection<SimplePhysicsComponent>("ScrollingBackgroundStars"); 

		for (auto physicsComponent : *physicsComponents) {
			physicsComponent.transformComponent->position.y += physicsComponent.velocity.y; 

			if (physicsComponent.transformComponent->position.y > this->windowHeight) {
				physicsComponent.transformComponent->position.y = 0.0f; 
			}
		}

		this->graphics->UpdateGraphics(graphicsComponents, transformComponents); 
	}

	return false; 
}


