#ifndef SNAKE_GAME_MENU_STAGE_H
#define SNAKE_GAME_MENU_STAGE_H

#include "Game\IStage.h"
#include "Actions\IAction.h"

class MouseMotionEventArgs;
class MouseButtonEventArgs;
class SDLEventCollector; 

class SnakeGameMenuStage : public IStage
{

	list<IAction*> actions;

	int stageHeight;
	int stageWidth;

	SDLEventCollector* sdlEventCollector;
	ComponentCollectionRepository* componentCollectionRepository;
	IGameApp* gameApp;

public:

	SnakeGameMenuStage(IGameApp* gameApp);

	~SnakeGameMenuStage();

	void Update(IGameApp* gameApp) override final;

	void OnMenuStartGameClick(const MouseButtonEventArgs& mouseButtonEventArgs) const;
	
	void OnMenuStartGameMouseOver(const MouseMotionEventArgs& mouseMotionEventArgs) const;
	
};

#endif // SNAKE_GAME_MENU_STAGE_H