//
// Created by Julian  on 17/11/15.
//

#ifndef COMPONENT_POOL_H
#define COMPONENT_POOL_H

#include <list>
#include <unordered_map>
#include <cstdint>

#define BLOCK_SIZE 2048
#define NUM_BLOCKS 10

using namespace std; 

//
struct DataBlock
{
	uint8_t data[BLOCK_SIZE];
};

struct FreeDataBlock
{
	uint16_t dataBlockIndex; 
	uint8_t* start; 
	uint8_t* end; 

	FreeDataBlock(uint16_t dataBlockIndex, uint8_t* start, uint8_t* end)
	{
		this->dataBlockIndex = dataBlockIndex; 
		this->start = start; 
		this->end = end;
	}

	void Shrink(uint16_t n)
	{
		start += n; 
	}

	int Size() const
	{
		return this->end - this->start; 
	}

	bool Empty()
	{
		return (this->Size() > 0); 
	}
};

class ComponentPool
{
private:

	size_t size;

	list<DataBlock*> dataBlocks; 
	list<FreeDataBlock*> freeDataBlocks; 

public:

	ComponentPool(size_t n)
	{
		size = n; 

		for (int i = 0; i < NUM_BLOCKS; i++) {
			auto dataBlock = new DataBlock; 
			dataBlocks.push_back(dataBlock); 
			freeDataBlocks.push_back(new FreeDataBlock(i, dataBlock->data, dataBlock->data + BLOCK_SIZE)); 
		}
	}

	~ComponentPool()
	{
		dataBlocks.remove_if([](DataBlock* block){delete block; return true;});
		freeDataBlocks.remove_if([](FreeDataBlock* freeDataBlock) {delete freeDataBlock; return true; }); 
	}


	void* Allocate() 
	{
		auto freeDataBlock = freeDataBlocks.front(); 

		uint8_t* alloc = freeDataBlock->start; 
		freeDataBlock->Shrink(this->size);

		if (freeDataBlock->Empty()) {
			freeDataBlocks.pop_front(); 
		}

		return alloc; 
	}

	void Dealloc(uint8_t* ptr) 
	{
		for (auto dataBlock : this->dataBlocks) {
			auto ptrDiff = ptr - dataBlock->data; 
			if (ptrDiff > 0 && ptrDiff < BLOCK_SIZE) {
				freeDataBlocks.push_front(new FreeDataBlock(0, ptr, ptr + this->size)); 
			}
		}
	}
};

#endif // COMPONENT_POOL_H