//
// Created by Julian  on 30/01/16.
//

#ifndef COMPONENT_ALLOCATOR_H
#define COMPONENT_ALLOCATOR_H

#include <cstddef>
#include <cstdint>
#include <limits>
#include <unordered_map>
#include <vector>

using namespace std; 



template<class T>
class ComponentAllocator
{
private:

	vector<T> pool; 

public:

	typedef T* pointer; 
	typedef const T* const_pointer; 
	
	typedef T& reference; 
	typedef const T& const_reference; 

	typedef size_t size_type; 
	typedef ptrdiff_t difference_type; 

	typedef T value_type; 
	
	ComponentAllocator() throw() {}
	ComponentAllocator(const ComponentAllocator&) throw() {}
	
	template<class U>
	ComponentAllocator(const ComponentAllocator<U>&) throw() {}

	~ComponentAllocator() throw() { }

	template<class U>
	struct rebind
	{
		typedef ComponentAllocator<U> other;
	};

	pointer address(reference value) const
	{
		return &value; 
	}

	const_pointer address(const_reference value) const
	{
		return &value; 
	}

	pointer allocate(size_type n, const void* hint = nullptr)
	{
		this->pool.push_back(T); 
		return &this->pool.back(); 
	}

	void construct(pointer p, const T& value)
	{
		new(static_cast<void*>(p))T(value); 
	}

	void destroy(pointer p)
	{
		auto result = std::find_first_of(this->pool.begin(), this->pool.back(), 
		[p](T obj) 
		{ 
			if (p == &obj) return true; 
		} );

		this->pool.erase(result); 
	}

	void deallocate(void* ptr, size_type n)
	{
		::operator delete(static_cast<void*>(ptr)); 
	}

	size_type max_size() const
	{
		return std::numeric_limits<size_t>::max() / sizeof(T); 
	}
};

template<class T1, class T2>
bool operator== (const ComponentAllocator<T1>& a, const ComponentAllocator<T2>& b) throw()
{
	return true; 
}

template<class T1, class T2>
bool operator!= (const ComponentAllocator<T1>& a, const ComponentAllocator<T2>& b) throw()
{
	return false; 
}
#endif // COMPONENT_ALLOCATOR_H