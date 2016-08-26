#ifndef BACKGROUND_STARS_ACTION_H
#define BACKGROUND_STARS_ACTION_H

#include "Actions/IAction.h"
#include "Utility/MathUtility.h"
#include "Components/VelocityComponent.h"
#include "Game/IGameApp.h"
#include "SpaceGameEntityConstructor.h"
#include <Graphics/StarGraphicsResource.h>
#include <Graphics/Graphics.h>

class BackgroundStarsAction : public IAction
{
private:

	unsigned int width; 
	unsigned int height; 

public:

	BackgroundStarsAction(IStage* stage) : IAction(stage)
	{
		auto graphics = this->GetParentStage()->GetGameApp()->GetGraphics();

		this->width = graphics->WindowWidth(); 
		this->height = graphics->WindowHeight();

		auto starGraphicResId = graphics->AddGraphicsResource(new StarGraphicsResource(5.0f, 2.5f, Color(Color::DarkGray)));
		
		SpaceGameEntityConstructor::ConstructBackgroundStars(this->GetParentStage()->GetComponentRepository(), starGraphicResId, this->width, this->height, 20);
	}

	void Update() override final
	{
		auto componentRepository = this->GetParentStage()->GetComponentRepository(); 

		auto starPhysicsComponents = componentRepository->Select<VelocityComponent>("ScrollingBackgroundStars");
		auto starTransformComponents = componentRepository->Select<TransformComponent>("ScrollingBackgroundStars"); 

		// star background loop
		for (auto physicsComponent : starPhysicsComponents) {

			auto id = physicsComponent.transformComponentId; 
			auto transformComponent = componentRepository->SelectId<TransformComponent>(id); 

			transformComponent->position.y += physicsComponent.velocity.y;

			if (transformComponent->position.y > this->height) {

				transformComponent->position.y = 0.0f;
				transformComponent->position.x = this->width * MathUtility::RandomFloatUniformDist();
			}
		}
	}
};

#endif // BACKGROUND_STARS_ACTION_H