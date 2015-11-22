#include "../Headers/GameApp.h"
#include "../TestClasses/TestGraphics.h"
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

