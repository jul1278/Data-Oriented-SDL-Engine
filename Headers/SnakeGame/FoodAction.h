#ifndef FOOD_ACTIONS_H
#define FOOD_ACTIONS_H

#include "Graphics/Graphics.h"
#include "Components/ComponentCollectionRepository.h"
#include "Physics/Physics.h"
#include "Actions/IAction.h"
#include "Events/CollisionEventArgs.h"
#include "Game/IGameApp.h"
#include "Utility/MathUtility.h"
#include "Components/GraphicsComponent.h"
#include <Graphics/RectGraphicsResource.h>

class FoodAction : public IAction
{
private:
	int counter; 

	int width;
	int height;

	void SpawnFood(IGameApp* gameApp)
	{
		auto graphics = gameApp->GetGraphics();
		auto componentCollections = gameApp->GetComponentCollectionRepository();

		auto width = graphics->WindowWidth();
		auto height = graphics->WindowHeight();

		auto& foodTransform = componentCollections->SelectFromCollection<TransformComponent>("Food")->front();
		auto snakeTransforms = componentCollections->SelectFromCollection<TransformComponent>("Snake");

		auto notSpawnFood = true;

		while (notSpawnFood) {

			int x = 10 * (MathUtility::RandomIntUniformDist() % (width / 10));
			int y = 10 * (MathUtility::RandomIntUniformDist() % (height / 10));

			foodTransform.position.x = x;
			foodTransform.position.y = y;

			notSpawnFood = false;

			for (auto snakeTransform : *snakeTransforms) {
				if (snakeTransform.position == foodTransform.position) {
					notSpawnFood = true;
					break;
				}
			}
		}
	}

public:
	
	FoodAction(IGameApp* gameApp)
	{
		counter = 0; 

		width = gameApp->GetGraphics()->WindowWidth(); 
		height = gameApp->GetGraphics()->WindowHeight(); 

		auto componentCollection = gameApp->GetComponentCollectionRepository(); 
		auto graphics = gameApp->GetGraphics(); 
		auto physics = gameApp->GetPhysics(); 

		auto foodGraphicId = graphics->AddGraphicsResource(new RectGraphicsResource(8.0f, 8.0f, 0xff, 0xff, 0xff, 0xff));

		componentCollection->NewCollection("Food");

		auto foodPos = componentCollection->NewComponent<TransformComponent>("Food");
		auto foodGraphic = componentCollection->NewComponent<GraphicsComponent>("Food");

		foodPos->position.x = MathUtility::RandomIntUniformDist() % graphics->WindowWidth();
		foodPos->position.y = MathUtility::RandomIntUniformDist() % graphics->WindowHeight();

		foodGraphic->resourceId = foodGraphicId;
		foodGraphic->transformComponent = foodPos;

		this->SpawnFood(gameApp);

		// physics->
	}

	~FoodAction() override
	{
	}

	void Update(IGameApp* gameApp)
	{
		auto components = gameApp->GetComponentCollectionRepository();
		auto& foodTransform = components->SelectFromCollection<TransformComponent>("Food")->front();

		foodTransform.position.x += 10.0f * ((MathUtility::RandomIntUniformDist() / 10) % width); 
		foodTransform.position.y += 10*(MathUtility::RandomIntUniformDist() % 2);
	}

	void OnSnakeCollision(const CollisionEventArgs& collisionEventArgs)
	{
		
	}
};

#endif // FOOD_ACTIONS_H