#include "stdafx.h"
#include "CppUnitTest.h"
#include "Headers/DataBlockTree.h"

#include <vector>
#include <list>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ComponentTests
{
	TEST_CLASS(DataBlockTreeTests)
	{
	public:

		TEST_METHOD(DataBlockTreeInsert)
		{
			list<DataBlock*> dataBlocks; 

			DataBlock dataBlock; 
			DataBlockIndex dataBlockIndex; 

			dataBlockIndex.ptr = reinterpret_cast<uint8_t*>(&dataBlock.data[0]);
			dataBlockIndex.len = 512; 

			dataBlocks.push_back(&dataBlock);
			FreeDataBlockNode freeDataBlockNodeRoot(&dataBlockIndex); 
			
			for (int i = 0; i < 9; i++) {
				auto newDataBlock = new DataBlock; 
				auto newDataBlockIndex = new DataBlockIndex;

				newDataBlockIndex->ptr = reinterpret_cast<uint8_t*>(&newDataBlock->data[0]); 
				newDataBlockIndex->len = 512; 

				dataBlocks.push_back(newDataBlock); 
				freeDataBlockNodeRoot.Insert(newDataBlockIndex); 
			}


			Assert::AreEqual(1U, freeDataBlockNodeRoot.CountNodes()); 
			Assert::AreEqual(1U, freeDataBlockNodeRoot.Depth()); 
		}

		TEST_METHOD(DataBlockTreeInsertAndAlloc)
		{
			list<DataBlock*> dataBlocks;

			DataBlock dataBlock;
			DataBlockIndex dataBlockIndex;

			dataBlockIndex.ptr = reinterpret_cast<uint8_t*>(&dataBlock.data[0]);
			dataBlockIndex.len = 512;

			dataBlocks.push_back(&dataBlock);
			FreeDataBlockNode freeDataBlockNodeRoot(&dataBlockIndex);

			for (int i = 0; i < 9; i++) {
				auto newDataBlock = new DataBlock;
				auto newDataBlockIndex = new DataBlockIndex;

				newDataBlockIndex->ptr = reinterpret_cast<uint8_t*>(&newDataBlock->data[0]);
				newDataBlockIndex->len = 512;

				dataBlocks.push_back(newDataBlock);
				freeDataBlockNodeRoot.Insert(newDataBlockIndex);
			}

			void* mem = freeDataBlockNodeRoot.Allocate(32);


			auto nodeCount = freeDataBlockNodeRoot.CountNodes(); 
			auto depth = freeDataBlockNodeRoot.Depth(); 

			Assert::IsNotNull(mem); 
			Assert::AreEqual(2U, nodeCount);
			Assert::AreEqual(2U, depth);
		}


	};

}
