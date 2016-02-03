#include "stdafx.h"
#include "CppUnitTest.h"
#include "Headers/Vector.h"
#include "Headers/ComponentRepository.h"
#include "Headers/Components/BaseComponent.h"
#include "Headers/Components/TransformComponent.h"
#include "Headers/Components/SimplePhysicsComponent.h"
#include "Headers/ComponentAllocator.h"

#include <vector>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ComponentAllocatorTests
{
	TEST_CLASS(ComponentRepositoryTests)
	{
	public:

		TEST_METHOD(TestComponentAllocator)
		{
			vector<int, ComponentAllocator<int>> a; 

			a.push_back(1);
			a.push_back(2);
			a.push_back(3);
			a.push_back(4);

			Assert::AreEqual(4U, a.size()); 		
		}
	};

}