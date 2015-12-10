//
// Created by Julian  on 17/11/15.
//

#include "../Headers/GameApp.h"
#include "../Headers/Transforms/PlayerMoveTransform.h"
#include "../Headers/GraphicsResources/CircleFillGraphicsResource.h"
#include "../Headers/GraphicsResources/CircleOutlineGraphicsResource.h"
#include "../Headers/GraphicsResources/TriangleGraphicsResource.h"

#include <time.h>
#include <stdlib.h>
//------------------------------------------------------------------------------------
// Name: GameApp
// Desc:
//------------------------------------------------------------------------------------
GameApp::GameApp()
{
    this->windowHeight = 480;
    this->windowWidth = 640;
    this->appName = "SDL RTS";

    this->graphics = new Graphics(this->windowWidth, this->windowHeight, this->appName);
}
//------------------------------------------------------------------------------------
// Name: ~GameApp
// Desc:
//------------------------------------------------------------------------------------
GameApp::~GameApp()
{
    for (Entity* entity : this->entityList) {
        delete entity;
    }

    delete this->graphics;
}
//------------------------------------------------------------------------------------
// Name: Run
// Desc:
//------------------------------------------------------------------------------------
bool GameApp::Run()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        return true;
    }

    for (IEntityTransform* entityTransform : this->entityTransforms) {

        this->entityList = entityTransform->Transform(this->entityList, &event);
    }

    this->graphics->UpdateGraphics(nullptr, graphicsComponents, transformComponents);

    return false;
}
