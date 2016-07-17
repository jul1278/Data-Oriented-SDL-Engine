#ifndef PLAYER_SPACE_SHIP_ACTION_H
#define PLAYER_SPACE_SHIP_ACTION_H

#include "Actions/IAction.h"
#include "Game/IGameApp.h"
#include "Events/SDLEventCollector.h"
#include "Components/PhysicsComponent.h"
#include "Graphics/Graphics.h"
#include "SpaceGameEntityConstructor.h"
#include "Events/ButtonEventArgs.h"
#include "Physics/CollisionPhysicsTask.h"
#include "Graphics/RectGraphicsResource.h"
#include "Events/QuitApplicationEventArgs.h"

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

	void OnQuitApplication(const QuitApplicationEventArgs& quitApplicationEventArgs)
	{
		// TODO: this won't work if there are more than one stage..
		// unless the quit event goes to the other stages as well
		this->GetParentStage()->GetGameApp()->PopStage();
	}

public:

	PlayerSpaceshipAction(IStage* stage);

	void Update() override final 
	{
		this->sdlEventCollector->Update(); 

		auto componentCollectionRepository = this->GetParentStage()->GetComponentCollectionRepository();
		auto projectileGraphics = componentCollectionRepository->SelectFromCollection<GraphicsComponent>("PlayerSpaceShipProjectiles");

		if (projectileGraphics == nullptr || projectileGraphics->size() == 0) {
			return; 
		}

		for (auto graphicsComponent : *projectileGraphics) {
			auto transform = componentCollectionRepository->Select<TransformComponent>(graphicsComponent.transformComponentId);
			
			if (transform == nullptr) {
				continue; 
			}

			if (transform->position.x > this->width || 
				transform->position.x < 0.0f || 
				transform->position.y > this->height || 
				transform->position.y < 0.0f) {

				componentCollectionRepository->RemoveEntity(graphicsComponent.entityId); 
			}
		}
	}
};

#endif // PLAYER_SPACE_SHIP_ACTION_H