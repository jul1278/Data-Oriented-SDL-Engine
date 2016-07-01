#ifndef PLAYER_SPACE_SHIP_ACTION_H
#define PLAYER_SPACE_SHIP_ACTION_H

#include "Actions/IAction.h"
#include "Game/IGameApp.h"
#include "Events/SDLEventCollector.h"
#include "Components/PhysicsComponent.h"
#include "Graphics/Graphics.h"
#include "SpaceGameEntityConstructor.h"
#include <Events/ButtonEventArgs.h>
#include <Physics/CollisionPhysicsTask.h>
#include <Graphics/RectGraphicsResource.h>

class PlayerSpaceshipAction : public IAction
{
private:

	unsigned int width; 
	unsigned int height; 

	SDLEventCollector* sdlEventCollector;

	unsigned int moveCounter;
	int projectileGraphicResId;
	
	void MoveSpaceShip(const ButtonEventArgs& buttonEventArgs) const;
	void FireWeapon(const ButtonEventArgs buttonEventArgs) const;
	void OnButtonEvent(const ButtonEventArgs& buttonEventArgs) const;

	void OnPlayerAsteroidCollision(const CollisionEventArgs& collisionEventArgs) const;
	void OnProjectileAsteroidCollision(const CollisionEventArgs& collisionEventArgs) const; 

public:

	PlayerSpaceshipAction(IStage* stage);

	void Update() override final 
	{
		this->sdlEventCollector->Update(); 

		auto componentCollectionRepository = this->GetParentStage()->GetComponentCollectionRepository();
		auto projectileGraphics = componentCollectionRepository->SelectFromCollection<GraphicsComponent>("PlayerSpaceShipProjectiles");

		for (auto graphicsComponent : *projectileGraphics) {
			auto transform = componentCollectionRepository->Select<TransformComponent>(graphicsComponent.transformComponentId);
			
			if (transform->position.x > this->width || transform->position.x < 0) {
				if (transform->position.y > this->height || transform->position.y < 0) {
					componentCollectionRepository->RemoveEntity(graphicsComponent.entityId); 
				}
			}
		}
	}
};

#endif // PLAYER_SPACE_SHIP_ACTION_H