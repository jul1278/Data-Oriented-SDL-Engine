#ifndef CAMERA_H
#define CAMERA_H

#include "Graphics.h"
#include <Utility/Vector.h>
#include <Events/SDLEventCollector.h>
#include "Events/MouseMotionEventArgs.h"
#include <Components/TransformComponent.h>
#include <Components/GraphicsComponent.h>
#include <Components/ComponentCollectionRepository.h>
#include "ITransform.h"

class Camera
{
private:
	
	ComponentCollectionRepository* componentCollectionRepository;
	Graphics* graphics; 

	list<string> renderCollections; 

	ITransform* transform;

public:

	Camera(Vector2D size, Vector2D position, ComponentCollectionRepository* componentCollectionRepository, Graphics* graphics)
	{
		this->componentCollectionRepository = componentCollectionRepository; 
		this->graphics = graphics; 
	}
	
	// names of collections we want to render onto this camera
	void InsertCollection(string collection)
	{
		if (find(renderCollections.begin(), renderCollections.end(), collection) == renderCollections.end()) {
			this->renderCollections.push_back(collection);
		}
	}

	void InsertTransformParent(ITransform* transform)
	{
		this->transform = transform; 
	}

	void Render()
	{
		for (auto collection : this->renderCollections) {
			
			auto graphicComponents = this->componentCollectionRepository->SelectFromCollection<GraphicsComponent>(collection);
			auto transformComponents = this->componentCollectionRepository->SelectFromCollection<TransformComponent>(collection); 

			auto p = (*transform)(); 

			this->graphics->UpdateGraphics(graphicComponents, transformComponents, p);
		}
	}
};

#endif // CAMERA_H