#ifndef COMPONENT_CONTAINER_FACTORY_H
#define COMPONENT_CONTAINER_FACTORY_H

#include "Components/Repository/IComponentContainer.h"
#include "Utility/TypeUtility.h"

#include <typeinfo>
#include <unordered_map>
#include <string>

using namespace std;

class ComponentContainerFactory 
{
	unordered_map<string, function<IComponentContainer*(void)>> componentTypeFactory; 

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
		auto factory = []() -> IComponentContainer* {return new ComponentContainer<T>();};

		this->componentTypeFactory.insert(make_pair(typeName, factory));
	}

	//------------------------------------------------------------------------------
	// Name: New
	// Desc: News up a component container.
	//------------------------------------------------------------------------------
	shared_ptr<IComponentContainer> New(const string& name)
	{
		return shared_ptr<IComponentContainer>(this->componentTypeFactory.at(name)()); 
	}

};

#endif // COMPONENT_CONTAINER_FACTORY_H