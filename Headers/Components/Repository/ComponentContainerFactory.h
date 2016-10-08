#ifndef COMPONENT_CONTAINER_FACTORY_H
#define COMPONENT_CONTAINER_FACTORY_H

#include "Components/Repository/IComponentContainer.h"
#include "Utility/TypeUtility.h"

#include <typeinfo>
#include <unordered_map>
#include <string>
#include <exception>

using namespace std;

class ComponentContainerFactory 
{
	list<string> componentNames; 
	
	unordered_map<string, function<IComponentContainer*(void)>> componentTypeContainerFactory;
	unordered_map<string, function<BaseComponent*(void)>> componentTypeFactory; 

public:

	ComponentContainerFactory();

	~ComponentContainerFactory() {}

	//------------------------------------------------------------------------------
	// Name: Register
	// Desc: register a type into the factory. Must be derived from BaseComponent
	//------------------------------------------------------------------------------
	template<typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
	void Register()
	{
		auto typeName = TypeUtility::TypeName<T>();
		auto containerFactory = []() -> IComponentContainer* {return new ComponentContainer<T>();};
		auto componentFactory = []() -> BaseComponent* {return new T();};

		this->componentTypeContainerFactory.insert(make_pair(typeName, containerFactory));
		this->componentNames.push_back(typeName);

		this->componentTypeFactory.insert(make_pair(typeName, componentFactory));
	}

	//------------------------------------------------------------------------------
	// Name: New
	// Desc: News up a component container.
	//------------------------------------------------------------------------------
	shared_ptr<IComponentContainer> New(const string& name)
	{
		return shared_ptr<IComponentContainer>(this->componentTypeContainerFactory.at(name)()); 
	}

	//-------------------------------------------------------------------------------
	// Name: ComponentFromName
	// Desc: 
	//-------------------------------------------------------------------------------
	shared_ptr<BaseComponent> ComponentFromName(const string& name)
	{
		if (this->componentTypeFactory.find(name) != this->componentTypeFactory.end()) {
			return shared_ptr<BaseComponent>(this->componentTypeFactory[name]());
		}

		throw string(name + " does not exist."); 
	}

	//------------------------------------------------------------------------------
	// Name: ComponentNames
	// Desc: 
	//------------------------------------------------------------------------------
	list<string> ComponentNames()
	{
		return this->componentNames; 
	}

};

#endif // COMPONENT_CONTAINER_FACTORY_H