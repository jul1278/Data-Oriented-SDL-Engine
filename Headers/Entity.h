//
// Created by Julian  on 17/11/15.
//

#ifndef SDL_RTS_ENTITY_H
#define SDL_RTS_ENTITY_H

#include "Components/BaseComponent.h"
#include <map>
#include "ComponentType.h"

struct Entity
{
private:

    map<ComponentType, IBaseComponent*> componentMap;
	map<int, IBaseComponent*> componentIdMap;
    int id;

public:

    Entity(int id)
    {
        this->id = id;
    }

	int Id() const { return this->id; }

    void AddComponent(ComponentType componentType, IBaseComponent* component)
    {
        this->componentMap.insert(std::pair<ComponentType , IBaseComponent*>(componentType, component));
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


#endif //SDL_RTS_ENTITY_H
