#include "Graphics/Graphics.h"
#include "Physics/Physics.h"
#include "Components/ComponentCollectionRepository.h"
#include "SnakeGame/SnakeGameApp.h"
#include "SnakeGame/SnakeGameStage.h"
#include "SnakeGame/SnakeGameMenuStage.h"

//------------------------------------------------------------------------------------
// Name: SnakeGameApp
// Desc:
//------------------------------------------------------------------------------------
SnakeGameApp::SnakeGameApp()
{
	this->windowHeight = 480;
	this->windowWidth = 640;
	this->appName = "Snake";

	this->componentCollectionRepository = new ComponentCollectionRepository;

	this->graphics = new Graphics(this->windowWidth, this->windowHeight, this->appName);
	this->physics = new Physics(this->windowWidth, this->windowHeight);

	this->snakeGameStage = new SnakeGameStage(this);
	this->snakeGameMenu = new SnakeGameMenuStage(this);

	this->PushStage(this->snakeGameMenu);
	this->PushStage(this->snakeGameStage);
}
//------------------------------------------------------------------------------------
// Name: SnakeGameApp
// Desc:
//------------------------------------------------------------------------------------
SnakeGameApp::~SnakeGameApp()
{
	delete this->graphics; 
	delete this->componentCollectionRepository;
	delete this->physics; 

	delete this->snakeGameMenu; 
	delete this->snakeGameStage; 
}
//------------------------------------------------------------------------------------
// Name: GetGraphics
// Desc:
//------------------------------------------------------------------------------------
Graphics* SnakeGameApp::GetGraphics()
{
	return this->graphics;
}
//------------------------------------------------------------------------------------
// Name: GetPhysics
// Desc:
//------------------------------------------------------------------------------------
Physics* SnakeGameApp::GetPhysics()
{
	return this->physics;
}
//------------------------------------------------------------------------------------
// Name: GetComponentCollectionRepository
// Desc:
//------------------------------------------------------------------------------------
ComponentCollectionRepository* SnakeGameApp::GetComponentCollectionRepository()
{
	return this->componentCollectionRepository;
}
