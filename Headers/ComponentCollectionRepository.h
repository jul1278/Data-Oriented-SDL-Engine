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

const int collectionNameMinLength = 4; 

struct IVectorContainer {};

template <typename T>
struct VectorContainer : IVectorContainer
{
	vector<T> vec;

	VectorContainer()
	{
		assert((bool)(is_base_of<BaseComponent, T>::value) == true); 
		vec.reserve(100); 
	}
};

// ComponentCollection
class ComponentCollection
{

	unordered_map<type_index, IVectorContainer*> componentCollection; 
	list<type_index> typeIndices; 

public:

	ComponentCollection() {}; 

	template <typename T>
	T* NewComponent()
	{
		T* newComponent = nullptr; 

		if (this->componentCollection.find(type_index(typeid(T))) == this->componentCollection.end()) {
			auto vectorContainer = new VectorContainer<T>();	 
			this->componentCollection[type_index(typeid(T))] = vectorContainer;
		}
		
		auto container = static_cast<VectorContainer<T>*>(this->componentCollection[type_index(typeid(T))]); 
		container->vec.resize(container->vec.size() + 1); 
		return &(container->vec.back()); 
	}

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

	// map string to component collection
	unordered_map<string, ComponentCollection*> componentCollectionMap; 

	// all component types
	unordered_map<type_index, list<IVectorContainer*>> componentTypeMap; 

public:

	ComponentCollectionRepository()
	{
		// default collection so there is always somewhere to add to
		componentCollectionMap["defaultCollection"] = new ComponentCollection(); 
	}

	template<typename T>
	T* NewComponent(string collectionName = "")
	{
		if (componentCollectionMap.find(collectionName) == componentCollectionMap.end()) {
			return componentCollectionMap["defaultCollection"]->NewComponent<T>(); 
		}

		return componentCollectionMap[collectionName]->NewComponent<T>();
	}

	void NewCollection(string collectionName)
	{
		if (collectionName.length() < collectionNameMinLength) {
			return; 
		}

		if (componentCollectionMap.find(collectionName) == componentCollectionMap.end()) {
			componentCollectionMap[collectionName] = new ComponentCollection(); 
		}
	}

};

#endif // COMPONENT_COLLECTION_REPOSITORY_H