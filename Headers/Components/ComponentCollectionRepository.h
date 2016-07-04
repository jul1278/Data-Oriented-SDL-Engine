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
 
const string defaultCollectionName = "defaultCollection";

// ComponentCollectionRepository
class ComponentCollectionRepository
{
private:

	// map string to component collection
	// TODO: can we make this not a pointer?
	unordered_map<string, ComponentCollection*> componentCollectionMap; 

	// id to parent collection
	unordered_map<unsigned int, string> idToCollectionMap;

	// entity id to component id
	unordered_map<unsigned int, list<unsigned int>> entityToComponent; 

	// namedEntities
	// unordered_map<string, list<unsigned int>> nameToEntityId; 

public:

	//------------------------------------------------------------------------------------
	// Name: Constructor
	// Desc:
	//------------------------------------------------------------------------------------
	ComponentCollectionRepository()
	{
		// default collection so there is always somewhere to add to
        this->componentCollectionMap[defaultCollectionName] = new ComponentCollection(); 
	}
	//------------------------------------------------------------------------------------
	// Name: Destructor
	// Desc:
	//------------------------------------------------------------------------------------
    ~ComponentCollectionRepository()
	{
        for (const auto& pair : this->componentCollectionMap) {
            delete pair.second; 
        }
	}
	//------------------------------------------------------------------------------------
	// Name: NewComponent
	// Desc: collectionName and entityId is optional
	//       if an entity id is associated with the collection name 
	//       (except in the case of defaultCollectionName) it will be assigned
	//------------------------------------------------------------------------------------
	template<typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
	T* NewComponent(const string collectionName = defaultCollectionName, unsigned int entityId = 0)
	{
		this->NewCollection(collectionName); 

		BaseComponent* newComponent = nullptr;

		newComponent = this->componentCollectionMap[collectionName]->NewComponent<T>();

		auto collection = componentCollectionMap[collectionName]; 
		this->idToCollectionMap[newComponent->id] = collectionName; 

		if (entityId > 0) {
			this->entityToComponent[entityId].push_back(newComponent->id);
		} 

		return static_cast<T*>(newComponent);
	}
	//------------------------------------------------------------------------------------
	// Name: RemoveComponent
	// Desc: 
	//------------------------------------------------------------------------------------
	void RemoveComponent(unsigned int id)
	{
		auto collectionName = defaultCollectionName; 

		if (this->idToCollectionMap.find(id) != this->idToCollectionMap.end()) {
			collectionName = this->idToCollectionMap[id];
		}

		auto collection = this->componentCollectionMap[collectionName]; 
		auto component = this->SelectBase(id); 

		// find my entity and remove my id from its list
		// NOTE: might be okay to not remove these. Ideally most of the
		// time you'd be removing a whole entity rather than individual components..
		if (this->entityToComponent.find(component->entityId) != this->entityToComponent.end()) {
			this->entityToComponent[component->entityId].remove_if([id](unsigned int componentId) {return componentId == id; });
		}

		if (collection != nullptr) {
			collection->DeleteId(id); 
			
			auto it = this->idToCollectionMap.find(id); 

			if (it != this->idToCollectionMap.end()) {
				this->idToCollectionMap.erase(it); 
			}
		}
	}
	//------------------------------------------------------------------------------------
	// Name: RemoveEntity
	// Desc:
	//------------------------------------------------------------------------------------
	void RemoveEntity(unsigned int entityId)
	{
		if (this->entityToComponent.find(entityId) != this->entityToComponent.end()) {
			
			auto& ids = this->entityToComponent[entityId];
			
			for_each(ids.begin(), ids.end(), [=](unsigned int id) {this->RemoveComponent(id); });
			ids.clear(); 
		}
	}
	//------------------------------------------------------------------------------------
	// Name: NewCollection
	// Desc: generates an entity id for the collection should one choose to use it.
	//------------------------------------------------------------------------------------
	void NewCollection(const string collectionName)
	{
		if (componentCollectionMap.find(collectionName) == componentCollectionMap.end()) {
            componentCollectionMap[collectionName] = new ComponentCollection();
		}
	}
	//------------------------------------------------------------------------------------
	// Name: NewEntityId
	// Desc: 
	//------------------------------------------------------------------------------------
	unsigned int NewEntityId()
	{
		auto id = ComponentCollection::GenerateId(); 
		this->entityToComponent[id]; 
		return id; 
	}
	//------------------------------------------------------------------------------------
	// Name: SelectFromCollection
	// Desc:
	//------------------------------------------------------------------------------------
	template<typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
    vector<T>* SelectFromCollection(const string collectionName = defaultCollectionName)
	{
        if (this->componentCollectionMap.find(collectionName) != this->componentCollectionMap.end())
        {
            return this->componentCollectionMap[collectionName]->Select<T>(); 
        }

        return nullptr; 
	}
	//------------------------------------------------------------------------------------
	// Name: Select
	// Desc:
	//------------------------------------------------------------------------------------
	template<typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
	T* Select(int id)
	{
		auto collectionName = this->idToCollectionMap[id]; 
		auto collection = this->componentCollectionMap[collectionName]; 

		if (collection != nullptr) {

			T* result = collection->Select<T>(id); 
			return result;
		}

		return nullptr;
	}
	//------------------------------------------------------------------------------------
	// Name: SelectBase
	// Desc:
	//------------------------------------------------------------------------------------
	BaseComponent* SelectBase(int id)
	{
		auto collectionName = this->idToCollectionMap[id]; 
		auto collection = this->componentCollectionMap[collectionName];

		if (collection != nullptr) {
			return collection->SelectBase(id); 
		}

		return nullptr; 
	}
	//------------------------------------------------------------------------------------
	// Name: DeleteCollection
	// Desc:
	//------------------------------------------------------------------------------------
	void DeleteCollection(const string& name)
	{
		delete this->componentCollectionMap[name];
	}
	//------------------------------------------------------------------------------------
	// Name: GetCollections
	// Desc:
	//------------------------------------------------------------------------------------
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