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
            vector<BaseComponent*> components; 

            for (auto i = 0; i < 10; i++)
            {
                auto transformComponent = componentCollectionRepository.NewComponent<TransformComponent>();
                components.push_back(transformComponent);
                Assert::AreEqual(transformComponent->id, i);
            }
		}
        //-----------------------------------------------------------------------------
        // Name: 
        // Desc: 		
        //-----------------------------------------------------------------------------
        TEST_METHOD(ComponentPointersAreCorrect)
        {
            ComponentCollectionRepository componentCollectionRepository;
            vector<TransformComponent*> transformComponents;
            vector<SimplePhysicsComponent*> physicsComponents; 

            for (auto i = 0; i < 100; i++)
            {
                auto transformComponent = componentCollectionRepository.NewComponent<TransformComponent>();
                auto physicsComponent = componentCollectionRepository.NewComponent<SimplePhysicsComponent>(); 

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
        // Name: 
        // Desc: 		
        //-----------------------------------------------------------------------------
        TEST_METHOD(ComponentPointersAreContiguous)
        {
            ComponentCollectionRepository componentCollectionRepository;
            vector<TransformComponent*> transformComponents;

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

	};


}