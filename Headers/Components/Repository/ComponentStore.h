#ifndef COMPONENT_STORE_H
#define COMPONENT_STORE_H


class ComponentStore
{
	// id to collection
	unordered_map<unsigned int, shared_ptr<ComponentRepository>> idToRepository; 

	// id to container
	unordered_map<unsigned int, shared_ptr<IContainer>> idToContainer;

public:

	ComponentStore() {}
	~ComponentStore() {}

	void Store(unsigned int id, shared_ptr<ComponentRepository> repository, shared_ptr<IContainer> container);
	
    template<typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
    T* RetrieveComponent(unsigned int id); 
};

#endif // COMPONENT_STORE_H