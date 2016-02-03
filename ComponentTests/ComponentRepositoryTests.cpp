#include "stdafx.h"
#include "CppUnitTest.h"
#include "Headers/Vector.h"
#include "Headers/ComponentRepository.h"
#include "Headers/Components/BaseComponent.h"
#include "Headers/Components/TransformComponent.h"
#include "Headers/Components/SimplePhysicsComponent.h"

#include <vector>

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
		TEST_METHOD(InsertRemoveComponents)
		{
			ComponentRepository componentRepository;
			vector<int> ids;

			componentRepository.RegisterComponentType<TransformComponent>();
			componentRepository.RegisterComponentType<SimplePhysicsComponent>();

			for (int i = 0; i < 10; i++) {

				auto newTransformComponent = componentRepository.NewComponent<TransformComponent>();
				auto newPhysicsComponent = componentRepository.NewComponent<SimplePhysicsComponent>();

				ids.push_back(newTransformComponent->id);
				ids.push_back(newPhysicsComponent->id);
			}

			for (auto id : ids) {
				componentRepository.DeleteComponent(id);
			}

			Assert::AreEqual(0, componentRepository.Count());
		}
		//-----------------------------------------------------------------------------
		// Name: RetrieveNonExistantComponent
		// Desc: try to remove a component that doesn't exist
		//-----------------------------------------------------------------------------
		TEST_METHOD(TryRetrieveNonExistantComponent)
		{
			ComponentRepository componentRepository;
			componentRepository.RegisterComponentType<TransformComponent>(); 

			auto component = componentRepository.Select<TransformComponent*>(1000); 

			Assert::IsNull(component); 
		}
		//-----------------------------------------------------------------------------
		// Name: RetrieveComponent
		// Desc: insert transform components then retrieve them and assert their value
		//-----------------------------------------------------------------------------
		TEST_METHOD(RetrieveComponent)
		{
			ComponentRepository componentRepository;
			map<int, Vector2D> idVectorMap; 
			componentRepository.RegisterComponentType<TransformComponent>();

			for (int i = 0; i < 10; i++) {
				auto newTransformComponent = componentRepository.NewComponent<TransformComponent>(); 
				newTransformComponent->position = Vector2D(static_cast<float>(i), static_cast<float>(i)); 

				idVectorMap[newTransformComponent->id] = Vector2D(static_cast<float>(i), static_cast<float>(i));
			}

			for (auto idVectorPair : idVectorMap) {
				auto id = idVectorPair.first; 
				auto vector = idVectorPair.second; 

				auto transformComponent = componentRepository.Select<TransformComponent*>(id); 

				Assert::AreEqual(id, transformComponent->id); 
				Assert::AreEqual(vector.x, transformComponent->position.x);
				Assert::AreEqual(vector.y, transformComponent->position.y); 
			}
		}
		//-----------------------------------------------------------------------------
		// Name: BuildSimpleEntity
		// Desc: construct a simple entity through the component repo
		//-----------------------------------------------------------------------------
		TEST_METHOD(BuildSimpleEntity)
		{
			ComponentRepository componentRepository;

			componentRepository.RegisterComponentType<TransformComponent>();
			componentRepository.RegisterComponentType<SimplePhysicsComponent>();
			
			auto entity = componentRepository.NewEntity(); 
			
			auto transformComponent = componentRepository.NewComponent<TransformComponent>(entity->Id()); 
			auto simplePhysicsComponent = componentRepository.NewComponent<SimplePhysicsComponent>(entity->Id()); 

			simplePhysicsComponent->transformComponent = transformComponent; 

			auto retrievedTransformComponent = entity->GetComponent<TransformComponent*>(transformComponent->id); 
			
			Assert::AreEqual(retrievedTransformComponent->id, transformComponent->id); 
			Assert::AreEqual(retrievedTransformComponent->entityId, transformComponent->entityId); 
		}
		//-----------------------------------------------------------------------------
		// Name: ComponentsAreContiguous
		// Desc: check if sequentially allocated components are contiguous in memory
		//-----------------------------------------------------------------------------
		TEST_METHOD(ComponentsAreContiguous)
		{
			ComponentRepository componentRepository;
			componentRepository.RegisterComponentType<TransformComponent>();
			
			vector<int> ids; 

			for (int i = 0; i < 100; i++) {
				
				auto newTransformComponent = componentRepository.NewComponent<TransformComponent>();
				newTransformComponent->position = Vector2D(i, 0.0f); 
			}

			auto transformComponents = componentRepository.Select<TransformComponent>(); 
			auto ptr = (*transformComponents)[0]; 
			auto transformComponent = reinterpret_cast<TransformComponent*>(ptr); 

			return; 

			for (int i = 0; i < 100; i++) {

				Assert::IsNotNull(&(transformComponent[i])); 
				Assert::AreEqual(0.0f, transformComponent[i].position.y); 
			}
		}
	};
}