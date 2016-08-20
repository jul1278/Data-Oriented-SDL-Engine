#ifndef I_STAGE_H
#define I_STAGE_H


#include "Components/Repository/ComponentCollectionRepository.h"
#include <Physics/Physics.h>
#include <Actions/IAction.h>
#include <Graphics/Graphics.h>

class IGameApp; 

class IStage
{
private:
 
	IGameApp* gameApp; 

	ComponentCollectionRepository* componentCollectionRepository; 
	Physics* physics; 

	list<IAction*> actions; 

public:

	IStage(IGameApp* gameApp, ComponentCollectionRepository* componentCollectionRepository, Physics* physics)
	{
		this->gameApp = gameApp; 
		this->componentCollectionRepository = componentCollectionRepository; 
		this->physics = physics; 
	}

	virtual void Update()
	{
		for_each(this->actions.begin(), this->actions.end(), [] (IAction* action) { action->Update(); });
	}

	virtual ~IStage()
	{
		delete this->componentCollectionRepository; 
		delete this->physics;

		remove_if(this->actions.begin(), this->actions.end(), [](IAction* action){ delete action; return true; });
	};

	void InsertAction(IAction* action)
	{
		if (action != nullptr) {
			this->actions.push_back(action); 
		}
	}

	ComponentCollectionRepository* GetComponentCollectionRepository() const
	{
		return this->componentCollectionRepository; 
	}
	
	Physics* GetPhysics() const
	{
		return this->physics; 
	}
	
	IGameApp* GetGameApp() const
	{
		return this->gameApp; 
	}
};

#endif // I_STAGE_H