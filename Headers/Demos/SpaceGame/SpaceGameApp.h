//
// Created by Julian  on 17/11/15.
//
#ifndef SPACE_GAME_APP_H
#define SPACE_GAME_APP_H

#include "Game/IGameApp.h"

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

class SpaceGameApp : public IGameApp
{

private:

	int windowHeight;
	int windowWidth;
	string appName;

	Graphics* graphics; 
	
	IStage* spaceGameStage;
	IStage* spaceGameMenu;

public:

	SpaceGameApp();
	~SpaceGameApp();

	Graphics* GetGraphics() override final;
};

#endif 