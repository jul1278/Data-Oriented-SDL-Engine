//
// Created by Julian  on 17/11/15.
//

#include "../Headers/GameApp.h"
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
    delete this->graphics;
}
//------------------------------------------------------------------------------------
// Name: Run
// Desc:
//------------------------------------------------------------------------------------
int GameApp::Run()
{
    int t = 0;

    while(t < 1000) {

        for ( TransformComponent& transformComponent : this->transformComponents) {

            // Make everything spin around
            transformComponent.orientation = Vector2D(transformComponent.orientation.Angle() + (1.0f/(80.0f*PI)));
        }

        this->graphics->UpdateGraphics(this->graphicsComponents, this->transformComponents);
        t++;
    }

    return 0;
}
