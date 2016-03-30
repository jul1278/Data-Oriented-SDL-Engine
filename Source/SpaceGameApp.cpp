//
// Created by Julian  on 17/11/15.
//

#include <time.h>
#include <stdlib.h>
#include <memory>
#include <SpaceGame\SpaceGameApp.h>
#include <GraphicsResources\RectGraphicsResource.h>
#include <GraphicsResources\StarGraphicsResource.h>
#include <GraphicsResources\ProceduralAsteroidGraphicsResource.h>

#include <ComponentCollectionRepository.h>
#include <Components\SimplePhysicsComponent.h>
#include <SpaceGame\SpaceGameEntityConstructor.h>
#include <Utility\MathUtility.h>
#include <Actions/AsteroidAction.h>
#include <Actions/PlayerSpaceshipAction.h>
#include <Actions/BackgroundStarsAction.h>
#include <SpaceGame/SpaceGameStage.h>

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
	this->physics = new Physics(this->windowWidth, this->windowHeight); 

	this->spaceGameStage = new SpaceGameStage(this); 
	this->PushStage(this->spaceGameStage); 
}
//------------------------------------------------------------------------------------
// Name: ~SpaceGameApp
// Desc:
//------------------------------------------------------------------------------------
SpaceGameApp::~SpaceGameApp()
{
	// delet
	delete this->componentCollectionRepository; 
	delete this->graphics; 
	delete this->physics;
}
//------------------------------------------------------------------------------------
// Name: GetGraphics
// Desc:
//------------------------------------------------------------------------------------
Graphics* SpaceGameApp::GetGraphics()
{
	return this->graphics; 
}
//------------------------------------------------------------------------------------
// Name: GetPhysics
// Desc:
//------------------------------------------------------------------------------------
Physics* SpaceGameApp::GetPhysics()
{
	return this->physics;
}
//------------------------------------------------------------------------------------
// Name: GetComponentCollectionRepository
// Desc:
//------------------------------------------------------------------------------------
ComponentCollectionRepository* SpaceGameApp::GetComponentCollectionRepository()
{
	return this->componentCollectionRepository; 
}
