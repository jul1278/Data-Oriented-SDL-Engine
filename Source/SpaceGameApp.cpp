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
	return false; 
}


