#include "stdafx.h"
#include "CppUnitTest.h"
#include "Headers/Vector.h"
#include "Headers/ComponentCollectionRepository.h"
#include "Headers/Components/BaseComponent.h"
#include "Headers/Components/TransformComponent.h"
#include "Headers/Components/SimplePhysicsComponent.h"

#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ComponentTests
{
	TEST_CLASS(ComponentCollectionRepositoryTests)
	{
	public:

		//-----------------------------------------------------------------------------
		// Name: 
		// Desc: 		
		//-----------------------------------------------------------------------------
		TEST_METHOD(NewComponentTest)
		{
			ComponentCollectionRepository componentCollectionRepository; 
 
			auto component = componentCollectionRepository.NewComponent<TransformComponent>();
			Assert::IsNotNull(component); 
		}

	};


}