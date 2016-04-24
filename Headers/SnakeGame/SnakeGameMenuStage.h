#ifndef SNAKE_GAME_MENU_STAGE_H
#define SNAKE_GAME_MENU_STAGE_H

#include "Game\IStage.h"
#include "Game\IGameApp.h"
#include "Actions\IAction.h"
#include "Events\SDLEventCollector.h"
#include "Graphics\TextGraphicsResource.h"
#include "Events\MouseMotionEventArgs.h"
#include "Components\SimpleButtonComponent.h"

class SnakeGameMenuStage : public IStage
{

	list<IAction*> actions;

	int stageHeight;
	int stageWidth;

	SDLEventCollector* sdlEventCollector;
	ComponentCollectionRepository* componentCollectionRepository;
	IGameApp* gameApp;

public:

	SnakeGameMenuStage(IGameApp* gameApp)
	{
		auto graphics = gameApp->GetGraphics();
		this->componentCollectionRepository = gameApp->GetComponentCollectionRepository();
		this->gameApp = gameApp;
		this->sdlEventCollector = new SDLEventCollector();

		this->stageHeight = graphics->WindowHeight();
		this->stageWidth = graphics->WindowWidth();

		// graphics owns this memory
		auto buttonGraphicsComponent = new TextGraphicsResource("Start Game", "", 25);
		auto newGameTextGraphicResId = graphics->AddGraphicsResource(buttonGraphicsComponent);

		componentCollectionRepository->NewCollection("MainMenu");

		auto newGameTextTransform = componentCollectionRepository->NewComponent<TransformComponent>("MainMenu");
		auto newGameTextGraphicComponent = componentCollectionRepository->NewComponent<GraphicsComponent>("MainMenu");
		auto newGameButtonComponent = componentCollectionRepository->NewComponent<SimpleButtonComponent>("MainMenu");

		newGameTextTransform->position = Vector2D(this->stageWidth / 2, this->stageHeight / 2);
		newGameTextTransform->scale = Vector2D(1.0f, 1.0f);

		newGameTextGraphicComponent->transformComponent = newGameTextTransform;
		newGameTextGraphicComponent->resourceId = newGameTextGraphicResId;

		newGameButtonComponent->transformComponent = newGameTextTransform;
		newGameButtonComponent->size = buttonGraphicsComponent->GetSize();

		this->sdlEventCollector->RegisterMouseClickHandler(newGameButtonComponent, bind(&SnakeGameMenuStage::OnMenuStartGameClick, this, placeholders::_1));
		this->sdlEventCollector->RegisterMouseOverHandler(newGameButtonComponent, bind(&SnakeGameMenuStage::OnMenuStartGameMouseOver, this, placeholders::_1));
	}

	~SnakeGameMenuStage()
	{
		for (auto action : this->actions) {
			delete action; 
		}
	}

	void Update(IGameApp* gameApp) override final
	{
		auto graphics = gameApp->GetGraphics();
		auto componentCollectionRepository = gameApp->GetComponentCollectionRepository();

		auto transformComponents = componentCollectionRepository->SelectFromCollection<TransformComponent>("MainMenu");
		auto graphicsComponents = componentCollectionRepository->SelectFromCollection<GraphicsComponent>("MainMenu");

		this->sdlEventCollector->Update();

		graphics->Clear();
		graphics->UpdateGraphics(graphicsComponents, transformComponents);
		graphics->Present();
	}

	void OnMenuStartGameClick(const MouseButtonEventArgs& mouseButtonEventArgs)
	{
		if (mouseButtonEventArgs.MouseButton() == LEFT_BUTTON && mouseButtonEventArgs.Released()) {
			this->gameApp->PopStage();
		}
	}

	void OnMenuStartGameMouseOver(const MouseMotionEventArgs& mouseMotionEventArgs)
	{
		auto startGameButton = this->componentCollectionRepository->SelectFromCollection<SimpleButtonComponent>("MainMenu");

		if (mouseMotionEventArgs.MouseOver()) {
			startGameButton->front().transformComponent->scale = Vector2D(1.2f, 1.2f);
		}
		else {
			startGameButton->front().transformComponent->scale = Vector2D(1.0f, 1.0f);
		}
	}
};

#endif // SNAKE_GAME_MENU_STAGE_H