//
// Created by Julian  on 30/01/16.
//

#ifndef COMPONENT_ALLOCATOR_H
#define COMPONENT_ALLOCATOR_H

#include "BinarySortTree.h"

#include <cstddef>
#include <cstdint>
#include <limits>
#include <queue>
#include <unordered_map>

using namespace std; 



template<class T>
class ComponentAllocator
{
private:
	uint16_t nextBlockIndex = 0; 
	const uint32_t maxNumBlocks = 256; 
	const uint32_t blockSize = 512;

	unordered_map<uint16_t, DataBlock*> blockMap;
	unordered_map<T*, DataBlockIndex> ptrToBlockIndexMap; 
	
	unordered_map<uint16_t, vector<DataBlockIndex*>> freeBlocks; 

	void NewBlock()
	{
		uint16_t blockIndex = nextBlockIndex; 

		blockMap[blockIndex] = new DataBlock; 
		
		DataBlockIndex* dataBlockIndex = new DataBlockIndex; 

		dataBlockIndex->blockIndex = blockIndex;
		dataBlockIndex->offset = 0; 
		dataBlockIndex->len = blockSize; 

		freeBlocks[dataBlockIndex->len].push_back(dataBlockIndex);
	}


 
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

	~ComponentAllocator() throw()
	{
		for (auto dataBlockIndex : this->freeBlocks) {
			delete dataBlockIndex; 
		}

		for (auto pair : this->blockMap) {
			delete pair.second; 
		}
	}

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
		if (freeBlocks.size() > 0) {
			
			auto dataBlockIndex = freeBlocks.front(); 


		}


		pointer ret = static_cast<pointer>(::operator new(n*sizeof(T))); 
		return ret; 
	}

	void construct(pointer p, const T& value)
	{
		new(static_cast<void*>(p))T(value); 
	}

	void destroy(pointer p)
	{
		p->~T(); 
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