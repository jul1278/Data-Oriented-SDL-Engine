//
// Created by Julian  on 17/11/15.
//

#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std; 

class IMemoryPool {};

template<typename T>
class MemoryPool : public IMemoryPool
{
private:

	vector<T> pool; 
	unordered_map<T*, int> allocToIndex; 

public:

	MemoryPool() 
	{
		this->pool.reserve(100); 
	}

	T* New()
	{
		this->pool.push_back(T()); 
		T* alloc = &this->pool.back();

		this->allocToIndex[alloc] = this->pool.size() - 1; 

		return alloc; 
	}

	void Delete(void* ptr)
	{
		/*auto result = this->allocToIndex[ptr]; 

		if ()*/
	}

	uint32_t Size()
	{
		return sizeof(T)*this->pool.size(); 
	}

};

#endif // MEMORY_POOL_H