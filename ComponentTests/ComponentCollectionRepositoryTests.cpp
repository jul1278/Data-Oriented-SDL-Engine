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
		TEST_METHOD(ComponentCollectionTest)
		{
			ComponentCollectionRepository componentCollectionRepository; 
			
			auto transformComponentContainer = new VectorContainer<TransformComponent>();

			transformComponentContainer->vec.push_back(TransformComponent(Vector2D(3.0f, 2.0f))); 

			auto componentCollection = new ComponentCollection(); 
			componentCollection->componentCollection[type_index(typeid(TransformComponent))] = transformComponentContainer; 
			componentCollectionRepository.componentCollectionMap["TransformComponents"] = componentCollection; 
			
			auto collection = componentCollectionRepository.componentCollectionMap["TransformComponents"]; 
			auto componentContainer = static_cast<VectorContainer<TransformComponent>*>(collection->componentCollection[type_index(typeid(TransformComponent))]); 

			auto component = componentContainer->vec.front();

			Assert::AreEqual(component.position.x, 3.0f); 
			Assert::AreEqual(component.position.y, 2.0f); 
		}

	};


}