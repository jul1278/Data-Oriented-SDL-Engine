//#include <SpaceGame\SpaceGameApp.h>
#include "SnakeGame\SnakeGameApp.h"
#define SDL_MAIN_HANDLED

//------------------------------------------------------------------------------------
// Name: main
// Desc:
//------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//SpaceGameApp spaceGameApp; 
	//spaceGameApp.Run(); 

	SnakeGameApp snakeGameApp; 
	snakeGameApp.Run(); 

    return 0;
}

