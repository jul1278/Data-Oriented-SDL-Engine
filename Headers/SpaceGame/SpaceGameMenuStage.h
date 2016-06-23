#ifndef SPACE_GAME_MENU_STAGE_H
#define SPACE_GAME_MENU_STAGE_H

#include "Game\IStage.h"
#include "Game\IGameApp.h"
#include "Events\SDLEventCollector.h"
#include "Events\MouseMotionEventArgs.h"

class SpaceGameMenuStage : public IStage
{
	int stageHeight; 
	int stageWidth; 

	SDLEventCollector* sdlEventCollector;

	void OnMenuStartGameMouseOver(const MouseMotionEventArgs& mouseMotionEventArgs) const;
	void OnMenuStartGameClick(const MouseButtonEventArgs& mouseButtonEventArgs) const;

public:

	SpaceGameMenuStage(IGameApp* gameApp); 

	void Update() override final;
};

#endif // SPACE_GAME_MENU_STAGE_H