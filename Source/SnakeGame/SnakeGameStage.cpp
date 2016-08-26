#include "Demos/SnakeGame/SnakeGameStage.h"
#include "Graphics/Graphics.h"
#include "Components/Repository/ComponentRepository.h"
#include "Demos/SnakeGame/SnakeAction.h"
#include "Components/GraphicsComponent.h"
#include "SDL.h"

//-----------------------------------------------------------------------
// Name: SnakeGameStage
// Desc:
//-----------------------------------------------------------------------
SnakeGameStage::SnakeGameStage(IGameApp* gameApp) : IStage(gameApp, new ComponentRepository("SnakeGameStage"),
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
	auto componentRepository = this->GetComponentRepository();
	auto graphics = this->GetGameApp()->GetGraphics();
	auto physics = this->GetPhysics();

	physics->ExecuteTasks(componentRepository);

	this->foodAction->Update();
	this->snakeAction->Update();

	auto graphicsComponents = componentRepository->Select<GraphicsComponent>("Snake");
	auto transformComponents = componentRepository->Select<TransformComponent>("Snake");
	auto foodGraphicsComponents = componentRepository->Select<GraphicsComponent>("Food");
	auto foodTransformComponents = componentRepository->Select<TransformComponent>("Food");
	auto scoreTransformComponents = componentRepository->Select<TransformComponent>("Score");
	auto scoreGraphicsComponents = componentRepository->Select<GraphicsComponent>("Score");

	SDL_Delay(100);

	graphics->Clear();
	graphics->UpdateGraphics(graphicsComponents, transformComponents);
	graphics->UpdateGraphics(foodGraphicsComponents, foodTransformComponents);
	graphics->UpdateGraphics(scoreGraphicsComponents, scoreTransformComponents);
	graphics->Present();
}
