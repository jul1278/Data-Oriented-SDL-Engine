#ifndef CAMERA_TEST_STAGE_H
#define CAMERA_TEST_STAGE_H

#include "Game/IStage.h"

class CameraTestStage : public IStage
{
	SDLEventCollector* sdlEventCollector;
	IGameApp* gameApp; 

public:

	CameraTestStage(IGameApp* gameApp, componentRepository* componentRepository, Physics* physics, SDLEventCollector* sdlEventCollector)
		: IStage(gameApp, componentRepository, physics)
	{
		this->gameApp = gameApp; 
		this->sdlEventCollector = sdlEventCollector; 
	}

	void Update() override final
	{
		this->sdlEventCollector->Update();

		this->gameApp->GetGraphics()->Clear();
		this->gameApp->GetGraphics()->RenderCameras();
		this->gameApp->GetGraphics()->Present(); 
	}
};

#endif // CAMERA_TEST_STAGE_H