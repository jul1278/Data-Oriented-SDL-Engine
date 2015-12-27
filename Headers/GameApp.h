//
// Created by Julian  on 17/11/15.
//

#ifndef SDL_RTS_GAMEAPP_H
#define SDL_RTS_GAMEAPP_H

#include "Graphics.h"


class GameApp
{

private:

    int windowHeight;
    int windowWidth;
    std::string appName;

    Graphics* graphics;

    std::vector<IBaseComponent*> graphicsComponents;
    std::vector<IBaseComponent*> transformComponents;

public:

    GameApp();
    ~GameApp();

    bool Run();
};


#endif //SDL_RTS_GAMEAPP_H
