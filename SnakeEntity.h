#ifndef SNAKE_ENTITY_H
#define SNAKE_ENTITY_H

#include "Headers/Components/TransformComponent.h"
#include <string>
#include <unordered_map>
#include <functional>

class IEventArgs;
using namespace std; 

enum ComponentType
{
	TRANSFORM,
	GRAPHICS,
	COLLISION,
	INTERSECTION,
};

class EntityComponents
{
	string name; 

	ComponentRepository componentRepository;

	unordered_map<tuple<string, ComponentType>, list<BaseComponent*>> componentMap; 
	unordered_map<int, tuple<ComponentType, BaseComponent*>> componentIdMap; 

public:

	EntityComponents(string name) : name(name)
	{
		componentRepository->RegisterContainer(this, this->name); 
	}

	void RebuildCache(int)
	{
		// retrieve pointers again
	}

	void RebuildCache(string, ComponentType)
	{
		// retrieve pointers again
	}

	unsigned int NewComponent(std::string id, ComponentType componentType)
	{
		auto component = this->componentRepository->NewComponent(this->name, componentType); 
		componentMap[tuple<string, ComponentType>(id, componentType)].push_back(component); 
		componentIdMap[component->id] = tuple<ComponentType, BaseComponent*>(componentType, component); 
	}

	unsigned int NewComponent(std::string, ComponentType, int parentId)
	{
		auto component = this->componentRepository->NewComponent(this->name, componentType);
		component->parentId = parentId; 

		componentMap[tuple<string, ComponentType>(id, componentType)].push_back(component);
		componentIdMap[component->id] = tuple<ComponentType, BaseComponent*>(componentType, component);
	}

	BaseComponent* GetBaseComponent(int Id);
	list<BaseComponent*> GetBaseComponents(string, ComponentType);

	template<typename T>
	T* GetComponent(int id);

	template<typename T>
	list<T*> GetComponents(string);

};

class IEntity
{
private:

	// probably need something like this...
	PythonContext pythonContext;

	EntityComponents entityComponents;

	// map event types to python script objects 
	unordered_map<EventType, list<IScript*>> eventScriptMap;


	void RegisterEventHandler(EventType eventType)
	{
		this->systemEvents->RegisterHandler(this, KEYBOARD_EVENTS);
	}

	// example generic event handler
	void OnEvent(const IEventArgs* eventArgs)
	{
		auto scripts = this->eventScriptMap[eventArgs->EventType()];

		for (auto script : *scripts) {
			script(eventArgs, this);
		}
	}

public:

	IEntity()
	{
		// push this->RegisterEventHandler(...) to python 
	}

	IEntity(string strId)
	{
		// something like this... get script files for this entity
		auto scripts = this->resources->GetFiles(strId); 
		for ( auto s : scripts) {

			// run each script
			s(this); 
		}
	}

	unsigned int AddNewComponent(string, ComponentType); 
	unsigned int AddNewComponent(string, ComponentType, int);

	template<typename T>
	T* GetComponent(string); 

	template<typename T>
	T* GetComponents(string);

	void AddNewEventHandler(IScript* pythonScript); 
	void AddNewEventHandler(function<const IEventArgs*> handler);
	
	template<typename T>
	void AddNewEventHandler(function<const T&> handler); 
};

class SnakeEntity : public IEntity
{
private:

	unsigned int snakeLen;

public:

	SnakeEntity(string strId) : IEntity(strId)
	{
		auto headId = this->AddNewComponent("SnakeHead", TRANSFORM);
		this->AddNewComponent("SnakeHead", GRAPHICS, headId);

		for (int i = 0; i < (snakeLen-1); ++i) {
			auto id = this->AddNewComponent("SnakeBody", TRANSFORM);
			this->AddNewComponent("SnakeBody", GRAPHICS, id);
		}

	}

	// Script.py
	// 
	//
	//
	//
	//
	//

	// example event handler
	void OnButtonPress(const ButtonPressArgs& buttonPressArgs)
	{
		auto bodyTransforms = this->GetComponents<TransformComponent>("SnakeBody");
		auto snakeHead = this->GetComponent<TransformComponent>("SnakeHead"); 

		// update snake parts
	}
};

#endif // SNAKE_ENTITY_H