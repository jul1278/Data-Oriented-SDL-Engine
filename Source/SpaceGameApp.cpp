//
// Created by Julian  on 17/11/15.
//

#include <time.h>
#include <stdlib.h>
#include <memory>
#include <SpaceGame\SpaceGameApp.h>
#include <GraphicsResources\RectGraphicsResource.h>
#include <GraphicsResources\StarGraphicsResource.h>
#include <GraphicsResources\ProceduralAsteroidGraphicsResource.h>

#include <ComponentCollectionRepository.h>
#include <Components\SimplePhysicsComponent.h>
#include <SpaceGame\SpaceGameEntityConstructor.h>
#include <Utility\MathUtility.h>
#include <Actions/AsteroidAction.h>
#include <Actions/PlayerSpaceshipAction.h>
#include <Actions/BackgroundStarsAction.h>

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
	this->physics = new Physics(this->windowWidth, this->windowHeight); 

	this->sdlEventCollector = new SDLEventCollector();

	auto spaceShipGraphicResId = this->graphics->LoadGraphicResource("Resources//space_ship.png", "spaceShip");
	auto projectileGraphicResId = this->graphics->AddGraphicsResource(new RectGraphicsResource(2.0f, 12.0f, 0xff, 0xff, 0x00, 0x00));
	auto starGraphicResId = this->graphics->AddGraphicsResource(new StarGraphicsResource(5.0f, 2.5f, 0xff, 0x5f, 0x5f, 0x5f)); 
	auto enemyTriangleResId = this->graphics->LoadGraphicResource("Resources//enemy_triangle.png", "enemyTriangle");

	vector<int> asteroidGraphicsResIds;

	for (auto i = 0; i < 5; i++) {
		asteroidGraphicsResIds.push_back(this->graphics->AddGraphicsResource(new ProceduralAsteroidGraphicsResource(20.0f, 1.2f, 10)));
	}
	
	SpaceGameEntityConstructor::ConstructBackgroundStars(this->componentCollectionRepository, starGraphicResId, this->windowWidth, this->windowHeight, 20); 
	SpaceGameEntityConstructor::ConstructPlayerSpaceShip(this->componentCollectionRepository, spaceShipGraphicResId, Vector2D(this->windowWidth/2.0f, this->windowHeight - 60)); 
	SpaceGameEntityConstructor::ConstructEnemyAsteroids(this->componentCollectionRepository, asteroidGraphicsResIds, this->windowWidth, this->windowHeight, 4); 
	
	// Actions
	this->actions.push_back(new AsteroidAction(this->windowWidth, this->windowHeight)); 
	this->actions.push_back(new PlayerSpaceshipAction(this->windowHeight, this->windowWidth, this->sdlEventCollector)); 
	this->actions.push_back(new BackgroundStarsAction(this->windowWidth, this->windowHeight)); 

	this->graphics->PrintConsoleText("Hello! Welcome to " + this->appName);
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

	for (auto action : this->actions) {
		delete action; 
	}
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
		//SDL_Event(&event);

		//if (event.type == SDL_QUIT) {
		//	break;
		//}

		auto starTransformComponents = this->componentCollectionRepository->SelectFromCollection<TransformComponent>("ScrollingBackgroundStars");
		auto starGraphicsComponents = this->componentCollectionRepository->SelectFromCollection<GraphicsComponent>("ScrollingBackgroundStars");
		
		auto playerTransformComponents = this->componentCollectionRepository->SelectFromCollection<TransformComponent>("PlayerSpaceShip");
		auto playerGraphicsComponents = this->componentCollectionRepository->SelectFromCollection<GraphicsComponent>("PlayerSpaceShip");
		
		auto asteroidTransformComponents = this->componentCollectionRepository->SelectFromCollection<TransformComponent>("EnemyAsteroids"); 
		auto asteroidGraphicsComponents = this->componentCollectionRepository->SelectFromCollection<GraphicsComponent>("EnemyAsteroids"); 

		for (auto action : this->actions) {
			action->Update(this->componentCollectionRepository); 
		}

		//for_each(this->actions.begin(), this->actions.end(), [this](IAction* action){action->Update(this->componentCollectionRepository); });

		this->graphics->Clear();

		this->graphics->UpdateGraphics(starGraphicsComponents, starTransformComponents); 
		this->graphics->UpdateGraphics(asteroidGraphicsComponents, asteroidTransformComponents); 
		this->graphics->UpdateGraphics(playerGraphicsComponents, playerTransformComponents);

		this->graphics->Present(); 
	}

	return false; 
}


