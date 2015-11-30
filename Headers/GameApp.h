//
// Created by Julian  on 17/11/15.
//

#ifndef SDL_RTS_GAMEAPP_H
#define SDL_RTS_GAMEAPP_H

#include "Graphics.h"
#include "Transforms/IEntityTransform.h"

class GameApp
{

private:

    int windowHeight;
    int windowWidth;
    std::string appName;

    Graphics* graphics;
    ComponentSpecs* componentSpecs;

    std::vector<IEntityTransform*> entityTransforms;

    std::vector<Entity*> entityList;

    std::vector<BaseComponent*> graphicsComponents;
    std::vector<BaseComponent*> transformComponents;

public:

    GameApp();
    ~GameApp();

    bool Run();
};


#endif //SDL_RTS_GAMEAPP_H
