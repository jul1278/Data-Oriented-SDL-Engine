//
// Created by Julian  on 17/11/15.
//

#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "Graphics.h"
#include "Components/ComponentRepository.h"


class GameApp
{

private:

    int windowHeight;
    int windowWidth;
    std::string appName;

    Graphics* graphics;	
	ComponentRepository* componentRepository; 

public:

    GameApp();
    ~GameApp();

    bool Run();
};


#endif //GAMEAPP_H
