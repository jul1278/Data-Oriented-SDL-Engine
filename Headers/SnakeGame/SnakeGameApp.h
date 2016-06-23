#ifndef SNAKE_GAME_APP_H
#define SNAKE_GAME_APP_H

#include "Game\IGameApp.h"

class SnakeGameApp : public IGameApp
{
	int windowHeight;
	int windowWidth;
	std::string appName;

	Graphics* graphics;
	
	IStage* snakeGameStage;
	IStage* snakeGameMenu;

public:

	SnakeGameApp();
	~SnakeGameApp();

	Graphics* GetGraphics() override final;
};

#endif // SNAKE_GAME_APP_H