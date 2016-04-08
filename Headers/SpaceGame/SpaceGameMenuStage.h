#ifndef SPACE_GAME_MENU_STAGE_H
#define SPACE_GAME_MENU_STAGE_H

#include <Game/IStage.h>
#include <Game/IGameApp.h>
#include <IAction.h>
#include <Events/SDLEventCollector.h>
#include <GraphicsResources/TextGraphicsResource.h>

class SpaceGameMenuStage : public IStage
{
private:

	list<IAction*> actions; 

	int stageHeight; 
	int stageWidth; 

	SDLEventCollector* sdlEventCollector;

public:

	SpaceGameMenuStage(IGameApp* gameApp)
	{
		auto graphics = gameApp->GetGraphics();
		auto componentCollectionRepository = gameApp->GetComponentCollectionRepository();

		this->sdlEventCollector = new SDLEventCollector();

		this->stageHeight = graphics->WindowHeight();
		this->stageWidth = graphics->WindowWidth();

		auto newGameTextGraphicResId = graphics->AddGraphicsResource(new TextGraphicsResource("Start Game", "", 25)); 
		
		componentCollectionRepository->NewCollection("MainMenu");

		auto newGameTextTransform = componentCollectionRepository->NewComponent<TransformComponent>("MainMenu");
		auto newGameTextGraphicComponent = componentCollectionRepository->NewComponent<GraphicsComponent>("MainMenu"); 

		newGameTextTransform->position = Vector2D(this->stageWidth / 2, this->stageHeight / 2); 
		newGameTextTransform->scale = Vector2D(1.0f, 3.0f); 

		newGameTextGraphicComponent->transformComponent = newGameTextTransform; 
		newGameTextGraphicComponent->resourceId = newGameTextGraphicResId; 
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