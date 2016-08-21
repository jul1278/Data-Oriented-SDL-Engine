#ifndef SNAKE_GAME_MENU_STAGE_H
#define SNAKE_GAME_MENU_STAGE_H

#include "Game/IStage.h"
#include "Actions/IAction.h"

class QuitApplicationEventArgs;
class MouseMotionEventArgs;
class MouseButtonEventArgs;
class SDLEventCollector; 

class SnakeGameMenuStage : public IStage
{
public:

private:
	list<IAction*> actions;

	int stageHeight;
	int stageWidth;

	SDLEventCollector* sdlEventCollector;
	IGameApp* gameApp;

	void Setup();

public:

	SnakeGameMenuStage(IGameApp* gameApp);
	~SnakeGameMenuStage();

	void Update() override final;

	void OnMenuStartGameClick(const MouseButtonEventArgs& mouseButtonEventArgs) const;
	void OnMenuStartGameMouseOver(const MouseMotionEventArgs& mouseMotionEventArgs) const;
	void OnQuitApplication(const QuitApplicationEventArgs& quitApplicationEventArgs) const; 
};

#endif // SNAKE_GAME_MENU_STAGE_H