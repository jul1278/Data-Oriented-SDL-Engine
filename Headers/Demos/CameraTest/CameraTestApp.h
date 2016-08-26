#ifndef CAMERA_TEST_APP_H
#define CAMERA_TEST_APP_H

#include "Game/IGameApp.h"
#include "Components/Repository/componentRepository.h"
#include "Graphics/Camera.h"
#include "Graphics/StarGraphicsResource.h"
#include "Graphics/CameraTestStage.h"
#include "Graphics/MouseCameraTransform.h"
#include "Graphics/GridGraphicsResource.h"

class CameraTestApp : public IGameApp
{
	int windowHeight;
	int windowWidth;
	std::string appName;

	SDLEventCollector* sdlEventCollector;

	Graphics* graphics;
	componentRepository* componentRepository; 
	IStage* cameraTestStage;

	MouseCameraTransform* mouseCameraTransform; 

	Camera* camera; 

public:

	CameraTestApp()
	{
		this->sdlEventCollector = new SDLEventCollector(500, 500); 
		this->componentRepository = new componentRepository();
		this->graphics = new Graphics(500, 500, "CameraTest"); 
		
		this->mouseCameraTransform = new MouseCameraTransform(this->sdlEventCollector);

		this->camera = new Camera(Vector2D(500.0f, 500.0f), Vector2D(0.0f, 0.0f), this->componentRepository, this->graphics); 

		auto graphicResourceId = this->graphics->AddGraphicsResource(new StarGraphicsResource(10.0f, 5.0f, 0xff, 0xff, 0xff, 0xff)); 
		auto gridResourceId = this->graphics->AddGraphicsResource(new GridGraphicsResource(20.0f, 50, 50, 0xff, 0xff, 0xff, 0xff)); 

		this->componentRepository->NewCollection("CameraTestComponents");
		auto transform = this->componentRepository->NewComponent<TransformComponent>("CameraTestComponents"); 
		auto graphicComponent = this->componentRepository->NewComponent<GraphicsComponent>("CameraTestComponents"); 

		auto transformGrid = this->componentRepository->NewComponent<TransformComponent>("CameraTestComponents");
		auto graphicComponentGrid = this->componentRepository->NewComponent<GraphicsComponent>("CameraTestComponents");

		transformGrid->position = Vector2D(0.0f, 0.0f); 
		graphicComponentGrid->transformComponent = transformGrid;
		graphicComponentGrid->resourceId = gridResourceId; 

		transform->position = Vector2D(250.0f, 250.0f); 

		graphicComponent->transformComponent = transform; 
		graphicComponent->resourceId = graphicResourceId; 

		this->camera->InsertCollection("CameraTestComponents");
		this->camera->InsertTransformParent(this->mouseCameraTransform);

		this->graphics->AddCamera(this->camera); 

		this->PushStage(new CameraTestStage(this, this->componentRepository, nullptr, this->sdlEventCollector));
	}

	~CameraTestApp()
	{
		delete this->componentRepository;
	}

	Graphics* GetGraphics() override final
	{
		return this->graphics; 
	}
};


#endif // CAMERA_TEST_APP_H