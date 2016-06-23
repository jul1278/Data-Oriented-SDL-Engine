#ifndef SPACE_GAME_STAGE_H
#define SPACE_GAME_STAGE_H

#include "Game/IStage.h"
#include "SpaceGame/BackgroundStarsAction.h"
#include "SpaceGame/PlayerSpaceshipAction.h"
#include "SpaceGame/AsteroidAction.h"
#include "Actions/IAction.h"

class SpaceGameStage : public IStage
{

	int stageWidth; 
	int stageHeight; 

	SDLEventCollector* sdlEventCollector; 

public:

	explicit SpaceGameStage(IGameApp* gameApp) : IStage(gameApp, new ComponentCollectionRepository,
		new Physics(gameApp->GetGraphics()->WindowWidth(), gameApp->GetGraphics()->WindowHeight()))
	{
		auto graphics = this->GetGameApp()->GetGraphics(); 

		this->stageHeight = graphics->WindowHeight(); 
		this->stageWidth = graphics->WindowWidth(); 

		this->sdlEventCollector = new SDLEventCollector(this->stageWidth, this->stageHeight); 

		// Actions
		this->InsertAction(new AsteroidAction(this));
		this->InsertAction(new PlayerSpaceshipAction(this));
		this->InsertAction(new BackgroundStarsAction(this));
	}

	~SpaceGameStage()
	{
		delete this->sdlEventCollector; 
	}

	void Update() override final
	{
		//this->sdlEventCollector->Update();
		this->GetPhysics()->ExecuteTasks(this->GetComponentCollectionRepository()); 

		// call base class update first
		IStage::Update(); 

		auto graphics = this->GetGameApp()->GetGraphics();
		auto componentCollectionRepository = this->GetComponentCollectionRepository();

		auto starTransformComponents = componentCollectionRepository->SelectFromCollection<TransformComponent>("ScrollingBackgroundStars");
		auto starGraphicsComponents = componentCollectionRepository->SelectFromCollection<GraphicsComponent>("ScrollingBackgroundStars");

		auto playerTransformComponents = componentCollectionRepository->SelectFromCollection<TransformComponent>("PlayerSpaceShip");
		auto playerGraphicsComponents = componentCollectionRepository->SelectFromCollection<GraphicsComponent>("PlayerSpaceShip");

		auto asteroidTransformComponents = componentCollectionRepository->SelectFromCollection<TransformComponent>("EnemyAsteroids");
		auto asteroidGraphicsComponents = componentCollectionRepository->SelectFromCollection<GraphicsComponent>("EnemyAsteroids");

		auto projectileTransformComponents = componentCollectionRepository->SelectFromCollection<TransformComponent>("PlayerSpaceShipProjectiles");
		auto projectileGraphicsComponents = componentCollectionRepository->SelectFromCollection<GraphicsComponent>("PlayerSpaceShipProjectiles"); 

		graphics->Clear();

		graphics->UpdateGraphics(starGraphicsComponents, starTransformComponents);
		graphics->UpdateGraphics(asteroidGraphicsComponents, asteroidTransformComponents);
		graphics->UpdateGraphics(playerGraphicsComponents, playerTransformComponents);
		graphics->UpdateGraphics(projectileGraphicsComponents, projectileTransformComponents); 

		graphics->Present();
	}


};

#endif // SPACE_GAME_STAGE_H