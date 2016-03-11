#include "stdafx.h"
#include "CppUnitTest.h"
#include "Headers/Vector.h"

#include "Headers/ComponentCollectionRepository.h"
#include "Headers/Physics.h"

#include "Headers/Components/BaseComponent.h"
#include "Headers/Components/TransformComponent.h"
#include "Headers/Components/SimplePhysicsComponent.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PhysicsTest
{
	TEST_CLASS(PhysicsTest)
	{
	public:

		TEST_METHOD(SolveSimplePhysicsTest)
		{
			const string testCollectionName = "TestCollection";

			ComponentCollectionRepository componentCollectionRepository; 
			Physics physics; 

			componentCollectionRepository.NewCollection(testCollectionName); 
			
			auto simplePhysicsComponent = componentCollectionRepository.NewComponent<SimplePhysicsComponent>(testCollectionName);
			auto transformComponent = componentCollectionRepository.NewComponent<TransformComponent>(testCollectionName); 

			simplePhysicsComponent->transformComponent = transformComponent; 

			transformComponent->position = Vector2D(1.0f, 1.0f); 
			simplePhysicsComponent->velocity = Vector2D(1.0f, 1.0f); 

			physics.SolveSimplePhysics(&componentCollectionRepository, testCollectionName); 

			Assert::AreEqual(transformComponent->position.x, 2.0f); 
			Assert::AreEqual(transformComponent->position.y, 2.0f); 
		}

		TEST_METHOD(SolvePhysicsTest)
		{
			const string testCollectionName = "TestCollection";

			ComponentCollectionRepository componentCollectionRepository;
			Physics physics;

			componentCollectionRepository.NewCollection(testCollectionName);

			auto physicsComponent = componentCollectionRepository.NewComponent<PhysicsComponent>(testCollectionName);
			auto transformComponent = componentCollectionRepository.NewComponent<TransformComponent>(testCollectionName);

			physicsComponent->transformComponent = transformComponent;

			transformComponent->position = Vector2D(1.0f, 1.0f);
			transformComponent->orientation = Vector2D(0.0f, 0.0f); 

			physicsComponent->velocity = Vector2D(1.0f, 1.0f);
			physicsComponent->angularVelocity = 1.0f; 

			physics.SolvePhysics(&componentCollectionRepository, testCollectionName);
			
			auto angle = transformComponent->Angle(); 
			
			Assert::AreEqual(transformComponent->position.x, 2.0f);
			Assert::AreEqual(transformComponent->position.y, 2.0f);
			Assert::AreEqual(angle, 1.0f); 
		}

	};
}