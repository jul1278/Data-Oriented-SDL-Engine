#include "GameApp.h"
#include "TestGraphics.h"
//------------------------------------------------------------------------------------
// Name: main
// Desc:
//------------------------------------------------------------------------------------
int main()
{
    GameApp gameApp;
    while (gameApp.Run() == false) {}
    return 0;
}

