#ifndef MOUSE_CAMERA_TRANSFORM_H
#define MOUSE_CAMERA_TRANSFORM_H

#include "Graphics/ITransform.h"
#include <Events/MouseMotionEventArgs.h>
#include "Components/TransformComponent.h"
#include <Events/SDLEventCollector.h>
#include <Events/ButtonEventArgs.h>

class MouseCameraTransform : public ITransform
{	
private:

	SDLEventCollector* sdlEventCollector;
	TransformComponent transformComponent;

public:

	MouseCameraTransform(SDLEventCollector* sdlEventCollector)
	{
		this->sdlEventCollector = sdlEventCollector; 
		this->sdlEventCollector->RegisterListener<MouseMotionEventArgs>(bind(&MouseCameraTransform::OnMouseMotion, this, std::placeholders::_1));
	}

	~MouseCameraTransform()
	{
		// don't delete sdlEventCollector
	}

	TransformComponent* operator()(void) override
	{
		return &this->transformComponent;
	}

	void OnMouseMotion(const MouseMotionEventArgs& mouseMotionEventArgs)
	{
		if (mouseMotionEventArgs.CurrentPositionNormalized().x < 0.1f) {
			this->transformComponent.position.x += 2.0f;

		} else if (mouseMotionEventArgs.CurrentPositionNormalized().x > 0.9f) {
			this->transformComponent.position.x -= 2.0f;

		}

		if (mouseMotionEventArgs.CurrentPositionNormalized().y < 0.1f) {
			this->transformComponent.position.y -= 2.0f; 

		} else if (mouseMotionEventArgs.CurrentPositionNormalized().y > 0.9f) {
			this->transformComponent.position.y += 2.0f;

		}
	}
};


#endif // MOUSE_CAMERA_TRANSFORM_H