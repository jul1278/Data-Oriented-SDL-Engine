#ifndef SPACE_GAME_ACTION_H
#define SPACE_GAME_ACTION_H

#include "Game/IStage.h"
#include "Actions/IAction.h"

class SpaceGameAction : public IAction
{

public:

	SpaceGameAction(IStage* stage): IAction(stage)
	{
	}

	void Update() override final
	{
	}

};

#endif // SPACE_GAME_ACTION_H