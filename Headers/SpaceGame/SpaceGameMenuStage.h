#ifndef SPACE_GAME_MENU_STAGE_H
#define SPACE_GAME_MENU_STAGE_H

#include <Game/IStage.h>
#include <Game/IGameApp.h>
#include <IAction.h>
#include <Events/SDLEventCollector.h>
#include <GraphicsResources/TextGraphicsResource.h>

class SpaceGameMenuStage : IStage
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

		auto newGameTextGraphicResId = graphics->AddGraphicsResource(new TextGraphicsResource("Start Game", "")); 
	}

	void Update(IGameApp* gameApp) override final
	{

	}
};

#endif // SPACE_GAME_MENU_STAGE_H