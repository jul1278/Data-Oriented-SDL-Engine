//
// Created by Julian  on 20/12/15.
//

#ifndef COMPONENT_REPOSITORY_H
#define COMPONENT_REPOSITORY_H

#include "Components/BaseComponent.h"
#include "Entity.h"
#include <unordered_map>
#include <vector>
#include <../lib/boost_1_60_0/boost/pool/pool.hpp>
#include <typeindex>

using namespace std; 

class ComponentRepository
{
private:

	int currId; 
	int currEntityId; 

	int GetNextId() { return currId++; }
	int GetNextEntityId() { return currEntityId++; }

	unordered_map<type_index, vector<BaseComponent*>> componentTypeAddressMap;
	unordered_map<int, BaseComponent*> componentIdMap;
	unordered_map<int, Entity*> entityMap;
	unordered_map<type_index, uint16_t> componentSize;
	//unordered_map<type_index, boost::pool<>*> componentPool;
	unordered_map<int, type_index*> idToTypeMap; 

	template<class T>
	int InsertComponent(BaseComponent* baseComponent)
	{
		baseComponent->id = GetNextId();
		baseComponent->entityId = 0; // don't get assigned to an entity by default

		if (componentTypeAddressMap.find(type_index(typeid(T))) == componentTypeAddressMap.end()) {
			componentTypeAddressMap.insert(pair<type_index, vector<BaseComponent*>>(type_index(typeid(T)), vector<BaseComponent*>()));
		}

		componentTypeAddressMap[typeid(T)].push_back(baseComponent);
		componentIdMap[baseComponent->id] = baseComponent;

		this->idToTypeMap.emplace(baseComponent->id, new type_index(type_index(typeid(T))));
		
		return baseComponent->id;
	}

public:

	ComponentRepository()
	{
		this->currId = 1; 
		this->currEntityId = 1; 
	}

	~ComponentRepository()
	{
		/*for (auto pool : this->componentPool) {
			delete pool.second; 
		}
*/
		for (const auto& pair : componentIdMap) {
			delete pair.second; 
		}
	}

	int Count() const
	{
		return this->componentIdMap.size(); 
	}

	template<class T>
	void RegisterComponentType()
	{
		// possibly obselete

		//if (this->componentPool.find(typeid(T)) == this->componentPool.end()) {
		//	this->componentPool[typeid(T)] = new boost::pool<>(sizeof(T));

		//	// probably ok if we dont check for this?
		//	this->componentSize[typeid(T)] = sizeof(T);

		//}
	}

	Entity* NewEntity()
	{
		Entity* newEntity = new Entity(this->GetNextEntityId()); 
		
		entityMap[newEntity->Id()] = newEntity; 
		return newEntity; 
	}

	template<class T>
	T* NewComponent()
	{
		/*if (this->componentPool.find(typeid(T)) == this->componentPool.end()) {
			return nullptr; 
		}*/

		//BaseComponent* newComponent = reinterpret_cast<BaseComponent*>(this->componentPool[typeid(T)]->malloc()); 
		
		BaseComponent* newComponent = reinterpret_cast<BaseComponent*>(new T); 

		int id = this->InsertComponent<T>(newComponent); 
		return static_cast<T*>(newComponent); 
	}

	template<class T>
	T* NewComponent(int parentEntityId)
	{
		auto newComponent = this->NewComponent<T>();

		// fails silently if
		if (this->entityMap.find(parentEntityId) != this->entityMap.end()) {
			this->entityMap[parentEntityId]->AddComponent<T>(newComponent); 
		}

		return static_cast<T*>(newComponent); 
	}

	template<class T>
	vector<BaseComponent*>* Select()
	{
		if (componentTypeAddressMap.find(typeid(T)) != componentTypeAddressMap.end()) {
			return &componentTypeAddressMap[typeid(T)]; 
		}

		return nullptr; 
	}

	template<typename T> 
	T Select(int id)
	{
		BaseComponent* component = this->componentIdMap[id];
		return static_cast<T>(component);  
	}

	Entity* SelectEntity(int id)
	{
		if (this->entityMap.find(id) != this->entityMap.end()) {
			return this->entityMap[id]; 
		}

		return nullptr; 
	}

	void DeleteComponent(int id)
	{
		auto deleteType = *this->idToTypeMap[id];
		auto deleteAddr = this->componentIdMap[id]; 

		// If I belong to an entity, remove me from it
		if (this->entityMap.find(deleteAddr->entityId) != this->entityMap.end()) {
			this->entityMap[deleteAddr->entityId]->RemoveComponentId(id); 
		}

		// remove from id map
		if (this->componentIdMap.find(id) != this->componentIdMap.end()) {
			this->componentIdMap.erase(id); 
		}

		// remove from type vector address map
		if (this->componentTypeAddressMap.find(deleteType) != this->componentTypeAddressMap.end()) {
			auto components = &this->componentTypeAddressMap[deleteType];

			auto result = find_if(components->begin(), components->end(), [id](BaseComponent* c) {return (c->id == id); });

			if (result != components->end()) {
				components->erase(result); 
			}
		}

		//this->componentPool[deleteType]->free(reinterpret_cast<void*>(deleteAddr));
	}

	void DeleteEntity(int entityId)
	{
			
	}

	void Release()
	{
		// What do??
	}

};

#endif // 