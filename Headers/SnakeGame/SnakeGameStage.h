#ifndef SNAKE_GAME_STAGE_H
#define SNAKE_GAME_STAGE_H

#include "Game/IGameApp.h"
#include "Game/IStage.h"
#include "SnakeAction.h"

class SnakeGameStage : public IStage
{
private:

	SnakeAction* snakeAction; 

public:

	SnakeGameStage(IGameApp* gameApp)
	{
		this->snakeAction = new SnakeAction(gameApp); 
	}

	~SnakeGameStage()
	{
		delete this->snakeAction; 
	}

	void Update(IGameApp* gameApp) override final
	{
		auto componentCollections = gameApp->GetComponentCollectionRepository(); 
		auto graphics = gameApp->GetGraphics(); 
	
		this->snakeAction->Update(gameApp); 

		auto graphicsComponents = componentCollections->SelectFromCollection<GraphicsComponent>("Snake"); 
		auto transformComponents = componentCollections->SelectFromCollection<TransformComponent>("Snake"); 
		auto foodGraphicsComponents = componentCollections->SelectFromCollection<GraphicsComponent>("Food"); 
		auto foodTransformComponents = componentCollections->SelectFromCollection<TransformComponent>("Food"); 
		auto scoreTransformComponents = componentCollections->SelectFromCollection<TransformComponent>("Score"); 
		auto scoreGraphicsComponents = componentCollections->SelectFromCollection<GraphicsComponent>("Score");

		SDL_Delay(100); 

		graphics->Clear(); 
		graphics->UpdateGraphics(graphicsComponents, transformComponents); 
		graphics->UpdateGraphics(foodGraphicsComponents, foodTransformComponents); 
		graphics->UpdateGraphics(scoreGraphicsComponents, scoreTransformComponents); 
		graphics->Present();
	}

};

#endif // SNAKE_GAME_STAGE_H
