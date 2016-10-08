//
// Created by Julian  on 17/11/15.
//
#ifndef BASE_COMPONENT_H
#define BASE_COMPONENT_H

struct BaseComponent
{
	unsigned int id;
    unsigned int entityId;

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

struct BaseLinkedComponent : public BaseComponent
{
	unsigned int linkedComponentId; 

	BaseLinkedComponent()
	{
		this->linkedComponentId = 0; 
	}
};

#endif //BASE_COMPONENT_H
