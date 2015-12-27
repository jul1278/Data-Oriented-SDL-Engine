//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_COMPONENT_COLLECTION_H
#define SDLRTS_COMPONENT_COLLECTION_H

#include "Components/BaseComponent.h"
#include "ComponentType.h"
#include <map>
#include <vector>

 class ComponentCollection
{
private:

	std::map<int, IBaseComponent*> componentMap;
	std::map<ComponentType, std::vector<int>> typeIdMap; 

public:

	IBaseComponent* operator[](int id)
	{
		if (this->componentMap.find(id) != this->componentMap.end()) {
			return componentMap[id]; 
		}

		return nullptr; 
	}

	std::map<int, IBaseComponent*> operator[](ComponentType componentType)
	{
		if (this->typeIdMap.find(componentType) != this->typeIdMap.end()) {
			std::map<int, IBaseComponent*> components; 
			std::vector<int> ids = this->typeIdMap[componentType]; 

			for (int id : ids) {
				components.insert(std::pair<int, IBaseComponent*>(id, componentMap[id])); 
			}
			return components; 
		}
	}

	void Insert(ComponentType componentType, IBaseComponent* component)
	{	
		// already have this id stored
		if (this->componentMap.find(component->id) == this->componentMap.end()) {
			return; 
		}

		// 
		if (this->typeIdMap.find(componentType) != this->typeIdMap.end()) {
			this->typeIdMap[componentType].push_back(component->id); 
			this->componentMap.insert(std::pair<int, IBaseComponent*>(component->id, component)); 
		} else {
			this->typeIdMap[componentType] = std::vector<int>{component->id};
		}
	}
};

#endif //SDLRTS_COMPONENT_COLLECTION_H