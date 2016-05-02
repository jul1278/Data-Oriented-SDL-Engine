#include "Game/IGameApp.h"
#include "Graphics/Graphics.h"
#include "Physics/Physics.h"
#include "Components/ComponentCollectionRepository.h"
#include "Events/SDLEventCollector.h"
#include "Events/IntersectionEventArgs.h"
#include "Physics/IntersectionTask.h"
#include "Events/ButtonEventArgs.h"
#include "Events/QuitApplicationEventArgs.h"
#include "Graphics/RectGraphicsResource.h"
#include "Graphics/TextGraphicsResource.h"
#include "Components/GraphicsComponent.h"
#include "Components/TransformComponent.h"
#include "SnakeGame/SnakeAction.h"

#include <string>
#include <iostream>

//---------------------------------------------------------------------------
// Name: SnakeAction 
// Desc:
//---------------------------------------------------------------------------
SnakeAction::SnakeAction(IGameApp* gameApp)
{
	this->snakeStartLength = 4;
	this->snakeScore = 0;
	this->snakeLength = this->snakeStartLength;

	this->currentSnakeDirection = SNAKE_LEFT;

	this->gameApp = gameApp; 

	auto graphics = gameApp->GetGraphics();
	auto physics = gameApp->GetPhysics(); 
	auto componentCollection = gameApp->GetComponentCollectionRepository();
	
	auto headStartPos = Vector2D(graphics->WindowWidth() / 2.0f, graphics->WindowHeight() / 2.0f);

	/* Create the score text */
	componentCollection->NewCollection("Score");
	this->textGraphicResource = new TextGraphicsResource("0", "", 20); 
	auto textGraphicResourceId = graphics->AddGraphicsResource(this->textGraphicResource); 
	
	auto scoreTextTransformComponent = componentCollection->NewComponent<TransformComponent>("Score");
	auto scoreGraphicsComponent = componentCollection->NewComponent<GraphicsComponent>("Score"); 

	scoreTextTransformComponent->position = Vector2D(15.0f, 10.0f); 
	scoreGraphicsComponent->transformComponent = scoreTextTransformComponent; 
	scoreGraphicsComponent->resourceId = textGraphicResourceId; 
	
	/* Create the snake */
	componentCollection->NewCollection("Snake");
	 
	auto snakeHead = componentCollection->NewComponent<TransformComponent>("Snake");
	auto snakeHeadGraphics = componentCollection->NewComponent<GraphicsComponent>("Snake");

	this->snakeGraphicId = graphics->AddGraphicsResource(new RectGraphicsResource(8.0f, 8.0f, 0xff, 0xff, 0xff, 0xff));

	snakeHead->position = headStartPos;
	snakeHeadGraphics->transformComponent = snakeHead;
	snakeHeadGraphics->resourceId = this->snakeGraphicId;

	auto lastPos = snakeHead->position;

	for (auto i = 0; i < (this->snakeStartLength - 1); i++) {

		auto snakePart = componentCollection->NewComponent<TransformComponent>("Snake");
		auto snakePartGraphics = componentCollection->NewComponent<GraphicsComponent>("Snake");

		lastPos += Vector2D(10.0f, 0.0);

		snakePart->position = lastPos;
		snakePartGraphics->transformComponent = snakePart;
		snakePartGraphics->resourceId = snakeGraphicId;
	}

	this->sdlEventCollector.RegisterListener<ButtonEventArgs>(bind(&SnakeAction::OnButtonEvent, this, placeholders::_1));
	this->sdlEventCollector.RegisterListener<QuitApplicationEventArgs>(bind(&SnakeAction::OnQuitApplication, this, placeholders::_1));

	auto physicsTask = new IntersectionTask("Food", "Snake"); 
	physics->AddPhysicsTask(physicsTask); 
	physicsTask->RegisterListener<IntersectionEventArgs>(bind(&SnakeAction::OnEatFood, this, placeholders::_1));
}
//---------------------------------------------------------------------------
// Name: Update
// Desc:
//---------------------------------------------------------------------------
void SnakeAction::Update(IGameApp* gameApp) 
{
	auto componentCollectionRepository = gameApp->GetComponentCollectionRepository(); 

	auto transformComponents = componentCollectionRepository->SelectFromCollection<TransformComponent>("Snake");
	auto graphicsComponents = componentCollectionRepository->SelectFromCollection<GraphicsComponent>("Snake");
	auto foodTransform = componentCollectionRepository->SelectFromCollection<TransformComponent>("Food")->front(); 

	this->sdlEventCollector.Update();

	if (!transformComponents->empty()) {
		auto& headTransform = transformComponents->front();

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

		for (auto i = 1; i < transformComponents->size(); i++) {
			lastPos = (*transformComponents)[i].position;
			(*transformComponents)[i].position = nextPos;
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
	auto componentCollectionRepository = this->gameApp->GetComponentCollectionRepository(); 

	auto snakeComponents = componentCollectionRepository->SelectFromCollection<TransformComponent>("Snake"); 
	auto snakeHeadId = snakeComponents->front().id; 

	if (intersectionEventArgs.TransformComponent1()->id == snakeHeadId 
		|| intersectionEventArgs.TransformComponent2()->id == snakeHeadId) {
		
		this->snakeScore++;

		this->textGraphicResource->SetText(to_string(this->snakeScore));

		auto newSnakePart = componentCollectionRepository->NewComponent<TransformComponent>("Snake");
		auto newSnakeGraphic = componentCollectionRepository->NewComponent<GraphicsComponent>("Snake");

		newSnakePart->position = snakeComponents->back().position;
		newSnakeGraphic->transformComponent = newSnakePart;
		newSnakeGraphic->resourceId = this->snakeGraphicId;
	}
}
//---------------------------------------------------------------------------
// Name: OnQuitApplication
// Desc:
//---------------------------------------------------------------------------
void SnakeAction::OnQuitApplication(const QuitApplicationEventArgs& quitApplicationEventArgs)
{
	this->gameApp->PopStage(); 
}
