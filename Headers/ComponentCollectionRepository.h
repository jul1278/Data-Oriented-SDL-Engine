//
// Created by Julian  on 20/12/15.
//
#ifndef COMPONENT_COLLECTION_REPOSITORY_H
#define COMPONENT_COLLECTION_REPOSITORY_H

#include "Components/BaseComponent.h"
#include "Entity.h"
#include <unordered_map>
#include <vector>
#include <boost/pool/pool.hpp>
#include <typeindex>
#include <type_traits>
#include <assert.h>

using namespace std;

struct IVectorContainer {};

template <typename T>
struct VectorContainer : IVectorContainer
{
	vector<T> vec;

	VectorContainer()
	{
		assert((bool)(is_base_of<BaseComponent, T>::value) == true); 
	}
};

// ComponentCollection
struct ComponentCollection
{
	unordered_map<type_index, IVectorContainer*> componentCollection; 
	list<type_index> typeIndices; 

	template<typename T>
	vector<T>* Select()
	{
		auto iContainer = static_cast<IVectorContainer*>(componentCollection[type_index(typeid(T))]); 		
		auto container = static_cast<VectorContainer<T>*>(iContainer); 

		return &(container.vec); 
	}

};

// ComponentCollectionRepository
class ComponentCollectionRepository
{
private:
public:

	// map string to component collection
	unordered_map<string, ComponentCollection*> componentCollectionMap; 

	// all component types
	unordered_map<type_index, list<IVectorContainer*>> componentTypeMap; 
};

#endif // COMPONENT_COLLECTION_REPOSITORY_H