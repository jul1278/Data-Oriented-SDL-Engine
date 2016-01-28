//
// Created by Julian  on 20/12/15.
//

#ifndef COMPONENT_REPOSITORY_H
#define COMPONENT_REPOSITORY_H

#include "Components/BaseComponent.h"
#include "ComponentType.h"
#include "Entity.h"
#include "Components/SimplePhysicsComponent.h"

#include <unordered_map>
#include <vector>

#include <boost/pool/object_pool.hpp>

using namespace std; 

class ComponentRepository
{
private:

	int currId; 
	int currEntityId; 

	int GetNextId() { return currId++; }
	int GetNextEntityId() { return currEntityId++; }

	unordered_map<ComponentType, vector<BaseComponent*>> componentTypeAddressMap;
	unordered_map<int, BaseComponent*> componentIdMap; 
	unordered_map<int, Entity*> entityMap; 
	
	unordered_map<ComponentType, uint8_t> componentSize; 

	 

	int InsertComponent(ComponentType componentType, BaseComponent* baseComponent)
	{
		baseComponent->id = GetNextId();

		if (componentTypeAddressMap.find(componentType) == componentTypeAddressMap.end()) {
			componentTypeAddressMap.insert(pair<ComponentType, vector<BaseComponent*>>(componentType, vector<BaseComponent*>()));
		}

		componentTypeAddressMap[componentType].push_back(baseComponent);
		componentIdMap[baseComponent->id] = baseComponent;

		return baseComponent->id;
	}


public:

	ComponentRepository()
	{
		this->currId = 0; 
		this->currEntityId = 0; 

		this->componentSize[TRANSFORM_COMPONENT] = sizeof(TransformComponent); 
		this->componentSize[GRAPHICS_COMPONENT] = sizeof(GraphicsComponent); 
		this->componentSize[SIMPLE_PHYSICS_COMPONENT] = sizeof(SimplePhysicsComponent); 

		boost::pool<> p(sizeof(int)); 
	}

	~ComponentRepository()
	{
		// TODO: datablock needs to handle deleting components

		for (auto component : this->componentIdMap) {
			delete component.second; 
		}
	}

	Entity* NewEntity()
	{
		Entity* newEntity = new Entity(this->GetNextEntityId()); 
		
		entityMap[newEntity->Id()] = newEntity; 
		return newEntity; 
	}

	template<class T>
	T NewComponent(ComponentType componentType)
	{
		// TODO: allocate here in a pool of memory
		//
		uint8_t allocSize = this->componentSize[componentType]; 
		BaseComponent* newComponent = reinterpret_cast<BaseComponent*>(new uint8_t[allocSize]); 
		
		int id = this->InsertComponent(componentType, newComponent); 
		return static_cast<T>(newComponent); 
	}

	vector<BaseComponent*>* Select(ComponentType componentType)
	{
		if (componentTypeAddressMap.find(componentType) != componentTypeAddressMap.end()) {
			return &componentTypeAddressMap[componentType]; 
		}
		return nullptr; 
	}

	template<typename T> 
	T Select(int id)
	{
		BaseComponent* component = this->componentIdMap[id];
		return static_cast<T>(component);  
	}

};

#endif // 