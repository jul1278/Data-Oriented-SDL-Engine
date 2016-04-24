#ifndef FOOD_ACTIONS_H
#define FOOD_ACTIONS_H

#include "Actions/IAction.h"
#include "Events/CollisionEventArgs.h"
#include "Game/IGameApp.h"

class FoodAction : public IAction
{
public:
	
	FoodAction(IGameApp* gameApp)
	{
	}

	~FoodAction() override
	{
	}


	void OnSnakeCollision(const CollisionEventArgs& collisionEventArgs)
	{
		
	}
};

#endif // FOOD_ACTIONS_H