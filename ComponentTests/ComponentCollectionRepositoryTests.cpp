#include "stdafx.h"
#include "CppUnitTest.h"
#include "Components/ComponentCollectionRepository.h"
#include "Components/BaseComponent.h"
#include "Components/TransformComponent.h"
#include "Components/VelocityComponent.h"
#include <vector>
#include <Components/GraphicsComponent.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ComponentTests
{
	TEST_CLASS(ComponentCollectionRepositoryTests)
	{
	public:

		//-----------------------------------------------------------------------------
		// Name: NewComponentTest
		// Desc: 		
		//-----------------------------------------------------------------------------
		TEST_METHOD(NewComponentTest)
		{
			ComponentCollectionRepository componentCollectionRepository; 
			componentCollectionRepository.NewCollection("TestCollection"); 

            for (auto i = 0; i < 20; i += 2)
            {
				auto transformComponent = componentCollectionRepository.NewComponent<TransformComponent>("TestCollection");
				auto graphicsComponent = componentCollectionRepository.NewComponent<GraphicsComponent>("TestCollection");

                Assert::AreEqual(transformComponent->id, i);
				Assert::AreEqual(graphicsComponent->id, i + 1); 
            }
		}
        //-----------------------------------------------------------------------------
        // Name: ComponentPointersAreCorrect
        // Desc: 		
        //-----------------------------------------------------------------------------
        TEST_METHOD(ComponentPointersAreCorrect)
        {
            ComponentCollectionRepository componentCollectionRepository;
            vector<TransformComponent*> transformComponents;
            vector<VelocityComponent*> physicsComponents; 

			transformComponents.reserve(100);
			physicsComponents.reserve(100); 

            for (auto i = 0; i < 50; i++)
            {
                auto transformComponent = componentCollectionRepository.NewComponent<TransformComponent>();
				auto physicsComponent = componentCollectionRepository.NewComponent<VelocityComponent>();

                physicsComponent->transformComponent = transformComponent; 

                transformComponents.push_back(transformComponent); 
                physicsComponents.push_back(physicsComponent); 
            }

			for (auto i = 0; i < 50; i++)
			{
				auto transformComponent = componentCollectionRepository.NewComponent<TransformComponent>();
				auto physicsComponent = componentCollectionRepository.NewComponent<VelocityComponent>();

				physicsComponent->transformComponent = transformComponent;

				transformComponents.push_back(transformComponent);
				physicsComponents.push_back(physicsComponent);
			}

            for (auto i = 0; i < 100; i++)
            {
                Assert::AreEqual(static_cast<void*>(physicsComponents[i]->transformComponent), static_cast<void*>(transformComponents[i])); 
            }
        }

        //-----------------------------------------------------------------------------
        // Name: ComponentPointersAreContiguous
        // Desc: 		
        //-----------------------------------------------------------------------------
        TEST_METHOD(ComponentPointersAreContiguous)
        {
            ComponentCollectionRepository componentCollectionRepository;
            vector<TransformComponent*> transformComponents;

			transformComponents.reserve(100); 

            for (auto i = 0; i < 100; i++)
            {
                auto transformComponent = componentCollectionRepository.NewComponent<TransformComponent>();          
                transformComponents.push_back(transformComponent);
            }

            for (auto i = 0; i < 99; i++)
            {
                auto diff = reinterpret_cast<uint8_t*>(transformComponents[i + 1]) - reinterpret_cast<uint8_t*>(transformComponents[i]); 
                Assert::AreEqual(static_cast<unsigned int>(diff), sizeof(TransformComponent));
            }
        }
		//-----------------------------------------------------------------------------
		// Name: SelectById
		// Desc: 		
		//-----------------------------------------------------------------------------
		TEST_METHOD(SelectComponentById)
		{
			ComponentCollectionRepository componentCollectionRepository; 

			componentCollectionRepository.NewCollection("TestCollection");

			auto component1 = componentCollectionRepository.NewComponent<TransformComponent>();
			auto component2 = componentCollectionRepository.NewComponent<TransformComponent>();
			auto component3 = componentCollectionRepository.NewComponent<TransformComponent>("TestCollection");

			auto result = componentCollectionRepository.Select<TransformComponent>(component2->id); 

			Assert::AreEqual(result->id, component2->id); 
			Assert::AreNotEqual(result->id, component1->id); 
			Assert::AreNotEqual(result->id, component3->id); 
		}
	};
}