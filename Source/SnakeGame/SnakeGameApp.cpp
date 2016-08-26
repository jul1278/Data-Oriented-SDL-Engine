#include "Graphics/Graphics.h"
#include "Demos/SnakeGame/SnakeGameApp.h"
#include "Demos/SnakeGame/SnakeGameStage.h"
#include "Demos/SnakeGame/SnakeGameMenuStage.h"

//------------------------------------------------------------------------------------
// Name: SnakeGameApp
// Desc:
//------------------------------------------------------------------------------------
SnakeGameApp::SnakeGameApp()
{
	this->windowHeight = 480;
	this->windowWidth = 640;
	this->appName = "Snake";

	this->graphics = new Graphics(this->windowWidth, this->windowHeight, this->appName);

	this->PushStage(new SnakeGameMenuStage(this));
}
//------------------------------------------------------------------------------------
// Name: SnakeGameApp
// Desc:
//------------------------------------------------------------------------------------
SnakeGameApp::~SnakeGameApp()
{
	delete this->graphics; 	
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
