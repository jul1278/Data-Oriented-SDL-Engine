#include "Game/IGameApp.h"
#include "Graphics/Graphics.h"
#include "Physics/Physics.h"
#include "Components/Repository/ComponentRepository.h"
#include "Events/SDLEventCollector.h"
#include "Events/IntersectionEventArgs.h"
#include "Physics/IntersectionTask.h"
#include "Events/ButtonEventArgs.h"
#include "Events/QuitApplicationEventArgs.h"
#include "Graphics/RectGraphicsResource.h"
#include "Graphics/TextGraphicsResource.h"
#include "Components/GraphicsComponent.h"
#include "Components/TransformComponent.h"
#include "Demos/SnakeGame/SnakeAction.h"
#include "Demos/SnakeGame/SnakeEatFoodTask.h"
#include "Demos/SnakeGame/SnakeEatSelfTask.h"
#include "Demos/SnakeGame/SnakeGameStage.h"

#include <string>
#include <iostream>

//---------------------------------------------------------------------------
// Name: SnakeAction 
// Desc:
//---------------------------------------------------------------------------
SnakeAction::SnakeAction(IStage* stage) : IAction(stage)
{
	this->sdlEventCollector = new SDLEventCollector(stage->GetGameApp()->GetGraphics()->WindowWidth(), stage->GetGameApp()->GetGraphics()->WindowHeight());

	this->snakeStartLength = 4;
	this->snakeScore = 0;
	this->snakeLength = this->snakeStartLength;

	this->currentSnakeDirection = SNAKE_LEFT;

	this->stage = stage; 

	auto graphics = stage->GetGameApp()->GetGraphics();
	auto physics = stage->GetPhysics(); 
	auto componentCollection = stage->GetComponentRepository();
	
	auto headStartPos = Vector2D(graphics->WindowWidth() / 2.0f, graphics->WindowHeight() / 2.0f);

	/* Create the score text */
	componentCollection->NewCollection("Score");
	this->textGraphicResource = new TextGraphicsResource("0", 20, Color(Color::White)); 
	auto textGraphicResourceId = graphics->AddGraphicsResource(this->textGraphicResource); 
	
	auto scoreTextTransformComponent = componentCollection->NewComponent<TransformComponent>("Score");
	auto scoreGraphicsComponent = componentCollection->NewComponent<GraphicsComponent>("Score"); 

	scoreTextTransformComponent->position = Vector2D(15.0f, 10.0f); 
	scoreGraphicsComponent->transformComponentId = scoreTextTransformComponent->id; 
	scoreGraphicsComponent->resourceId = textGraphicResourceId; 
	
	/* Create the snake */
	componentCollection->NewCollection("Snake");
	 
	auto snakeHead = componentCollection->NewComponent<TransformComponent>("Snake");
	auto snakeHeadGraphics = componentCollection->NewComponent<GraphicsComponent>("Snake");

	this->snakeGraphicId = graphics->AddGraphicsResource(new RectGraphicsResource(8.0f, 8.0f, Color(Color::White)));

	snakeHead->position = headStartPos;
	snakeHeadGraphics->transformComponentId = snakeHead->id;
	snakeHeadGraphics->resourceId = this->snakeGraphicId;

	auto lastPos = snakeHead->position;

	for (auto i = 0; i < (this->snakeStartLength - 1); i++) {

		auto snakePart = componentCollection->NewComponent<TransformComponent>("Snake");
		auto snakePartGraphics = componentCollection->NewComponent<GraphicsComponent>("Snake");

		lastPos += Vector2D(10.0f, 0.0);

		snakePart->position = lastPos;
		snakePartGraphics->transformComponentId = snakePart->id;
		snakePartGraphics->resourceId = snakeGraphicId;
	}

	auto buttonEventHandler = [this] (const ButtonEventArgs& args){this->OnButtonEvent(args); };
	auto quitEventHandler = [this] (const QuitApplicationEventArgs& args) {this->OnQuitApplication(args); };

	this->sdlEventCollector->RegisterListener<ButtonEventArgs>(buttonEventHandler);
	this->sdlEventCollector->RegisterListener<QuitApplicationEventArgs>(quitEventHandler); 

	auto physicsTask = new SnakeEatFoodTask(); 
	physics->AddPhysicsTask(physicsTask); 
	physicsTask->RegisterListener<IntersectionEventArgs>(bind(&SnakeAction::OnEatFood, this, placeholders::_1));

	auto eatSelfTask = new SnakeEatSelfTask(); 
	physics->AddPhysicsTask(eatSelfTask); 
	eatSelfTask->RegisterListener<IntersectionEventArgs>(bind(&SnakeAction::OnEatSelf, this, placeholders::_1)); 
}
//---------------------------------------------------------------------------
// Name: destructor
// Desc:
//---------------------------------------------------------------------------
SnakeAction::~SnakeAction()
{
	delete this->sdlEventCollector; 
}
//---------------------------------------------------------------------------
// Name: Update
// Desc:
//---------------------------------------------------------------------------
void SnakeAction::Update() 
{
	auto componentRepository = this->stage->GetComponentRepository(); 

	auto transformComponents = componentRepository->Select<TransformComponent>("Snake");
	auto graphicsComponents = componentRepository->Select<GraphicsComponent>("Snake");
	auto foodTransform = componentRepository->Select<TransformComponent>("Food").front(); 

	this->sdlEventCollector->Update();

	if (!transformComponents.empty()) {
		auto& headTransform = transformComponents.front();

		Vector2D lastPos;
		auto nextPos = headTransform.position;

		switch (this->currentSnakeDirection) {
		case SNAKE_LEFT:
			headTransform.position += Vector2D(-10.0f, 0.0f);
			break;
		case SNAKE_RIGHT:
			headTransform.position += Vector2D(10.0f, 0.0f);
			break;
		case SNAKE_DOWN:
			headTransform.position += Vector2D(0.0f, 10.0f);
			break;
		case SNAKE_UP:
			headTransform.position += Vector2D(0.0f, -10.0f);
			break;
		}

		for (auto i = 1; i < transformComponents.Size(); i++) {
			lastPos = transformComponents[i].position;
			transformComponents[i].position = nextPos;
			nextPos = lastPos;
		}
	}
}
//---------------------------------------------------------------------------
// Name: OnButtonEvent
// Desc:
//---------------------------------------------------------------------------
void SnakeAction::OnButtonEvent(const ButtonEventArgs& buttonEventArgs)
{
	if (!buttonEventArgs.Released()) {
		return;
	}

	if (buttonEventArgs.Key() == LEFT_ARROW) {

		switch (this->currentSnakeDirection) {
		case SNAKE_LEFT:
			this->currentSnakeDirection = SNAKE_DOWN;
			break;
		case SNAKE_RIGHT:
			this->currentSnakeDirection = SNAKE_UP;
			break;
		case SNAKE_DOWN:
			this->currentSnakeDirection = SNAKE_LEFT;
			break;
		case SNAKE_UP:
			this->currentSnakeDirection = SNAKE_LEFT;
			break;
		}
	}
	else if (buttonEventArgs.Key() == RIGHT_ARROW) {

		switch (this->currentSnakeDirection) {
		case SNAKE_LEFT:
			this->currentSnakeDirection = SNAKE_UP;
			break;
		case SNAKE_RIGHT:
			this->currentSnakeDirection = SNAKE_DOWN;
			break;
		case SNAKE_DOWN:
			this->currentSnakeDirection = SNAKE_RIGHT;
			break;
		case SNAKE_UP:
			this->currentSnakeDirection = SNAKE_RIGHT;
			break;
		}
	}
}
//---------------------------------------------------------------------------
// Name: OnEatFood
// Desc:
//---------------------------------------------------------------------------
void SnakeAction::OnEatFood(const IntersectionEventArgs& intersectionEventArgs)
{
	auto componentRepository = this->stage->GetComponentRepository(); 
	auto snakeComponents = componentRepository->Select<TransformComponent>("Snake"); 
	
	this->snakeScore++;

	this->textGraphicResource->SetText(to_string(this->snakeScore));

	auto newSnakePart = componentRepository->NewComponent<TransformComponent>("Snake");
	auto newSnakeGraphic = componentRepository->NewComponent<GraphicsComponent>("Snake");

	newSnakePart->position = snakeComponents.back().position;
	newSnakeGraphic->transformComponentId = newSnakePart->id;
	newSnakeGraphic->resourceId = this->snakeGraphicId;	
}
//---------------------------------------------------------------------------
// Name: OnEatSelf
// Desc:
//---------------------------------------------------------------------------
void SnakeAction::OnEatSelf(const IntersectionEventArgs& intersectionEventArgs)
{
	this->stage->GetGameApp()->PopStage();
	this->stage->GetGameApp()->PushStage(new SnakeGameStage(this->stage->GetGameApp())); 
}
//---------------------------------------------------------------------------
// Name: OnQuitApplication
// Desc:
//---------------------------------------------------------------------------
void SnakeAction::OnQuitApplication(const QuitApplicationEventArgs& quitApplicationEventArgs) const
{
	this->stage->GetGameApp()->PopStage();
}
