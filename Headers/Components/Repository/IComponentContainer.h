#ifndef I_COMPONENT_CONTAINER_H
#define I_COMPONENT_CONTAINER_H

#include "Components/BaseComponent.h"

#include <list>
#include <vector>
#include <memory>
#include <type_traits>

using namespace std; 

class IComponentContainer
{
public:
    
    virtual BaseComponent* AddBase() = 0;
    virtual void Remove(unsigned int id) = 0;  
    virtual BaseComponent* SelectBase(unsigned int id) = 0; 

    virtual ~IComponentContainer() {}
};

template<typename T = BaseComponent, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
class ComponentContainer : public IComponentContainer
{

    //-------------------------------------------------------------
    // Name: FindId
    // Desc: Returns an iterator
    //-------------------------------------------------------------
    typename vector<T>::iterator FindId(unsigned int id)
    {
        auto component = find_if(components->begin(), components->end(), 
        [id] (const T& t) {
            return t.id == id;
        });

        return component; 
    }

public:

    shared_ptr<vector<T>> components; 

    //-------------------------------------------------------------
    // Name: Constructor
    // Desc:
    //-------------------------------------------------------------
    ComponentContainer(unsigned int reserveCount = 100) 
    { 
        this->components.reset(new vector<T>); 
        this->components->reserve(reserveCount); 
    }
    //-------------------------------------------------------------
    // Name: AddBase
    // Desc:
    //-------------------------------------------------------------
    virtual BaseComponent* AddBase() override final
    {
        return dynamic_cast<BaseComponent*>(this->Add()); 
    } 
    //-------------------------------------------------------------
    // Name: Add
    // Desc:
    //-------------------------------------------------------------
    T* Add()
    {
        this->components->push_back(T());
        return &this->components->back(); 
    }
    //-------------------------------------------------------------
    // Name: Remove
    // Desc:
    //-------------------------------------------------------------
    virtual void Remove(unsigned int id) override final 
    {
        auto component = this->FindId(id);         

        // swap 'n pop
        if (component != this->components->end()) {
            swap(*component, this->components->back());

            auto back = this->components->back();
            memset((void*)&back, 0, sizeof(T));

            this->components->pop_back(); 
        }
    }  
    //-------------------------------------------------------------
    // Name: SelectBase
    // Desc:
    //-------------------------------------------------------------
    virtual BaseComponent* SelectBase(unsigned int id) override final 
    {
        auto component = this->FindId(id); 
        return &(*component); 
    } 
    //-------------------------------------------------------------
    // Name: Destructor
    // Desc:
    //-------------------------------------------------------------
    virtual ~ComponentContainer() {}  
};

#endif // I_COMPONENT_CONTAINER_H