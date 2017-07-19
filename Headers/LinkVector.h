//
// Created on 10/08/2016.
//

#ifndef LINK_VECTOR_H
#define LINK_VECTOR_H

#include <list>
#include <queue>
#include <unordered_map>

class Block
{
	uint8_t* blockStart;
	uint8_t blockSize; 
};

template<typename T>
class LinkVector 
{
	std::unordered_map
	std::list<Block> blocks;

public:


	T* New()
	{
		if (!this->free.empty()) {
			T* free = this->free.front();
			this->free->pop(); 
		} else {
			
		}
	}
};

#endif