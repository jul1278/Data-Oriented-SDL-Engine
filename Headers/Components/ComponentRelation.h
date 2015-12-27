//
// Created by Julian  on 22/12/15.
//

#ifndef SDLRTS_COMPONENT_DEPENDENCY_H
#define SDLRTS_COMPONENT_DEPENDENCY_H

#include "BaseComponent.h"

// one
struct BaseComponentRelation
{
	IBaseComponent* parent; 

	BaseComponentRelation(IBaseComponent* parent)
	{
		this->parent = parent; 
	}

	template<typename T>
	T Parent() { return static_cast<T>(this->parent); }
};

// one to one pair relation
struct ComponentPairRelation : BaseComponentRelation
{
	IBaseComponent* child; 

	ComponentPairRelation(IBaseComponent* parent, IBaseComponent* child) : BaseComponentRelation(parent)
	{
		this->child = child; 
	}

	template<typename T>
	T Child() { return static_cast<T>(this->child); }
};

#endif