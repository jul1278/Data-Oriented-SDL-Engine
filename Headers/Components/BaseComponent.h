//
// Created by Julian  on 17/11/15.
//
#ifndef BASE_COMPONENT_H
#define BASE_COMPONENT_H

#include <map>

using namespace std; 

struct BaseComponent
{
    // Has to be set by something, obviously we can't choose our own Id.
    int id;
    int entityId;

    BaseComponent()
    {
        this->id = 0;
        this->entityId = 0;
    }

	template <class T>
	T As()
	{
		return static_cast<T>(this); 
	}
};

#endif //BASE_COMPONENT_H
