//
// Created by Julian  on 17/11/15.
//
#ifndef FUN_TEST_GAME_APP_H
#define FUN_TEST_GAME_APP_H

#include "Game/IGameApp.h"
#include "Demos\FunTest\FunTestMenuStage.h"

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG

#ifdef _DEBUG
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#endif
#endif

class FunTestGameApp : public IGameApp
{

private:

	int windowHeight;
	int windowWidth;
	string appName;

	Graphics* graphics;

	IStage* funTestMenuStage;

public:

	FunTestGameApp()
	{
		this->windowHeight = 480;
		this->windowWidth = 480;
		this->appName = "Fun Test App Thing";

		this->graphics = new Graphics(this->windowWidth, this->windowHeight, this->appName);

		this->funTestMenuStage = new FunTestMenuStage(this);
		
		this->PushStage(this->funTestMenuStage);
	}

	~FunTestGameApp()
	{
		delete this->graphics;
		delete this->funTestMenuStage; 
	}

	Graphics* GetGraphics() override final
	{
		return this->graphics; 
	}
};

#endif 
