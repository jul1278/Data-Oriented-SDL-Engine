#ifndef CAMERA_H
#define CAMERA_H

#include "Graphics.h"
#include "Utility/Vector.h"
#include "Events/SDLEventCollector.h"
#include "Events/MouseMotionEventArgs.h"
#include "Components/TransformComponent.h"
#include "Components/GraphicsComponent.h"
#include "Components/Repository/ComponentRepository.h"
#include "ITransform.h"

#include <algorithm>

class Camera
{
private:
	
	ComponentRepository* componentRepository;
	Graphics* graphics; 

	list<string> renderCollections; 

	ITransform* transform;

	unsigned int shakeCounter; 
	unsigned int shakeMax; 

	TransformComponent shakeTransform; 

public:

	//------------------------------------------------------------------------------------------------
	// Name: Constructor
	// Desc:
	//------------------------------------------------------------------------------------------------
	Camera(Vector2D size, Vector2D position, ComponentRepository* componentRepository, Graphics* graphics)
	{
		this->componentRepository = componentRepository; 
		this->graphics = graphics;
        this->transform = nullptr;
		this->shakeCounter = 0; 
	}
	//------------------------------------------------------------------------------------------------
	// Name: Constructor
	// Desc:
	//------------------------------------------------------------------------------------------------
	void InsertCollection(string collection)
	{
		if (find(this->renderCollections.begin(), this->renderCollections.end(), collection) == this->renderCollections.end()) {
			this->renderCollections.push_back(collection);
		}
	}
	//------------------------------------------------------------------------------------------------
	// Name: ContainsCollection
	// Desc:
	//------------------------------------------------------------------------------------------------
	bool ContainsCollection(const string& collection)
	{
		return find(this->renderCollections.begin(), this->renderCollections.end(), collection) != this->renderCollections.end();
	}
	//------------------------------------------------------------------------------------------------
	// Name: InsertTransformParent
	// Desc:
	//------------------------------------------------------------------------------------------------
	void InsertTransformParent(ITransform* transform)
	{
		this->transform = transform; 
	}

	void Render();

	~Camera() {}
};

#endif // CAMERA_H