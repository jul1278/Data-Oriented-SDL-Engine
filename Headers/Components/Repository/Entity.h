//
// Created by Julian  on 17/11/15.
//

#ifndef ENTITY_H
#define ENTITY_H

#include "Components/BaseComponent.h"
#include <unordered_map>
#include <algorithm>
#include <typeindex>

using namespace std;

// entity
class Entity
{
private:

    unordered_map<type_index, BaseComponent*> componentMap;
	unordered_map<int, BaseComponent*> componentIdMap;
    int id;

public:

	explicit Entity(int id)
    {
        this->id = id;
    }

	int Id() const { return this->id; }

	template<class T>
    void AddComponent(BaseComponent* component)
    {
		this->componentMap.insert(std::pair<type_index, BaseComponent*>(type_index(typeid(T)), component));
		this->componentIdMap.insert(pair<int, BaseComponent*>(component->id, component)); 
    }

	void RemoveComponentId(int id)
    {
		if (this->componentIdMap.find(id) == this->componentIdMap.end()) {
			return; 
		}

		auto result = find_if(this->componentMap.begin(), this->componentMap.end(), 
		[id](const pair<type_index, BaseComponent*>& component) {
			return (component.second->id == id);
		});

		if (result == this->componentMap.end()) {
			return; 
		}

		this->componentIdMap.erase(id);
		this->componentMap.erase(result); 
    }

	unordered_map<type_index, BaseComponent*>* ComponentMap()
    {
		return &this->componentMap; 
    }

	template<typename T> 
	T* GetComponent()
    {
		auto component = this->componentMap[typeid(T)]; 
		if (component != nullptr) {
			return static_cast<T*>(component); 
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
