#include "stdafx.h"
#include "CppUnitTest.h"
#include <Components/ComponentCollectionRepository.h>
#include <Components/GraphicsComponent.h>
#include <Components/VelocityComponent.h>
#include <Components/TransformComponent.h>
#include <Components/PhysicsComponent.h>
#include <list>

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

			componentCollectionRepository.NewCollection("TestCollection1");
			componentCollectionRepository.NewCollection("TestCollection2");

			vector<unsigned int> ids1; 
			vector<unsigned int> ids2; 

			for (auto i = 0; i < 200; i++) {
				auto component = componentCollectionRepository.NewComponent<TransformComponent>("TestCollection1");
				componentCollectionRepository.NewComponent<PhysicsComponent>("TestCollection1");
				component->position = Vector2D(i, i); 
				
				ids1.push_back(component->id); 
			}

			for (auto i = 0; i < 100; i++) {
				auto component = componentCollectionRepository.NewComponent<TransformComponent>("TestCollection2"); 
				componentCollectionRepository.NewComponent<GraphicsComponent>("TestCollection2");

				component->position = Vector2D(-i, -i);

				ids2.push_back(component->id); 
			}
			
			for (auto i = 0; i < 200; i++) {
				auto component = componentCollectionRepository.Select<TransformComponent>(ids1[i]); 
				Assert::AreEqual(component->position.x, (float)i); 
				Assert::AreEqual(component->position.y, (float)i); 
			}

			for (auto i = 0; i < 100; i++) {
				auto component = componentCollectionRepository.Select<TransformComponent>(ids2[i]);

				Assert::AreEqual(component->position.x, (float)-i);
				Assert::AreEqual(component->position.y, (float)-i);
			}
		}
		//-----------------------------------------------------------------------------
		// Name: RemoveById
		// Desc: 		
		//-----------------------------------------------------------------------------
		TEST_METHOD(RemoveComponentById)
		{
			ComponentCollectionRepository componentCollectionRepository; 
			componentCollectionRepository.NewCollection("TestCollection"); 

			auto component1 = componentCollectionRepository.NewComponent<TransformComponent>(); 
			auto id = component1->id; 

			componentCollectionRepository.RemoveComponent(id); 

			component1 = componentCollectionRepository.Select<TransformComponent>(id); 
			Assert::IsNull(component1); 
		}
		//-----------------------------------------------------------------------------
		// Name: IdsAreUnique
		// Desc: 		
		//-----------------------------------------------------------------------------
		TEST_METHOD(IdsAreUnique)
		{
			ComponentCollectionRepository componentCollectionRepository;
			componentCollectionRepository.NewCollection("TestCollection");

			list<unsigned int> ids; 

			for (auto i = 0; i < 1000; i++) {
				auto a = componentCollectionRepository.NewComponent<TransformComponent>("TestCollection");
				auto b = componentCollectionRepository.NewComponent<GraphicsComponent>();

				ids.push_back(a->id);
				ids.push_back(b->id); 
			}

			ids.sort(); 

			auto len = ids.size();	

			// duplicates will be removed
			ids.unique([](unsigned int a, unsigned int b) {return a == b; }); 

			Assert::AreEqual(len, ids.size()); 
		}
	};
}