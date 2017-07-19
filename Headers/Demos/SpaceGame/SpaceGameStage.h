#ifndef SPACE_GAME_STAGE_H
#define SPACE_GAME_STAGE_H

#include "Components/Repository/ComponentRepository.h"
#include "Game/IStage.h"
#include "Graphics/Camera.h"
#include "Demos/SpaceGame/BackgroundStarsAction.h"
#include "Demos/SpaceGame/PlayerSpaceshipAction.h"
#include "Demos/SpaceGame/AsteroidAction.h"
#include "Actions/IAction.h"
#include "Events/QuitApplicationEventArgs.h"
#include "Utility/Vector.h"

class SpaceGameStage : public IStage
{

	int stageWidth; 
	int stageHeight; 

	SDLEventCollector* sdlEventCollector;
	Camera* camera;

public:

	explicit SpaceGameStage(IGameApp* gameApp) : IStage(gameApp, new ComponentRepository("SpaceGameStage"),
		new Physics(gameApp->GetGraphics()->WindowWidth(), gameApp->GetGraphics()->WindowHeight()))
	{
		auto graphics = this->GetGameApp()->GetGraphics(); 

		this->stageHeight = graphics->WindowHeight(); 
		this->stageWidth = graphics->WindowWidth(); 

		this->sdlEventCollector = new SDLEventCollector(this->stageWidth, this->stageHeight);
		this->camera = new Camera(Vector2D(this->stageWidth, this->stageHeight), Vector2D(), this->GetComponentRepository(), graphics);

		// Actions
		this->InsertAction(new AsteroidAction(this));
		this->InsertAction(new PlayerSpaceshipAction(this));
		this->InsertAction(new BackgroundStarsAction(this));

		this->camera->InsertCollection("ScrollingBackgroundStars");
		this->camera->InsertCollection("PlayerSpaceShip");
		this->camera->InsertCollection("EnemyAsteroids");
		this->camera->InsertCollection("PlayerSpaceShipProjectiles");
		this->camera->InsertCollection("PlayerHealthBar"); 

		graphics->AddCamera(this->camera);
	}

	~SpaceGameStage()
	{
		delete this->sdlEventCollector; 
	}

	void Update() override final
	{
		// Warning! don't call this here otherwise actions wont get events - they'll be lost here.
		// Issue 58 addresses this.
		//this->sdlEventCollector->Update();

		// TODO: Shouldn't really have to call this? IStage should call this.
		this->GetPhysics()->ExecuteTasks(this->GetComponentRepository()); 

		// call base class update first
		IStage::Update(); 

		auto graphics = this->GetGameApp()->GetGraphics();

		graphics->Clear();
		graphics->RenderCameras();
		graphics->Present();
	}
};

#endif // SPACE_GAME_STAGE_H