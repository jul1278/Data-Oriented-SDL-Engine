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

		auto starGraphicResId = graphics->AddGraphicsResource(new StarGraphicsResource(5.0f, 2.5f, 0xff, 0x5f, 0x5f, 0x5f));
		
		SpaceGameEntityConstructor::ConstructBackgroundStars(this->GetParentStage()->GetComponentCollectionRepository(), starGraphicResId, this->width, this->height, 20);
	}

	void Update() override final
	{
		auto componentCollectionRepository = this->GetParentStage()->GetComponentCollectionRepository(); 

		auto starPhysicsComponents = componentCollectionRepository->SelectFromCollection<VelocityComponent>("ScrollingBackgroundStars");
		auto starTransformComponents = componentCollectionRepository->SelectFromCollection<TransformComponent>("ScrollingBackgroundStars"); 

		// star background loop
		for (auto physicsComponent : *starPhysicsComponents) {

			auto id = physicsComponent.transformComponentId; 
			auto transformComponent = componentCollectionRepository->Select<TransformComponent>(id); 

			transformComponent->position.y += physicsComponent.velocity.y;

			if (transformComponent->position.y > this->height) {

				transformComponent->position.y = 0.0f;
				transformComponent->position.x = this->width * MathUtility::RandomFloatUniformDist();
			}
		}
	}
};

#endif // BACKGROUND_STARS_ACTION_H