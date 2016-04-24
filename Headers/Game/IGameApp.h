//
// 27/03/16.
//
#ifndef I_GAME_APP_H
#define I_GAME_APP_H

#include "Graphics/Graphics.h"
#include "Components/ComponentCollectionRepository.h"
#include "Physics/Physics.h"
#include "Game/IStage.h"

#include <typeindex>
#include <queue>

using namespace std;

class IGameApp
{
private:

	queue<IStage*> stageQueue; 

public:
	

	IGameApp() {}

	~IGameApp()
	{
		while (!stageQueue.empty()) {
			delete stageQueue.front(); 
			stageQueue.pop(); 
		}
	}

	void Run()
	{
		while (!stageQueue.empty()) {
			stageQueue.front()->Update(this); 
		}
	}

	void PushStage(IStage* stage)
	{
		if (stage)
		{
			this->stageQueue.push(stage);
		}
	}

	void PopStage()
	{
		this->stageQueue.pop(); 
	}

	virtual Graphics* GetGraphics() = 0;
	virtual Physics* GetPhysics() = 0;
	virtual ComponentCollectionRepository* GetComponentCollectionRepository() = 0;
};

#endif // I_GAME_APP_H