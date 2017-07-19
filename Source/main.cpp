//#include "Demos/SpaceGame/SpaceGameApp.h"
#include "Demos\FunTest\FunTestGameApp.h"

//------------------------------------------------------------------------------------
// Name: Run
// Desc:
//------------------------------------------------------------------------------------
void Run()
{
	/*SpaceGameApp spaceGameApp; 
	spaceGameApp.Run(); */

	FunTestGameApp funGameTestApp;
	funGameTestApp.Run(); 
}

//------------------------------------------------------------------------------------
// Name: main
// Desc:
//------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	Run(); 

	return 0;
}


