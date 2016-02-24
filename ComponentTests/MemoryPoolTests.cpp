#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Headers/MemoryPool.h"
#include <Headers/Components/TransformComponent.h>
#include <vector>
#include <unordered_map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ComponentTests
{
	TEST_CLASS(MemoryPoolTests)
	{
	public:

		//-----------------------------------------------------------------------------
		// Name: 
		// Desc: 
		//-----------------------------------------------------------------------------
		TEST_METHOD(AllocateDellocateNewMemory)
		{
			MemoryPool<TransformComponent> componentPool; 
			
			vector<BaseComponent*> components; 

			for (int i = 0; i < 1000; i++) {
				BaseComponent* component = componentPool.New();
				components.push_back(component); 
			}

			Assert::AreEqual(1000 * sizeof(TransformComponent), componentPool.Size()); 

			for (auto ptr : components) {
				componentPool.Delete(ptr); 
			}

			//Assert::AreEqual(0U, componentPool.Size()); 
		}

		//-----------------------------------------------------------------------------
		// Name: 
		// Desc: 
		//-----------------------------------------------------------------------------
		TEST_METHOD(AllocationsAreContiguous)
		{
			MemoryPool<TransformComponent> componentPool;

			vector<BaseComponent*> components;

			for (int i = 0; i < 100; i++) {
				BaseComponent* component = componentPool.New();
				components.push_back(component);
			}

			Assert::AreEqual(100 * sizeof(TransformComponent), componentPool.Size());

			for (int i = 0; i < 99; i++) {
				auto currPtr = components[i]; 
				auto nextPtr = components[i + 1]; 

				auto ptrDiff = nextPtr - currPtr; 


				Assert::AreEqual(4, ptrDiff); 
			}
		}
	};
}