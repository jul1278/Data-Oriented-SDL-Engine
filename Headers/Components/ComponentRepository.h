//
// Created by Julian  on 20/12/15.
//

#ifndef SDL_RTS_COMPONENT_REPOSITORY_H
#define SDL_RTS_COMPONENT_REPOSITORY_H

#include "Components/BaseComponent.h"
#include "ComponentType.h"
#include <map>
#include <vector>

using namespace std; 

class ComponentRepository
{
private:

	int currId; 
	int currEntityId; 

	int GetNextId() { return currId++; }
	int GetNextEntityId() { return currEntityId++; }

	map<ComponentType, vector<IBaseComponent*>> componentTypeAddressMap;
	map<int, IBaseComponent*> componentIdMap; 

public:

	ComponentRepository()
	{
		this->currId = 0; 
		this->currEntityId = 0; 
	}


	~ComponentRepository()
	{
		for (auto component : this->componentIdMap) {
			delete component.second; 
		}
	}

	int InsertComponent(ComponentType componentType, IBaseComponent* baseComponent)
	{
		baseComponent->id = GetNextId(); 


		if (componentTypeAddressMap.find(componentType) == componentTypeAddressMap.end()) {
			componentTypeAddressMap.insert(pair<ComponentType, vector<IBaseComponent*>>(componentType, vector<IBaseComponent*>()));
		}

		componentTypeAddressMap[componentType].push_back(baseComponent);
		componentIdMap[baseComponent->id] = baseComponent; 

		return baseComponent->id; 
	}
	
	vector<IBaseComponent*>* Select(ComponentType componentType)
	{
		if (componentTypeAddressMap.find(componentType) != componentTypeAddressMap.end()) {
			return &componentTypeAddressMap[componentType]; 
		}
		return nullptr; 
	}

	template<typename T> T Select(int id)
	{
		IBaseComponent* component = this->componentIdMap[id];
		return static_cast<T>(component);  
	}

};

#endif // 