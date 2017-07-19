//
// Created on 10/08/2016.
//

#ifndef COMPONENT_REPOSITORY_H
#define COMPONENT_REPOSITORY_H

#include "Components/BaseComponent.h"
#include "Utility/TypeUtility.h"
#include "Components/Repository/IComponentContainer.h"
#include "Components/Repository/ComponentContainerFactory.h"
#include "Components/Repository/CComponentCollection.h"
#include "Components/Repository/ComponentCollectionIterator.h"

#include <unordered_map>
#include <functional>
#include <memory>
#include <typeinfo>
#include <vector>
#include <string>
#include <list>

using namespace std; 

class ComponentRepository
{
	// id
	static unsigned int id; 

	// this collection name
	string collectionName; 

	// named child collection
	unordered_map<string, shared_ptr<ComponentRepository>> childRepository; 

	// component type name to container 
	unordered_map<string, shared_ptr<IComponentContainer>> componentContainer;

	// id to Container
	unordered_map<unsigned int, weak_ptr<IComponentContainer>> idMap; 

	// entity id to id
	unordered_map<unsigned int, list<unsigned int>> entityIdToComponentId; 

	// collection name string -> ComponentRepository
	ComponentContainerFactory componentContainerFactory; 

	// TODO: ComponentStore componentStore; 

public:

	//-----------------------------------------------------------------------------------
	// Name: ComponentRepository
	// Desc:
	//-----------------------------------------------------------------------------------
	ComponentRepository(const string& name) 
	{
		this->collectionName = name; 
	}

	//-----------------------------------------------------------------------------------
	// Name: destructor
	// Desc:
	//-----------------------------------------------------------------------------------
	~ComponentRepository() 
	{
		this->collectionName = "deleted"; 
	}

	//-----------------------------------------------------------------------------------
	// Name: Name
	// Desc:
	//-----------------------------------------------------------------------------------
	string Name() 
	{ 
		return this->collectionName;
 	}
	
	// implemented in ComponentRepository.cpp
	static unsigned int GenerateId(); 

	//-----------------------------------------------------------------------------------
	// Name: SelectId
	// Desc: select component of id 
	//-----------------------------------------------------------------------------------
	template<typename T = BaseComponent, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
	T* SelectId(unsigned int id)
	{
		BaseComponent* component = nullptr; 

		if (this->idMap.find(id) != this->idMap.end()) {
			if (auto container = this->idMap[id].lock()) {
				component = container->SelectBase(id); 	
			}

		} else {

			for(auto child : this->childRepository) {
				auto repository = child.second; 

				if (component = repository->SelectId(id)) {
					break; 
				}
			}
		}

		if (component != nullptr) {
			return static_cast<T*>(component);
		}

		return nullptr; 
	}
	//-----------------------------------------------------------------------------------
	// Name: Select
	// Desc: select all components of type T from collection collectionName
	//-----------------------------------------------------------------------------------
	template<typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
	Repository::ComponentCollection<T> Select(const string& collectionName = "")
	{
		auto typeName = TypeUtility::TypeName<T>(); 
		Repository::ComponentCollection<T> collection; 

		// am I collectionName or is it a child of mine?
		if (collectionName == this->Name() || collectionName == "") {

			auto container = dynamic_pointer_cast<ComponentContainer<T>>(this->componentContainer[typeName]);
			if (container != nullptr) {
				collection.Append(container->components); 	
			}
		}

		if (collectionName != this->Name() || collectionName == "") {
			
			// search my children 
			for (auto namedRepository : this->childRepository) {

				// I guess this allows multiple repositories with the same name?
				auto repository = namedRepository.second;
				auto result = repository->Select<T>(collectionName);
				
				collection.Append(result);
			}
		}

		return collection; 
	}
	//--------------------------------------------------------------------------------
	// Name: NewComponent
	// Desc:
	//--------------------------------------------------------------------------------
	template<typename T = BaseComponent, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
	T* NewComponent(const string& collectionName = "")
	{
		auto type = TypeUtility::TypeName<T>();

		if (auto component = this->NewComponent(type, collectionName)) {
			return static_cast<T*>(component);
		}

		return nullptr;
	}
	//--------------------------------------------------------------------------------
	// Name: NewComponent
	// Desc:
	//--------------------------------------------------------------------------------
	template<typename T = BaseComponent, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
	T* NewComponent(const string& collectionName, unsigned int entityId)
	{
		T* component = nullptr;

		if (this->Name() == collectionName) {

			if(component = this->NewComponent<T>(collectionName)) {
				component->entityId = entityId; 	
				this->entityIdToComponentId[entityId].push_back(component->id);
			}

		} else {

			for (auto child : this->childRepository) {
				auto repository = child.second; 
				
				if(component = repository->NewComponent<T>(collectionName, entityId)) {
					break;
				}
			}
		}

		return component; 
	}
	//--------------------------------------------------------------------------------
	// Name: NewBaseComponent
	// Desc:
	//--------------------------------------------------------------------------------
	BaseComponent* NewComponent(const string& componentType, const string& collectionName = "")
	{
		BaseComponent* component = nullptr;

		// if I am collectionName then create component here otherwise ask my children
		if (collectionName == "" || this->Name() == collectionName) {

			if (this->componentContainer.find(componentType) == this->componentContainer.end()) {

				auto container = this->componentContainerFactory.New(componentType);
				this->componentContainer.insert(make_pair(componentType, container));
			}
			
			auto componentContainer = this->componentContainer[componentType]; 
			assert(componentContainer != nullptr); 

			component = componentContainer->AddBase();
			
			if (component != nullptr) {
				component->id = this->GenerateId(); 
			}  	
			
			// store the id
			this->idMap.insert(make_pair(component->id, componentContainer));

			return component;
		
		} else {

			for (auto child : this->childRepository) {
				
				auto repository = child.second;
				if (component = repository->NewComponent(componentType, collectionName)) {
					//component->id = this->GenerateId(); 
					break; 
				}
			}
		}

		return component;
	}
	//--------------------------------------------------------------------------------
	// Name: Remove
	// Desc:
	//--------------------------------------------------------------------------------
	bool Remove(unsigned int id)
	{
		if (this->idMap.find(id) != this->idMap.end()) {
			if(auto container = this->idMap[id].lock()) {
			
				container->Remove(id); 
				this->idMap.erase(id);
				return true; 
			}

		} else {

			for(auto child : this->childRepository) {
				auto repository = child.second; 
				
				if(repository->Remove(id)) {
					return true; 
				} 
			}
		}

		return false; 
	}
	//--------------------------------------------------------------------------------
	// Name: RemoveEntity
	// Desc:
	//--------------------------------------------------------------------------------
	bool RemoveEntity(unsigned int entityId)
	{
		if (this->entityIdToComponentId.find(entityId) != this->entityIdToComponentId.end()) {

			auto ids = this->entityIdToComponentId[entityId]; 

			for(auto id : ids) {
				this->Remove(id); 
			}

			return true;

		} else {

			for (auto child : this->childRepository) {
				auto repository = child.second; 

				if (repository->RemoveEntity(entityId) ) {
					return true; 
				}
			}
		}

		return false; 
	}
	//--------------------------------------------------------------------------------
	// Name: NewCollection
	// Desc:
	//--------------------------------------------------------------------------------
	void NewCollection(const string& collectionName)
	{
		if (!this->ContainsCollection(collectionName)) {

			shared_ptr<ComponentRepository> componentRepository(new ComponentRepository(collectionName));
			this->childRepository.emplace(collectionName, componentRepository); 
		}
	}
	//--------------------------------------------------------------------------------
	// Name: ContainsCollection
	// Desc:
	//--------------------------------------------------------------------------------
	bool ContainsCollection(const string& collectionName)
	{
		if (this->Name() == collectionName) {
			return true;
		}

		for (auto child : this->childRepository) {
			if (child.second->ContainsCollection(collectionName)) {
				return true;
			}
		}

		return false; 
	}
};

#endif // COMPONENT_REPOSITORY_H