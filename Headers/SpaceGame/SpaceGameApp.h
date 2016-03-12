//
// Created by Julian  on 17/11/15.
//
#ifndef SPACE_GAME_APP_H
#define SPACE_GAME_APP_H

#include "IAction.h"
#include "Graphics.h"
#include "ComponentCollectionRepository.h"
#include "Events\SDLEventCollector.h"
#include "Physics.h"

#include <typeindex>

class SpaceGameApp
{
private:

	int windowHeight;
	int windowWidth;
	std::string appName;

	ComponentCollectionRepository* componentCollectionRepository; 
	
	Graphics* graphics; 
	Physics* physics; 

	SDLEventCollector* sdlEventCollector;

public:

	SpaceGameApp();
	~SpaceGameApp();

	bool Run();

};

#endif 