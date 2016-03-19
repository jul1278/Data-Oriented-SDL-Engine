#ifndef BACKGROUND_STARS_ACTION_H
#define BACKGROUND_STARS_ACTION_H

#include "IAction.h"
#include <Utility/MathUtility.h>
#include <Components/SimplePhysicsComponent.h>

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

	void Update(ComponentCollectionRepository* componentCollectionRepository) override final
	{
		auto starPhysicsComponents = componentCollectionRepository->SelectFromCollection<SimplePhysicsComponent>("ScrollingBackgroundStars");

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