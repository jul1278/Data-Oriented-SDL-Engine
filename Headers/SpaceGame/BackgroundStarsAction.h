#ifndef BACKGROUND_STARS_ACTION_H
#define BACKGROUND_STARS_ACTION_H

#include "Actions/IAction.h"
#include "Utility/MathUtility.h"
#include "Components/VelocityComponent.h"
#include "Game/IGameApp.h"

class BackgroundStarsAction : public IAction
{
private:

	unsigned int width; 
	unsigned int height; 

public:

	BackgroundStarsAction(unsigned int width, unsigned int height)
	{
		this->width = width; 
		this->height = height; 
	}

	void Update(IGameApp* gameApp) override final
	{
		auto componentCollectionRepository = gameApp->GetComponentCollectionRepository(); 

		auto starPhysicsComponents = componentCollectionRepository->SelectFromCollection<VelocityComponent>("ScrollingBackgroundStars");

		// star background loop
		for (auto physicsComponent : *starPhysicsComponents) {
			physicsComponent.transformComponent->position.y += physicsComponent.velocity.y;

			if (physicsComponent.transformComponent->position.y > this->height) {
				physicsComponent.transformComponent->position.y = 0.0f;
				physicsComponent.transformComponent->position.x = this->width * MathUtility::RandomFloatUniformDist();
			}
		}
	}
};

#endif // BACKGROUND_STARS_ACTION_H