//
// Created by Julian  on 17/11/15.
//


#include "SpaceGame/SpaceGameApp.h"
#include "Components/ComponentCollectionRepository.h"
#include "SpaceGame/SpaceGameStage.h"
#include "SpaceGame/SpaceGameMenuStage.h"

#include <time.h>
#include <stdlib.h>
#include <memory>

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
	this->spaceGameMenu = new SpaceGameMenuStage(this); 

	this->PushStage(this->spaceGameMenu); 
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
