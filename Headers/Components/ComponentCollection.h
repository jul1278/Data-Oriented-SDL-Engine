#ifndef COMPONENT_COLLECTION_H
#define COMPONENT_COLLECTION_H

#include "Components\BaseComponent.h"

#include <unordered_map>  
#include <vector>
#include <typeindex>
#include <type_traits>
#include <list>

using namespace std; 

const unsigned int vectorContainerReserveSize = 100;

struct IVectorContainer {};

template <typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
struct VectorContainer : IVectorContainer
{
	vector<T> vec;

	VectorContainer()
	{
		vec.reserve(vectorContainerReserveSize);
	}
};

// ComponentCollection
class ComponentCollection
{
	unordered_map<type_index, IVectorContainer*> componentCollection;
	
public:

	ComponentCollection() {}

	~ComponentCollection()
	{
		for (auto pair : this->componentCollection)
		{
			delete pair.second;
		}
	}
	
	template <typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
	T* NewComponent();

	template<typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
	vector<T>* Select();
};

//---------------------------------------------------------------------------------------------
// Name: NewComponent
// Desc:
//---------------------------------------------------------------------------------------------
template <typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
T* ComponentCollection::NewComponent()
{
	if (this->componentCollection[type_index(typeid(T))] == nullptr) {
		auto vectorContainer = new VectorContainer<T>();
		this->componentCollection[type_index(typeid(T))] = vectorContainer;
	}

	VectorContainer<T>* container = static_cast<VectorContainer<T>*>(this->componentCollection[type_index(typeid(T))]);

	if (container->vec.size() < vectorContainerReserveSize) {
		container->vec.push_back(T());
	}
	else {
		throw "Can't resize";
	}

	return &container->vec.back();
}

//---------------------------------------------------------------------------------------------
// Name: Select
// Desc:
//---------------------------------------------------------------------------------------------
template<typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
vector<T>* ComponentCollection::Select()
{
	auto iContainer = componentCollection[type_index(typeid(T))];
	auto container = static_cast<VectorContainer<T>*>(iContainer);
	return &(container->vec);
}

#endif // COMPONENT_COLLECTION_H
