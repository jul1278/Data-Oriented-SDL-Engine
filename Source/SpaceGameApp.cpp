//
// Created by Julian  on 17/11/15.
//

#include <time.h>
#include <stdlib.h>
#include <memory>
#include <SpaceGame\SpaceGameApp.h>
#include <typeinfo>
#include <typeindex>
#include <GraphicsResources\CircleFIllGraphicsResource.h>
#include <GraphicsResources\RectGraphicsResource.h>
#include <GraphicsResources\TriangleGraphicsResource.h>
#include <GraphicsResources\StarGraphicsResource.h>
#include <ComponentCollectionRepository.h>
#include <Components\SimplePhysicsComponent.h>
#include <Events\ButtonEventArgs.h>
#include <PlayerActions.h>
#include <SpaceGame\SpaceGameEntityConstructor.h>
#include <Utility\MathUtility.h>

//------------------------------------------------------------------------------------
// Name: SpaceGameApp
// Desc:
//------------------------------------------------------------------------------------
SpaceGameApp::SpaceGameApp()
{
	this->windowHeight = 480;
	this->windowWidth = 640;
	this->appName = "Space Game";

	this->componentCollectionRepository = new ComponentCollectionRepository; 
	this->graphics = new Graphics(this->windowWidth, this->windowHeight, this->appName);

	this->sdlEventCollector = new SDLEventCollector();

	auto spaceShipGraphicResId = this->graphics->LoadGraphicResource("Resources//space_ship.png", "spaceShip");
	auto projectileGraphicResId = this->graphics->AddGraphicsResource(new RectGraphicsResource(2.0f, 12.0f, 0xff, 0xff, 0x00, 0x00));
	auto starGraphicResId = this->graphics->AddGraphicsResource(new StarGraphicsResource(5.0f, 2.5f, 0xff, 0x5f, 0x5f, 0x5f)); 
	auto enemyTriangleResId = this->graphics->LoadGraphicResource("Resources//enemy_triangle.png", "enemyTriangle");

	SpaceGameEntityConstructor::ConstructBackgroundStars(this->componentCollectionRepository, starGraphicResId, this->windowWidth, this->windowHeight, 20); 
	SpaceGameEntityConstructor::ConstructPlayerSpaceShip(this->componentCollectionRepository, spaceShipGraphicResId, Vector2D(this->windowWidth/2.0f, this->windowHeight - 60)); 
}
//------------------------------------------------------------------------------------
// Name: ~SpaceGameApp
// Desc:
//------------------------------------------------------------------------------------
SpaceGameApp::~SpaceGameApp()
{
	// delet
	delete this->componentCollectionRepository; 
	delete this->graphics; 
}
//------------------------------------------------------------------------------------
// Name: SpaceGameApp
// Desc:
//------------------------------------------------------------------------------------
bool SpaceGameApp::Run()
{
	while (1)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT) {
			break;
		}

		auto starTransformComponents = this->componentCollectionRepository->SelectFromCollection<TransformComponent>("ScrollingBackgroundStars");
		auto starGraphicsComponents = this->componentCollectionRepository->SelectFromCollection<GraphicsComponent>("ScrollingBackgroundStars");
		auto starPhysicsComponents = this->componentCollectionRepository->SelectFromCollection<SimplePhysicsComponent>("ScrollingBackgroundStars");

		auto playerTransformComponents = this->componentCollectionRepository->SelectFromCollection<TransformComponent>("PlayerSpaceShip");
		auto playerGraphicsComponents = this->componentCollectionRepository->SelectFromCollection<GraphicsComponent>("PlayerSpaceShip");
		auto playerPhysicsComponents = this->componentCollectionRepository->SelectFromCollection<SimplePhysicsComponent>("PlayerSpaceShip");

		// player loop
		// TODO: move this out of here
		if (((event.type == SDL_KEYDOWN) || (event.type == SDL_KEYUP))) {

			for (auto physicsComponent : *playerPhysicsComponents) {
				
				if (physicsComponent.transformComponent->position.y < (this->windowHeight - 60)) {
					physicsComponent.velocity.y = 1.0f; 
				} else {
					physicsComponent.velocity.y = 0.0f; 
				}

				if ((event.key.keysym.sym == SDLK_LEFT) && (event.type == SDL_KEYDOWN)) {

					if (physicsComponent.transformComponent->position.x > 25) {
						physicsComponent.velocity = Vector2D(-4.0f, 0.0f);
					}

				} else if ((event.key.keysym.sym == SDLK_RIGHT) && (event.type == SDL_KEYDOWN)) {
					
					if (physicsComponent.transformComponent->position.x < (this->windowWidth - 50)) {
						physicsComponent.velocity = Vector2D(4.0f, 0.0f);
					}

				} else if ((event.key.keysym.sym == SDLK_UP) && (event.type == SDL_KEYDOWN)) {
					
					if (physicsComponent.transformComponent->position.y > 25) {
						physicsComponent.velocity = Vector2D(0.0f, -4.0f); 
					}
				} else if ((event.key.keysym.sym == SDLK_DOWN) && (event.type == SDL_KEYDOWN)) {
					
					if (physicsComponent.transformComponent->position.y < (this->windowHeight - 60)) {
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

		// star background loop
		for (auto physicsComponent : *starPhysicsComponents) {
			physicsComponent.transformComponent->position.y += physicsComponent.velocity.y; 

			if (physicsComponent.transformComponent->position.y > this->windowHeight) {
				physicsComponent.transformComponent->position.y = 0.0f; 
				physicsComponent.transformComponent->position.x = this->windowWidth * MathUtility::RandomFloatUniformDist(); 
			}
		}

		this->graphics->Clear();

		this->graphics->UpdateGraphics(starGraphicsComponents, starTransformComponents); 
		this->graphics->UpdateGraphics(playerGraphicsComponents, playerTransformComponents);
		
		this->graphics->Present(); 
	}

	return false; 
}


