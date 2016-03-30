#ifndef SPACE_GAME_STATE_ACTION_H
#define SPACE_GAME_STATE_ACTION_H

#include "IAction.h"
#include <Graphics.h>

class SpaceGameStateAction : public IAction
{

private:

	Graphics* graphics; 

public:

	void Update(ComponentCollectionRepository* componentCollectionRepository) override final
	{

	}





};

#endif // SPACE_GAME_STATE_ACTION_H