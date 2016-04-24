#ifndef INTERSECTION_COMPONENT
#define INTERSECTION_COMPONENT

#include "Components/BaseComponent.h"
#include "Components/TransformComponent.h"

struct IntersectionComponent : public BaseComponent
{
	Vector2D size;
	TransformComponent* transfromComponent;

	IntersectionComponent(): transfromComponent(nullptr) {}
};

#endif // INTERSECTION_COMPONENT