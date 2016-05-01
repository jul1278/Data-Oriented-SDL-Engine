#ifndef SNAKE_ACTION_H
#define SNAKE_ACTION_H

#include "Actions/IAction.h"
#include "Events/SDLEventCollector.h"

class ComponentCollectionRepository;
class IGameApp; 
class ButtonEventArgs;
class TextGraphicsResource; 

enum SnakeDirection
{
	SNAKE_UP, SNAKE_RIGHT, SNAKE_DOWN, SNAKE_LEFT
};

class SnakeAction : public IAction
{
public:

	int snakeScore;
	int snakeLength;
	int snakeStartLength;

	TextGraphicsResource* textGraphicResource;
	SDLEventCollector sdlEventCollector; 
	SnakeDirection currentSnakeDirection;

	SnakeAction(IGameApp* gameApp);

	void Update(IGameApp* gameApp) override;
	void OnButtonEvent(const ButtonEventArgs& buttonEventArgs); 
};

#endif // SNAKE_ACTION_H