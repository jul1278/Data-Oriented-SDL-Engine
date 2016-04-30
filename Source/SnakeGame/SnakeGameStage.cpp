#include "SnakeGame/SnakeGameStage.h"
#include "Graphics/Graphics.h"
#include "Components/ComponentCollectionRepository.h"
#include "SnakeGame/SnakeAction.h"
#include "Components/GraphicsComponent.h"
#include "SDL.h"

SnakeGameStage::SnakeGameStage(IGameApp* gameApp)
{
	this->snakeAction = new SnakeAction(gameApp);
	this->foodAction = new FoodAction(gameApp); 
}

SnakeGameStage::~SnakeGameStage()
{
	delete this->snakeAction;
}

void SnakeGameStage::Update(IGameApp* gameApp)
{
	auto componentCollections = gameApp->GetComponentCollectionRepository();
	auto graphics = gameApp->GetGraphics();

	this->foodAction->Update(gameApp); 
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