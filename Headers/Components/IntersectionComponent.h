#ifndef INTERSECTION_COMPONENT
#define INTERSECTION_COMPONENT

#include "Components/BaseComponent.h"
#include <Utility/Vector.h>

struct IntersectionComponent : public BaseComponent
{
	Vector2D size;
	unsigned int transformComponentId;

	IntersectionComponent()
	{
		this->transformComponentId = 0; 
	}
};

#endif // INTERSECTION_COMPONENT