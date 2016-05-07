#ifndef I_STAGE_H
#define I_STAGE_H

#include <Components/ComponentCollectionRepository.h>
#include <Physics/Physics.h>

class IGameApp;

class IStage
{
private:

	IGameApp* gameApp; 
	ComponentCollectionRepository* componentCollectionRepository; 
	Physics* physics; 

public:

	IStage(IGameApp* gameApp, ComponentCollectionRepository* componentCollectionRepository, Physics* physics)
	{
		this->gameApp = gameApp; 
		this->componentCollectionRepository = componentCollectionRepository; 
		this->physics = physics; 
	}

	virtual void Update() = 0;

	virtual ~IStage()
	{
		delete this->componentCollectionRepository; 
		delete this->physics; 
	};

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