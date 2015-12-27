//
// Created by Julian  on 17/11/15.
//

#include <time.h>
#include <stdlib.h>
#include <GameApp.h>

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
}
//------------------------------------------------------------------------------------
// Name: Run
// Desc:
//------------------------------------------------------------------------------------
bool GameApp::Run()
{
    return false;
}
