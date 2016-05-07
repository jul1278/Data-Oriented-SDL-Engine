#include "SnakeGame/SnakeGameStage.h"
#include "Graphics/Graphics.h"
#include "Components/ComponentCollectionRepository.h"
#include "SnakeGame/SnakeAction.h"
#include "Components/GraphicsComponent.h"
#include "SDL.h"

//-----------------------------------------------------------------------
// Name: SnakeGameStage
// Desc:
//-----------------------------------------------------------------------
SnakeGameStage::SnakeGameStage(IGameApp* gameApp) : IStage(gameApp, new ComponentCollectionRepository,
	new Physics(gameApp->GetGraphics()->WindowWidth(), gameApp->GetGraphics()->WindowHeight()))
{
	this->snakeAction = new SnakeAction(this);
	this->foodAction = new FoodAction(this); 
}
//-----------------------------------------------------------------------
// Name: ~SnakeGameStage
// Desc:
//-----------------------------------------------------------------------
SnakeGameStage::~SnakeGameStage()
{
	delete this->snakeAction;
}

//-----------------------------------------------------------------------
// Name: Update
// Desc:
//-----------------------------------------------------------------------
void SnakeGameStage::Update()
{
	auto componentCollections = this->GetComponentCollectionRepository();
	auto graphics = this->GetGameApp()->GetGraphics();
	auto physics = this->GetPhysics();

	physics->ExecuteTasks(componentCollections);

	this->foodAction->Update();
	this->snakeAction->Update();

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
