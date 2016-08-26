#ifndef FOOD_ACTIONS_H
#define FOOD_ACTIONS_H


#include "Game/IGameApp.h"
#include "Graphics/Graphics.h"
#include "Components/Repository/componentRepository.h"
#include "Physics/Physics.h"
#include "Actions/IAction.h"
#include "Events/CollisionEventArgs.h"
#include "Utility/MathUtility.h"
#include "Components/GraphicsComponent.h"
#include "Graphics/RectGraphicsResource.h"
#include "Physics/IntersectionTask.h"
#include "Demos/SnakeGame/SnakeEatFoodTask.h"

#include <math.h>

class FoodAction : public IAction
{

	int stepCounter;
	int updateCounter; 

	int width;
	int height;

	IStage* stage; 

	int goalX; 
	int goalY; 

	void SpawnFood() const
	{
		auto graphics = this->stage->GetGameApp()->GetGraphics();
		auto componentCollections = this->stage->GetComponentRepository();

		auto width = graphics->WindowWidth();
		auto height = graphics->WindowHeight();

		auto& foodTransform = componentCollections->Select<TransformComponent>("Food").front();
		auto snakeTransforms = componentCollections->Select<TransformComponent>("Snake");

		auto notSpawnFood = true;

		while (notSpawnFood) {

			int x = 10 * (MathUtility::RandomIntUniformDist() % (width / 10));
			int y = 10 * (MathUtility::RandomIntUniformDist() % (height / 10));

			foodTransform.position.x = x;
			foodTransform.position.y = y;

			notSpawnFood = false;

			for (auto snakeTransform : snakeTransforms) {
				if (snakeTransform.position == foodTransform.position) {
					notSpawnFood = true;
					break;
				}
			}
		}
	}

public:
	
	FoodAction(IStage* stage) : IAction(stage)
	{
		this->stage = stage; 

		this->stepCounter = 0;
		this->updateCounter = 0; 

		width = stage->GetGameApp()->GetGraphics()->WindowWidth(); 
		height = stage->GetGameApp()->GetGraphics()->WindowHeight(); 

		auto componentCollection = stage->GetComponentRepository();
		auto graphics = stage->GetGameApp()->GetGraphics();
		auto physics = stage->GetPhysics();

		componentCollection->NewCollection("Food");
		
		auto foodGraphicId = graphics->AddGraphicsResource(new RectGraphicsResource(8.0f, 8.0f, Color(Color::White)));
		auto foodPos = componentCollection->NewComponent<TransformComponent>("Food");
		auto foodGraphic = componentCollection->NewComponent<GraphicsComponent>("Food");

		foodPos->position.x = MathUtility::RandomIntUniformDist() % graphics->WindowWidth();
		foodPos->position.y = MathUtility::RandomIntUniformDist() % graphics->WindowHeight();

		foodGraphic->resourceId = foodGraphicId;
		foodGraphic->transformComponentId = foodPos->id;

		this->SpawnFood();

		auto eatFoodTask = new SnakeEatFoodTask(); 
		physics->AddPhysicsTask(eatFoodTask); 
		eatFoodTask->RegisterListener<IntersectionEventArgs>(bind(&FoodAction::OnSnakeIntersection, this, placeholders::_1));
	}

	~FoodAction() override { }

	void Update() override
	{
		this->stepCounter++;

		if (this->stepCounter < 5) {
			return;
		} else {
			this->stepCounter = 0; 
		}

		this->updateCounter++; 

		auto components = stage->GetComponentRepository();
		auto& foodTransform = components->Select<TransformComponent>("Food").front();

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
	
	void OnSnakeIntersection(const IntersectionEventArgs& intersectionEventArgs) const
	{
		auto components = this->stage->GetComponentRepository(); 
		auto snakeHead = components->Select<TransformComponent>("Snake").front(); 

		if (intersectionEventArgs.TransformComponent1()->id == snakeHead.id 
			|| intersectionEventArgs.TransformComponent2()->id == snakeHead.id) {
			this->SpawnFood();
		}
	}
};

#endif // FOOD_ACTIONS_H