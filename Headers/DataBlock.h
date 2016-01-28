#ifndef DATA_BLOCK_H
#define DATA_BLOCK_H

#include <vector>
#include <cstdint>
#include <queue>

using namespace std;

struct DataBlock
{
	uint8_t* data; 
	uint16_t len; 
};

struct DataAddress
{
	uint16_t blockIndex; 
	uint16_t dataOffset;
	uint16_t dataEnd; 
};

class DataPool
{
private:
	
	uint32_t blockPitch; 
	uint32_t blockSize; 
	vector<DataBlock*> dataBlocks; 
	queue<DataAddress*> freeBlocks; 

	unordered_map<void*, DataAddress*> allocations; 
	
public:

	DataPool(uint8_t blockPitch)
	{
		this->blockSize = 256; 
		this->blockPitch = blockPitch;  
	}

	~DataPool()
	{
		
	}

	void Free(void* data)
	{
		auto dataAddress = this->allocations[data]; 

	}

	void* Allocate()
	{
		if (freeBlocks.empty() == false) {

			auto blockIndex = freeBlocks.front().blockIndex; 
			auto dataOffset = freeBlocks.front().dataOffset; 
			auto dataEnd = freeBlocks.front().blockIndex; 

			this->freeBlocks.front().dataOffset += this->blockPitch; 

			if (this->freeBlocks.front().dataOffset == this->freeBlocks.front().dataEnd){
				
				// dont forget to pop
				this->freeBlocks.pop();
			}

			return reinterpret_cast<void*>(dataBlocks[blockIndex].data[dataOffset]); 
		} 

		this->dataBlocks.push_back(DataBlock()); 
		this->dataBlocks.back().data = new uint8_t[this->blockSize*this->blockPitch]; 

		// 
		DataAddress newDataAddress; 
		newDataAddress.blockIndex = dataBlocks.size() - 1; 
		newDataAddress.dataOffset = 0; 
		newDataAddress.dataEnd = this->blockSize*this->blockPitch; 

		this->freeBlocks.push(newDataAddress); 

		return this->dataBlocks.back().data; 

	}

};

#endif // DATA_BLOCK_H