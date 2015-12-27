//
// Created by Julian  on 17/11/15.
//

#ifndef SDL_RTS_ICOMPONENT_H
#define SDL_RTS_ICOMPONENT_H

#include <map>

using namespace std; 
// NOTE: IBaseComponent not IComponent

struct IBaseComponent
{
    // Has to be set by something, obviously we can't choose our own Id.
    int id;
    int entityId;

    IBaseComponent()
    {
        this->id = 0;
        this->entityId = 0;
    }
};

struct IBaseDependentComponent : public IBaseComponent
{
	IBaseComponent* dependency;

	IBaseDependentComponent()
	{
		this->dependency = nullptr;
	}
};

struct IBaseMultiDependentComponent : public IBaseComponent
{
	map<int, IBaseComponent*> dependentMap;

	IBaseMultiDependentComponent()
	{
	}
};

#endif //SDL_RTS_ICOMPONENT_H
