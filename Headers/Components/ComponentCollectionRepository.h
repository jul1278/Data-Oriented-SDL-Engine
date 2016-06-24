//
// Created by Julian  on 24/02/16.
//

#ifndef COMPONENT_COLLECTION_REPOSITORY_H
#define COMPONENT_COLLECTION_REPOSITORY_H

#include "Utility/MathUtility.h"
#include "ComponentCollection.h"

#include <unordered_map>  
#include <vector>
#include <typeindex>
#include <type_traits>
#include <algorithm>
#include <list>

using namespace std;

const int collectionNameMinLength = 4; 
const string defaultCollectionName = "defaultCollection";

// ComponentCollectionRepository
class ComponentCollectionRepository
{
private:

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
        this->componentCollectionMap[defaultCollectionName] = new ComponentCollection(); 
	}

    ~ComponentCollectionRepository()
	{
        for (const auto& pair : this->componentCollectionMap)
        {
            delete pair.second; 
        }
	}

	template<typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
	T* NewComponent(const string collectionName = defaultCollectionName)
	{
		auto collectionNameTemp = collectionName;

		BaseComponent* newComponent = nullptr;

		newComponent = this->componentCollectionMap[collectionNameTemp]->NewComponent<T>();

		auto collection = componentCollectionMap[collectionNameTemp]; 
		this->idToCollectionMap[newComponent->id] = collection; 

		return static_cast<T*>(newComponent);
	}

	void RemoveComponent(unsigned int id)
	{
		auto collection = this->idToCollectionMap[id]; 

		if (collection != nullptr) {
			collection->DeleteId(id); 
			
			auto it = this->idToCollectionMap.find(id); 
			if (it != this->idToCollectionMap.end()) {
				this->idToCollectionMap.erase(it); 
			}
		}
	}

	void NewCollection(const string collectionName)
	{
		if (collectionName.length() < collectionNameMinLength) {
			return; 
		}

		if (componentCollectionMap.find(collectionName) == componentCollectionMap.end()) {
            componentCollectionMap[collectionName] = new ComponentCollection();
		}
	}

	template<typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
    vector<T>* SelectFromCollection(const string collectionName = defaultCollectionName)
	{
        if (this->componentCollectionMap.find(collectionName) != this->componentCollectionMap.end())
        {
            return this->componentCollectionMap[collectionName]->Select<T>(); 
        }

        return nullptr; 
	}

	template<typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
	list<IVectorContainer*>* Select()
	{
		if (this->componentTypeMap.find(type_index(typeid(T))) != this->componentTypeMap.end()) {
			return &this->componentTypeMap[type_index(typeid(T))];
		}

		return nullptr; 
	}

	template<typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
	T* Select(int id)
	{
		auto collection = this->idToCollectionMap[id]; 

		if (collection != nullptr) {

			T* result = collection->Select<T>(id); 
			return result;
			
		}

		return nullptr;
	}

	template<typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
    void InsertCollection(IVectorContainer* vectorContainer)
	{
        this->componentTypeMap[type_index(typeid(T))].push_back(vectorContainer); 
	}

	void DeleteCollection(const string& name)
	{
		delete this->componentCollectionMap[name];
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