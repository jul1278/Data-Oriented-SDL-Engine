#ifndef PLAYER_SPACE_SHIP_ACTION_H
#define PLAYER_SPACE_SHIP_ACTION_H

#include "Actions/IAction.h"
#include "Game/IGameApp.h"
#include "Events/SDLEventCollector.h"
#include "Components/PhysicsComponent.h"

class PlayerSpaceshipAction : public IAction
{
private:

	unsigned int width; 
	unsigned int height; 
	SDLEventCollector* sdlEventCollector;

	unsigned int moveCounter; 

public:

	PlayerSpaceshipAction(unsigned int height, unsigned int width, SDLEventCollector* slEventCollector)
	{
		this->width = width;
		this->height = height; 
		this->sdlEventCollector = sdlEventCollector;

		this->moveCounter = 0; 
	}
	
	void Update(IGameApp* gameApp) override final
	{
		auto componentCollectionRepository = gameApp->GetComponentCollectionRepository(); 

		if (this->CheckAsteroidCollision(componentCollectionRepository)) {
			// end game
		} else {
			this->PlayerControlSpaceship(componentCollectionRepository);
		}
	}

	void PlayerControlSpaceship(ComponentCollectionRepository* componentCollectionRepository) const 
	{
		auto playerPhysicsComponents = componentCollectionRepository->SelectFromCollection<PhysicsComponent>("PlayerSpaceShip");

		// TODO: get this from SDLEventCollector
		SDL_Event event;
		SDL_PollEvent(&event);

		if (((event.type == SDL_KEYDOWN) || (event.type == SDL_KEYUP)  )) {

			for (auto physicsComponent : *playerPhysicsComponents) {

				if (physicsComponent.transformComponent->position.y < (this->height - 60)) {
					physicsComponent.velocity.y = 1.0f;
				}
				else {
					physicsComponent.velocity.y = 0.0f;
				}

				if ((event.key.keysym.sym == SDLK_LEFT) && (event.type == SDL_KEYDOWN)) {

					if (physicsComponent.transformComponent->position.x > 25) {
						physicsComponent.velocity = Vector2D(-4.0f, 0.0f);
					}
				}
				else if ((event.key.keysym.sym == SDLK_RIGHT) && (event.type == SDL_KEYDOWN)) {

					if (physicsComponent.transformComponent->position.x < (this->width - 50)) {
						physicsComponent.velocity = Vector2D(4.0f, 0.0f);
					}
				}
				else if ((event.key.keysym.sym == SDLK_UP) && (event.type == SDL_KEYDOWN)) {

					if (physicsComponent.transformComponent->position.y > 25) {
						physicsComponent.velocity = Vector2D(0.0f, -4.0f);
					}
				}
				else if ((event.key.keysym.sym == SDLK_DOWN) && (event.type == SDL_KEYDOWN)) {

					if (physicsComponent.transformComponent->position.y < (this->height - 60)) {
						physicsComponent.velocity = Vector2D(0.0f, 4.0f);
					}
				}

				if (event.type == SDL_KEYUP) {

					physicsComponent.velocity.x = 0.0f;
				}

				physicsComponent.transformComponent->position.x += physicsComponent.velocity.x;
				physicsComponent.transformComponent->position.y += physicsComponent.velocity.y;
			}
		}
	}
	
	static bool CheckAsteroidCollision(ComponentCollectionRepository* componentCollectionRepository)
	{
		auto asteroidPhysicsComponents = componentCollectionRepository->SelectFromCollection<PhysicsComponent>("EnemyAsteroids"); 
		auto playerPhysicsComponent = componentCollectionRepository->SelectFromCollection<PhysicsComponent>("PlayerSpaceShip");

		auto playerVector = playerPhysicsComponent->front().transformComponent->position; 
		auto playerSize = playerPhysicsComponent->front().radius; 

		for (auto asteroid : *asteroidPhysicsComponents) {
			
			auto diff = playerVector - asteroid.transformComponent->position; 
			auto r = playerSize + asteroid.radius; 

			if (diff.Length() < r) {
				return true; 
			}
		}
	}

};

#endif // PLAYER_SPACE_SHIP_ACTION_H