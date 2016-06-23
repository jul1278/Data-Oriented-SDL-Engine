//
// Created by Julian  on 17/11/15.
//
#ifndef SPACE_GAME_APP_H
#define SPACE_GAME_APP_H

#include "Game\IGameApp.h"

class SpaceGameApp : public IGameApp
{

private:

	int windowHeight;
	int windowWidth;
	std::string appName;

	Graphics* graphics; 
	
	IStage* spaceGameStage;
	IStage* spaceGameMenu;

public:

	SpaceGameApp();
	~SpaceGameApp();

	Graphics* GetGraphics() override final;
};

#endif 