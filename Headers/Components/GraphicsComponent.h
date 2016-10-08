//
// Created by Julian  on 17/11/15.
//
#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H

// GraphicsComponent
struct GraphicsComponent : public BaseComponent
{
    unsigned int resourceId;
	unsigned int transformComponentId; 

	GraphicsComponent()
	{
		this->resourceId = 0;
		this->transformComponentId = 0;
	}

    GraphicsComponent(unsigned int resourceId, unsigned int transformComponentId)
    {
		this->transformComponentId = transformComponentId; 
        this->resourceId = resourceId;
    }
};

#endif //GRAPHICS_COMPONENT_H
