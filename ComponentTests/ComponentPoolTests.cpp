#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Headers/ComponentPool.h"
#include <Headers/Components/TransformComponent.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ComponentTests
{
	TEST_CLASS(ComponentRepositoryTests)
	{
	public:

		//-----------------------------------------------------------------------------
		// Name: InsertRemoveComponents
		// Desc: insert 2000 components then remove them and check that the count is zero
		//-----------------------------------------------------------------------------
		TEST_METHOD(AllocateDeallocateComponentPool)
		{
			ComponentPool componentPool(sizeof(TransformComponent)); 

			vector<BaseComponent*> components; 

			for (int i = 0; i < 16; i++) {
				auto transformComponent = reinterpret_cast<TransformComponent*>(componentPool.Allocate());
				
				if (transformComponent != nullptr) {
					transformComponent->position = Vector2D(1.0f, 1.0f);
					components.push_back(transformComponent);

				}
			}
		}

	};

}