//
// Created by Julian  on 17/11/15.
//
#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "IAction.h"
#include "Graphics.h"
#include "ComponentRepository.h"
#include "Events\SDLEventCollector.h"

#include <typeindex>


class GameApp
{

private:

    int windowHeight;
    int windowWidth;
    std::string appName;

    Graphics* graphics;	
	ComponentRepository* componentRepository; 

	unordered_map<type_index, IAction*> eventMap; 

	SDLEventCollector* sdlEventCollector; 

public:

    GameApp();
    ~GameApp();

    bool Run();
};


#endif //GAMEAPP_H
