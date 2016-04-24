#ifndef SPACE_GAME_ACTION_H
#define SPACE_GAME_ACTION_H

#include <Game\IStage.h>
#include "Actions/IAction.h"

class SpaceGameAction : public IAction
{

private:

public:

	SpaceGameAction(const IStage& stage)
	{
		
	}

	void Update(IGameApp* gameApp) override final
	{

	}

};

#endif // SPACE_GAME_ACTION_H