#ifndef FOOD_ACTIONS_H
#define FOOD_ACTIONS_H


#include "Game/IGameApp.h"
#include "Graphics/Graphics.h"
#include "Components/ComponentCollectionRepository.h"
#include "Physics/Physics.h"
#include "Actions/IAction.h"
#include "Events/CollisionEventArgs.h"
#include "Utility/MathUtility.h"
#include "Components/GraphicsComponent.h"
#include "Graphics/RectGraphicsResource.h"
#include "Physics/IntersectionTask.h"

#include <math.h>

class FoodAction : public IAction
{

	int stepCounter;
	int updateCounter; 

	int width;
	int height;

	IGameApp* gameApp; 

	int goalX; 
	int goalY; 

	void SpawnFood(IGameApp* gameApp)
	{
		this->gameApp = gameApp; 

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
		this->stepCounter = 0;
		this->updateCounter = 0; 

		width = gameApp->GetGraphics()->WindowWidth(); 
		height = gameApp->GetGraphics()->WindowHeight(); 

		auto componentCollection = gameApp->GetComponentCollectionRepository(); 
		auto graphics = gameApp->GetGraphics(); 
		auto physics = gameApp->GetPhysics(); 

		componentCollection->NewCollection("Food");
		
		auto foodGraphicId = graphics->AddGraphicsResource(new RectGraphicsResource(8.0f, 8.0f, 0xff, 0xff, 0xff, 0xff));
		auto foodPos = componentCollection->NewComponent<TransformComponent>("Food");
		auto foodGraphic = componentCollection->NewComponent<GraphicsComponent>("Food");

		foodPos->position.x = MathUtility::RandomIntUniformDist() % graphics->WindowWidth();
		foodPos->position.y = MathUtility::RandomIntUniformDist() % graphics->WindowHeight();

		foodGraphic->resourceId = foodGraphicId;
		foodGraphic->transformComponent = foodPos;

		this->SpawnFood(gameApp);

		auto intersectionTask = new IntersectionTask("Food", "Snake"); 

		physics->AddPhysicsTask(intersectionTask); 

		intersectionTask->RegisterListener<IntersectionEventArgs>(bind(&FoodAction::OnSnakeIntersection, this, placeholders::_1)); 
	}

	~FoodAction() override { }

	void Update(IGameApp* gameApp) override
	{
		this->stepCounter++;

		if (this->stepCounter < 5) {
			return;
		} else {
			this->stepCounter = 0; 
		}

		this->updateCounter++; 

		this->gameApp = gameApp; 

		auto components = gameApp->GetComponentCollectionRepository();
		auto& foodTransform = components->SelectFromCollection<TransformComponent>("Food")->front();

		auto diffX = foodTransform.position.x - this->goalX; 
		auto diffY = foodTransform.position.y - this->goalY; 

		if (abs(diffX) > abs(diffY)) {
			if (diffX > 0.0f) {
				foodTransform.position.x -= 10.0f;
			} else {
				foodTransform.position.y += 10.0f; 
			}
		} else {
			if (diffY > 0.0f) {
				foodTransform.position.y -= 10.0f;
			} else {
				foodTransform.position.y += 10.0f;
			}
		}

		if (this->updateCounter > 10) {
			this->goalX = 10 * (MathUtility::RandomIntUniformDist() % (width / 10));
			this->goalY = 10 * (MathUtility::RandomIntUniformDist() % (height / 10));
		}		
	}
	
	void OnSnakeIntersection(const IntersectionEventArgs& intersectionEventArgs)
	{
		auto components = this->gameApp->GetComponentCollectionRepository(); 
		auto snakeHead = components->SelectFromCollection<TransformComponent>("Snake")->front(); 

		if (intersectionEventArgs.TransformComponent1()->id == snakeHead.id 
			|| intersectionEventArgs.TransformComponent2()->id == snakeHead.id) {
			this->SpawnFood(this->gameApp);

		}
	}
};

#endif // FOOD_ACTIONS_H