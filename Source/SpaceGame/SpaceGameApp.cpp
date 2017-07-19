//
// Created by Julian  on 17/11/15.
//

#include "Demos/SpaceGame/SpaceGameApp.h"
#include "Components/Repository/ComponentRepository.h"
#include "Demos/SpaceGame/SpaceGameStage.h"
#include "Demos/SpaceGame/SpaceGameMenuStage.h"

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
	this->appName = "Asteroid Action";

	this->graphics = new Graphics(this->windowWidth, this->windowHeight, this->appName);

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
	delete this->graphics; 
	delete this->spaceGameStage; 
	delete this->spaceGameMenu;
}
//------------------------------------------------------------------------------------
// Name: GetGraphics
// Desc:
//------------------------------------------------------------------------------------
Graphics* SpaceGameApp::GetGraphics()
{
	return this->graphics; 
}
