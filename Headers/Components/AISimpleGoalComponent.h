#ifndef AI_SIMPLE_GOAL_COMPONENT_H
#define AI_SIMPLE_GOAL_COMPONENT_H

#include "BaseComponent.h"
#include <Utility/Vector.h>

struct AiSimpleGoalComponent : public BaseComponent
{
	Vector2D goal;

	explicit AiSimpleGoalComponent(Vector2D goal) : goal(goal)
	{}

	AiSimpleGoalComponent() : goal(Vector2D(0.0f))
	{}
};

#endif // AI_SIMPLE_GOAL_COMPONENT_H