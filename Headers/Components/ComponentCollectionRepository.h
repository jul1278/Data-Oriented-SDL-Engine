//
// Created by Julian  on 24/02/16.
//

#ifndef COMPONENT_COLLECTION_REPOSITORY_H
#define COMPONENT_COLLECTION_REPOSITORY_H

#include "Components/BaseComponent.h"
#include "Entity.h"
#include <unordered_map>  
#include <vector>
#include <typeindex>
#include <type_traits>
#include <assert.h>
#include <list>

using namespace std;

const int collectionNameMinLength = 4; 
const string defaultCollectionName = "defaultCollection";
const unsigned int vectorContainerReserveSize = 100; 

class ComponentCollectionRepository; 

struct IVectorContainer {};

template <typename T>
struct VectorContainer : IVectorContainer
{
	vector<T> vec;

	VectorContainer()
	{
		assert(static_cast<bool>(is_base_of<BaseComponent, T>::value) == true); 
        vec.reserve(vectorContainerReserveSize);
	}
};

// ComponentCollection
class ComponentCollection
{
    ComponentCollectionRepository* parent; 

	unordered_map<type_index, IVectorContainer*> componentCollection; 
	list<type_index> typeIndices; 

public:

    ComponentCollection()
    {
        this->parent = nullptr;
    }

    ComponentCollection(ComponentCollectionRepository* parent)
    {
        this->parent = parent; 
    }

    ~ComponentCollection()
    {
        for (auto pair : this->componentCollection)
        {
            delete pair.second; 
        }
    }

	template <typename T>
	T* NewComponent()
	{
		T* newComponent = nullptr; 


		if (this->componentCollection.find(type_index(typeid(T))) == this->componentCollection.end()) {
			auto vectorContainer = new VectorContainer<T>();	 
			this->componentCollection[type_index(typeid(T))] = vectorContainer;

            if (this->parent != nullptr)
            {
                this->parent->InsertCollection<T>(vectorContainer); 
            }
		}
		
		auto container = static_cast<VectorContainer<T>*>(this->componentCollection[type_index(typeid(T))]); 		        
        container->vec.resize(container->vec.size() + 1); 

        return new (&(container->vec.back())) T();
	}

	template<typename T>
	vector<T>* Select()
	{
		auto iContainer = static_cast<IVectorContainer*>(componentCollection[type_index(typeid(T))]); 		
		auto container = static_cast<VectorContainer<T>*>(iContainer); 
		return &(container->vec); 
	}

};

// ComponentCollectionRepository
class ComponentCollectionRepository
{
private:

    unsigned int nextId; 
    unsigned int GetNextId() { return nextId++; }

	// map string to component collection
	unordered_map<string, ComponentCollection*> componentCollectionMap; 

	// all component types
	unordered_map<type_index, list<IVectorContainer*>> componentTypeMap; 

	// id to parent collection
	unordered_map<unsigned int, ComponentCollection*> idToCollectionMap; 

public:

	ComponentCollectionRepository()
	{
		// default collection so there is always somewhere to add to
        this->componentCollectionMap[defaultCollectionName] = new ComponentCollection(this);
        this->nextId = 0; 
	}

    ~ComponentCollectionRepository()
	{
        for (const auto& pair : this->componentCollectionMap)
        {
            delete pair.second; 
        }
	}

	template<typename T>
	T* NewComponent(const string collectionName = "")
	{
        if (static_cast<bool>(is_base_of<BaseComponent, T>::value) == false)
        {
            return nullptr; 
        }

		string collectionNameTemp = this->componentCollectionMap.find(collectionName) == 
									this->componentCollectionMap.end() 
			? defaultCollectionName : collectionName; 

        BaseComponent* newComponent = nullptr; 

		newComponent = this->componentCollectionMap[collectionNameTemp]->NewComponent<T>();
        newComponent->id = this->GetNextId(); 

		auto collection = componentCollectionMap[collectionNameTemp]; 
		this->idToCollectionMap[newComponent->id] = collection; 

        return static_cast<T*>(newComponent); 
	}

	void NewCollection(const string collectionName)
	{
		if (collectionName.length() < collectionNameMinLength) {
			return; 
		}

		if (componentCollectionMap.find(collectionName) == componentCollectionMap.end()) {
            componentCollectionMap[collectionName] = new ComponentCollection(this);
		}
	}

    template<typename T>
    vector<T>* SelectFromCollection(const string collectionName = defaultCollectionName)
	{
        if (this->componentCollectionMap.find(collectionName) != this->componentCollectionMap.end())
        {
            return this->componentCollectionMap[collectionName]->Select<T>(); 
        }

        return nullptr; 
	}

	template<typename T>
	list<IVectorContainer*>* Select()
	{
		if (this->componentTypeMap.find(type_index(typeid(T))) != this->componentTypeMap.end()) {
			return &this->componentTypeMap[type_index(typeid(T))];
		}

		return nullptr; 
	}

    template<typename T>
    void InsertCollection(IVectorContainer* vectorContainer)
	{
        if (static_cast<bool>(is_base_of<BaseComponent, T>::value) == true)
        {
            this->componentTypeMap[type_index(typeid(T))].push_back(vectorContainer); 
        }
	}

	list<string> GetCollections()
	{
		list<string> collectionNames; 

		for (auto name : this->componentCollectionMap) {
			collectionNames.push_back(name.first); 
		}

		return collectionNames; 
	}
};

#endif // COMPONENT_COLLECTION_REPOSITORY_H