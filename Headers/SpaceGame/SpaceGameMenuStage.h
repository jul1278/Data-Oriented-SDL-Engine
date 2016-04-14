#ifndef SPACE_GAME_MENU_STAGE_H
#define SPACE_GAME_MENU_STAGE_H

#include "Game\IStage.h"
#include "Game\IGameApp.h"
#include "Actions\IAction.h"
#include "Events\SDLEventCollector.h"
#include "Graphics\TextGraphicsResource.h"
#include "Events\MouseMotionEventArgs.h"
#include <Components/SimpleButtonComponent.h>

class SpaceGameMenuStage : public IStage
{
private:

	list<IAction*> actions; 

	int stageHeight; 
	int stageWidth; 

	SDLEventCollector* sdlEventCollector;
	ComponentCollectionRepository* componentCollectionRepository; 

public:

	SpaceGameMenuStage(IGameApp* gameApp)
	{
		auto graphics = gameApp->GetGraphics();
		this->componentCollectionRepository = gameApp->GetComponentCollectionRepository();

		this->sdlEventCollector = new SDLEventCollector();

		this->stageHeight = graphics->WindowHeight();
		this->stageWidth = graphics->WindowWidth();

		auto newGameTextGraphicResId = graphics->AddGraphicsResource(new TextGraphicsResource("Start Game", "", 25)); 
		
		componentCollectionRepository->NewCollection("MainMenu");

		auto topLeftX = (this->stageWidth / 4); 
		auto topLeftY = (this->stageHeight / 4);

		auto newGameTextTransform = componentCollectionRepository->NewComponent<TransformComponent>("MainMenu");
		auto newGameTextGraphicComponent = componentCollectionRepository->NewComponent<GraphicsComponent>("MainMenu"); 
		auto newGameButtonComponent = componentCollectionRepository->NewComponent<SimpleButtonComponent>("MainMenu");

		newGameTextTransform->position = Vector2D(this->stageWidth / 2, this->stageHeight / 2); 
		newGameTextTransform->scale = Vector2D(1.0f, 3.0f); 

		newGameTextGraphicComponent->transformComponent = newGameTextTransform; 
		newGameTextGraphicComponent->resourceId = newGameTextGraphicResId; 

		newGameButtonComponent->transformComponent = newGameTextTransform; 
		newGameButtonComponent->size = Vector2D(topLeftX, topLeftY); 
	}

	void Update(IGameApp* gameApp) override final
	{
		auto graphics = gameApp->GetGraphics();
		auto componentCollectionRepository = gameApp->GetComponentCollectionRepository();

		auto transformComponents = componentCollectionRepository->SelectFromCollection<TransformComponent>("MainMenu"); 
		auto graphicsComponents = componentCollectionRepository->SelectFromCollection<GraphicsComponent>("MainMenu"); 

		graphics->Clear(); 
		graphics->UpdateGraphics(graphicsComponents, transformComponents); 
		graphics->Present(); 
	}
};

#endif // SPACE_GAME_MENU_STAGE_H