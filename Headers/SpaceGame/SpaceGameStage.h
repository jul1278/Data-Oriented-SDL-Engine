#ifndef SPACE_GAME_STAGE_H
#define SPACE_GAME_STAGE_H

#include "Game/IStage.h"
#include "SpaceGame/BackgroundStarsAction.h"
#include "SpaceGame/PlayerSpaceshipAction.h"
#include "SpaceGame/AsteroidAction.h"
#include "SpaceGameEntityConstructor.h"
#include "Graphics/ProceduralAsteroidGraphicsResource.h"
#include "Graphics/StarGraphicsResource.h"
#include "Graphics/RectGraphicsResource.h"
#include "Actions/IAction.h"

class SpaceGameStage : public IStage
{
private:

	int stageWidth; 
	int stageHeight; 

	SDLEventCollector* sdlEventCollector; 

	list<IAction*> actions;

public:

	explicit SpaceGameStage(IGameApp* gameApp)
	{
		auto graphics = gameApp->GetGraphics();
		auto componentCollectionRepository = gameApp->GetComponentCollectionRepository(); 

		this->sdlEventCollector = new SDLEventCollector(); 

		this->stageHeight = graphics->WindowHeight(); 
		this->stageWidth = graphics->WindowWidth(); 

		auto spaceShipGraphicResId = graphics->LoadGraphicResource("Resources//space_ship.png", "spaceShip");
		auto projectileGraphicResId = graphics->AddGraphicsResource(new RectGraphicsResource(2.0f, 12.0f, 0xff, 0xff, 0x00, 0x00));
		auto starGraphicResId = graphics->AddGraphicsResource(new StarGraphicsResource(5.0f, 2.5f, 0xff, 0x5f, 0x5f, 0x5f));
		auto enemyTriangleResId = graphics->LoadGraphicResource("Resources//enemy_triangle.png", "enemyTriangle");

		vector<int> asteroidGraphicsResIds;

		for (auto i = 0; i < 5; i++) {
			asteroidGraphicsResIds.push_back(graphics->AddGraphicsResource(new ProceduralAsteroidGraphicsResource(20.0f, 1.2f, 10)));
		}

		SpaceGameEntityConstructor::ConstructBackgroundStars(componentCollectionRepository, starGraphicResId, this->stageWidth, this->stageHeight, 20);
		SpaceGameEntityConstructor::ConstructPlayerSpaceShip(componentCollectionRepository, spaceShipGraphicResId, Vector2D(this->stageWidth / 2.0f, this->stageHeight - 60));
		SpaceGameEntityConstructor::ConstructEnemyAsteroids(componentCollectionRepository, asteroidGraphicsResIds, this->stageWidth, this->stageHeight, 4);

		// Actions
		this->actions.push_back(new AsteroidAction(this->stageWidth, this->stageHeight));
		this->actions.push_back(new PlayerSpaceshipAction(this->stageHeight, this->stageWidth, this->sdlEventCollector));
		this->actions.push_back(new BackgroundStarsAction(this->stageWidth, this->stageHeight));
	}

	void Update(IGameApp* gameApp) override final
	{
		auto graphics = gameApp->GetGraphics();
		auto componentCollectionRepository = gameApp->GetComponentCollectionRepository();

		auto starTransformComponents = componentCollectionRepository->SelectFromCollection<TransformComponent>("ScrollingBackgroundStars");
		auto starGraphicsComponents = componentCollectionRepository->SelectFromCollection<GraphicsComponent>("ScrollingBackgroundStars");

		auto playerTransformComponents = componentCollectionRepository->SelectFromCollection<TransformComponent>("PlayerSpaceShip");
		auto playerGraphicsComponents = componentCollectionRepository->SelectFromCollection<GraphicsComponent>("PlayerSpaceShip");

		auto asteroidTransformComponents = componentCollectionRepository->SelectFromCollection<TransformComponent>("EnemyAsteroids");
		auto asteroidGraphicsComponents = componentCollectionRepository->SelectFromCollection<GraphicsComponent>("EnemyAsteroids");

		for_each(this->actions.begin(), this->actions.end(), [this, componentCollectionRepository](IAction* action) {
			         action->Update(componentCollectionRepository);
		         });

		graphics->Clear();

		graphics->UpdateGraphics(starGraphicsComponents, starTransformComponents);
		graphics->UpdateGraphics(asteroidGraphicsComponents, asteroidTransformComponents);
		graphics->UpdateGraphics(playerGraphicsComponents, playerTransformComponents);

		graphics->Present();
	}
};

#endif // SPACE_GAME_STAGE_H