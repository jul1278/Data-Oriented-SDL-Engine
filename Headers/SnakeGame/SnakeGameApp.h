#ifndef SNAKE_GAME_APP_H
#define SNAKE_GAME_APP_H

#include "Game\IGameApp.h"
#include "Components\ComponentCollectionRepository.h"

class SnakeGameApp : public IGameApp
{
	int windowHeight;
	int windowWidth;
	std::string appName;

	ComponentCollectionRepository* componentCollectionRepository;

	Graphics* graphics;
	Physics* physics;

	IStage* snakeGameStage;
	IStage* snakeGameMenu;

public:

	SnakeGameApp();
	~SnakeGameApp();

	Graphics* GetGraphics() override final;
	Physics* GetPhysics() override final;
	ComponentCollectionRepository* GetComponentCollectionRepository() override final;
};

#endif // SNAKE_GAME_APP_H