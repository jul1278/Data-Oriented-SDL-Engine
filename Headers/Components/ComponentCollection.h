#ifndef COMPONENT_COLLECTION_H
#define COMPONENT_COLLECTION_H

#include <Components/VectorContainer.h>
#include <Components/BaseComponent.h>
#include <unordered_map>  
#include <vector>
#include <typeindex>
#include <type_traits>
#include <algorithm>

using namespace std; 

// ComponentCollection
class ComponentCollection
{
	static unsigned int id; 

	unordered_map<type_index, IVectorContainer*> componentCollection;
	unordered_map<unsigned int, tuple<type_index*, BaseComponent*>> idToComponent;

public:

	ComponentCollection() {}

	~ComponentCollection()
	{
		for (auto pair : this->componentCollection)
		{
			delete pair.second;
		}

		for (auto pair : this->idToComponent) {
			auto tup = get<1>(pair); 
			auto type = get<0>(tup); 

			delete type; 
		}
	}
	
	template <typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
	T* NewComponent();

	void DeleteId(unsigned int id); 

	template<typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
	vector<T>* Select();

	template<typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
	T* Select(unsigned int id); 

	static unsigned int GenerateId()
	{
		return id++;
	}
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

	container->vec.push_back(T());
	T* component = &container->vec.back();

	component->id = ComponentCollection::GenerateId();

	auto type = new type_index(typeid(T));
	this->idToComponent[component->id] = tuple<type_index*, BaseComponent*>(type, component);

	return &container->vec.back();
}
//---------------------------------------------------------------------------------------------
// Name: Delete
// Desc:
//---------------------------------------------------------------------------------------------
inline void ComponentCollection::DeleteId(unsigned int id)
{
	auto typeComponentPair = this->idToComponent[id]; 

	auto type = get<0>(typeComponentPair); 
	this->componentCollection[*type]->RemoveId(id); 

	auto it = this->idToComponent.find(id);

	if (it != this->idToComponent.end()) {
		this->idToComponent.erase(it); 
	}
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
//---------------------------------------------------------------------------------------------
// Name: Select
// Desc:
//---------------------------------------------------------------------------------------------
template<typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
T* ComponentCollection::Select(unsigned int id)
{
	//auto pair = this->idToComponent[id]; 
	//auto component = get<1>(pair); 
	//T* container = static_cast<T*>(component);

	auto baseContainer = this->componentCollection[type_index(typeid(T))];
	VectorContainer<T>* container = static_cast<VectorContainer<T>*>(baseContainer);
	auto component = find_if(container->vec.begin(), container->vec.end(), [id](const T& t){return t.id == id; });

	return component._Ptr; 
}

#endif // COMPONENT_COLLECTION_H
