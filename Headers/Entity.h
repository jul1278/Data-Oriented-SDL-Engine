//
// Created by Julian  on 17/11/15.
//

#ifndef ENTITY_H
#define ENTITY_H

#include "Components/BaseComponent.h"
#include <map>
#include "ComponentType.h"

struct Entity
{
private:

    map<ComponentType, BaseComponent*> componentMap;
	map<int, BaseComponent*> componentIdMap;
    int id;

public:

    Entity(int id)
    {
        this->id = id;
    }

	int Id() const { return this->id; }

    void AddComponent(ComponentType componentType, BaseComponent* component)
    {
        this->componentMap.insert(std::pair<ComponentType , BaseComponent*>(componentType, component));
    }

	template<typename T> 
	T GetComponent(ComponentType componentType)
    {
		auto component = this->componentMap[componentType]; 
		if (component != nullptr) {
			return static_cast<T>(component); 
		}
		return nullptr; 
    }

	template<typename T> 
	T GetComponent(int id)
    {
		auto component = this->componentIdMap[id]; 
		if (component != nullptr) {
			return static_cast<T>(component);
		}
		return nullptr; 
    }
};


#endif //ENTITY_H
