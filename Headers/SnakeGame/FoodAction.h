#ifndef FOOD_ACTIONS_H
#define FOOD_ACTIONS_H

#include "Components/ComponentCollectionRepository.h"
#include "Actions/IAction.h"
#include "Events/CollisionEventArgs.h"
#include "Game/IGameApp.h"
#include "Utility/MathUtility.h"

class FoodAction : public IAction
{
private:
	int counter; 
public:
	
	FoodAction(IGameApp* gameApp)
	{
		counter = 0; 
	}

	~FoodAction() override
	{
	}

	void Update(IGameApp* gameApp)
	{
		auto components = gameApp->GetComponentCollectionRepository();
		auto& foodTransform = components->SelectFromCollection<TransformComponent>("Food")->front();

		foodTransform.position.x += 10*(MathUtility::RandomIntUniformDist() % 2);
		foodTransform.position.y += 10*(MathUtility::RandomIntUniformDist() % 2);
	}

	void OnSnakeCollision(const CollisionEventArgs& collisionEventArgs)
	{
		
	}
};

#endif // FOOD_ACTIONS_H