//
// 27/03/16.
//
#ifndef I_GAME_APP_H
#define I_GAME_APP_H

#include "Game/IStage.h"
#include <queue>

class Graphics;

using namespace std;

class IGameApp
{
private:

	queue<IStage*> stageQueue; 

public:
	

	IGameApp() {}

	virtual ~IGameApp()
	{
		while (!stageQueue.empty()) {
			delete stageQueue.front(); 
			stageQueue.pop(); 
		}
	}

	void Run()
	{
		while (!stageQueue.empty()) {
			stageQueue.front()->Update(); 
		}
	}

	void PushStage(IStage* stage)
	{
		if (stage) {
			this->stageQueue.push(stage);
		}
	}

	void PopStage()
	{
		this->stageQueue.pop(); 
	}

	// Don't want the base class to store graphics for now, 
	// but make sure derived classes have to. 
	virtual Graphics* GetGraphics() = 0;
};

#endif // I_GAME_APP_H