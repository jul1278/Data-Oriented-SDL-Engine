//
// Created by Julian  on 17/11/15.
//

#ifndef SDL_RTS_GAMEAPP_H
#define SDL_RTS_GAMEAPP_H

#include "Graphics.h"

const float PI = 3.1415927;

class GameApp
{

private:

    int windowHeight;
    int windowWidth;
    std::string appName;

    Graphics* graphics;

    std::vector<GraphicsComponent> graphicsComponents;
    std::vector<TransformComponent> transformComponents;

public:

    GameApp();
    ~GameApp();

    int Run();
};


#endif //SDL_RTS_GAMEAPP_H
