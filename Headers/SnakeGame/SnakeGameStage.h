#ifndef SNAKE_GAME_STAGE_H
#define SNAKE_GAME_STAGE_H

#include "Game/IGameApp.h"
#include "Game/IStage.h"
#include "FoodAction.h"

class SnakeAction; 

class SnakeGameStage : public IStage
{
private:

	SnakeAction* snakeAction; 
	FoodAction* foodAction; 

public:

	SnakeGameStage(IGameApp* gameApp); 
	
	~SnakeGameStage(); 

	void Update() override final; 

};

#endif // SNAKE_GAME_STAGE_H
