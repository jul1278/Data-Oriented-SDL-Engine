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

	// TODO: use smart pointer
	ComponentCollectionRepository* componentCollectionRepository;
	Graphics* graphics;	
	Physics* physics;

public:
	

	IGameApp() : componentCollectionRepository(nullptr), graphics(nullptr), physics(nullptr) {} 

	void Run()
	{
		if (this->graphics == nullptr) {
			this->graphics = this->GetGraphics();
		}

		if (this->physics == nullptr) {
			this->physics = this->GetPhysics();
		}

		if (this->componentCollectionRepository = nullptr) {
			this->componentCollectionRepository = this->GetComponentCollectionRepository(); 
		}

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