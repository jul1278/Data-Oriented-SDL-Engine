#ifndef COMPONENT_COLLECTION_ITERATOR_H
#define COMPONENT_COLLECTION_ITERATOR_H

#include "Components/Repository/CComponentCollectionFwd.h"

#include <cassert>      
#include <cstddef>      
#include <iterator>     
#include <type_traits>  
#include <utility>      
#include <iostream>

using namespace std;

//---------------------------------------------------------------------------------------
// Name: ComponentCollectionIterator
// Desc: forward iterator
//---------------------------------------------------------------------------------------
template<typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
class ComponentCollectionIterator : public iterator<forward_iterator_tag, T, long, const T*, T> 
{
	// NOT to be cleaned up
	Repository::ComponentCollection<T>* componentCollection;
	unsigned int index; 

public:

	//------------------------------------------------------------------------------------------
	// Name: Constructor
	// Desc: 
	//------------------------------------------------------------------------------------------
	ComponentCollectionIterator(Repository::ComponentCollection<T>* componentCollection)  
	{
		this->componentCollection = componentCollection; 
		this->index = 0; 
	}
	//-------------------------------------------------------------------------------------------
	// Name: ++ operator
	// Desc: Pre-inc
	//-------------------------------------------------------------------------------------------
	ComponentCollectionIterator<T>& operator++() 
	{
		auto size = this->componentCollection->Size();
		//if(this->index >= (size - 1)) {
		if(size == 0 || this->index + 1 >= size) {
			this->componentCollection = nullptr;  
		}

		this->index++;
		return *this; 
	}
	//-------------------------------------------------------------------------------------------
	// Name: ++ operator
	// Desc: Post-inc
	//-------------------------------------------------------------------------------------------
	ComponentCollectionIterator<T> operator++ (int)
	{
		auto size = this->componentCollection->Size();

		if(size == 0 || this->index + 1 >= size) {
			ComponentCollectionIterator componentCollectionIterator(nullptr); 
			return componentCollectionIterator; 
		}

		ComponentCollectionIterator componentCollectionIterator(this->componentCollection);
		this->index++; 

		return componentCollectionIterator; 
	}
	//-------------------------------------------------------------------------------------------
	// Name: swap
	// Desc: 
	//-------------------------------------------------------------------------------------------
	void swap(ComponentCollectionIterator<T>& other)
	{
		assert(this->componentCollection != nullptr);
		swap(&(*other), &(*this)); 
	}
	//-------------------------------------------------------------------------------------------
	// Name: inequality operator
	// Desc: Equality and inequality. 
	//       Check if the iterators refer to the same underlying component.
	//-------------------------------------------------------------------------------------------
	bool operator!= (const ComponentCollectionIterator<T> rhs) const
	{
		if (this->componentCollection == nullptr && rhs.componentCollection == nullptr) {
			return false;
		}

		if (this->componentCollection == nullptr || rhs.componentCollection == nullptr) {
			return true; 
		}

		return &(**this) != &(*rhs); 
	}
	//---------------------------------------------------------------------------------------------
	// Name: Equality operator 
	// Desc: Check if the iterators refer to the same underlying component.
	//---------------------------------------------------------------------------------------------
	bool operator== (const ComponentCollectionIterator<T> rhs) const
	{
		if (this->componentCollection == nullptr && rhs.componentCollection == nullptr) {
			return true;
		}

		if (this->componentCollection == nullptr || rhs.componentCollection == nullptr) {
			return false; 
		}

		return &(**this) == &(*rhs); 
	}
	//---------------------------------------------------------------------------------------------
	// Name: Dereference operator
	// Desc: 
	//---------------------------------------------------------------------------------------------
	T& operator* () const
	{
		assert(this->componentCollection != nullptr);
		return (*this->componentCollection)[this->index]; 
	}
	//---------------------------------------------------------------------------------------------
	// Name: Reference operator
	// Desc: 
	//---------------------------------------------------------------------------------------------
	T& operator-> () const
	{
		assert(this->componentCollection != nullptr);
		return (*this->componentCollection)[this->index]; 
	}
	//---------------------------------------------------------------------------------------------
	// Name: Const iterator 
	// Desc: 
	//---------------------------------------------------------------------------------------------
	operator ComponentCollectionIterator<const T>() const
	{
		assert(this->componentCollection != nullptr);
		ComponentCollectionIterator<const T> constIterator; 
		constIterator.index = this->index; 
		
		return constIterator;
	}
};

#endif // COMPONENT_COLLECTION_ITERATOR_H