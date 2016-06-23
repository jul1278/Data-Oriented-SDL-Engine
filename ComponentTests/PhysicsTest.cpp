#include "stdafx.h"
#include "CppUnitTest.h"
#include "Utility/Vector.h"
#include "Components/ComponentCollectionRepository.h"
#include "Physics/Physics.h"
#include "Components/PhysicsComponent.h"
#include "Components/TransformComponent.h"
#include "Components/VelocityComponent.h"
#include <Physics/CollisionPhysicsTask.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std; 

namespace PhysicsTest
{
	TEST_CLASS(PhysicsTest)
	{
	private:

		bool onCollisionSuccess = false; 

	public:

		//------------------------------------------------------------------------------------
		// Name: SolveSimplePhysicsTest
		// Desc:
		//------------------------------------------------------------------------------------
		TEST_METHOD(SolveSimplePhysicsTest)
		{
			const string testCollectionName = "TestCollection";

			ComponentCollectionRepository componentCollectionRepository; 
			Physics physics(10.0f, 10.0f); 

			componentCollectionRepository.NewCollection(testCollectionName); 
			
			auto simplePhysicsComponent = componentCollectionRepository.NewComponent<VelocityComponent>(testCollectionName);
			auto transformComponent = componentCollectionRepository.NewComponent<TransformComponent>(testCollectionName); 

			simplePhysicsComponent->transformComponentId = transformComponent->id; 

			transformComponent->position = Vector2D(1.0f, 1.0f); 
			simplePhysicsComponent->velocity = Vector2D(1.0f, 1.0f); 

			physics.SolveSimplePhysics(&componentCollectionRepository, testCollectionName); 

			Assert::AreEqual(transformComponent->position.x, 2.0f); 
			Assert::AreEqual(transformComponent->position.y, 2.0f); 
		}
		//------------------------------------------------------------------------------------
		// Name: SolvePhysicsTest
		// Desc:
		//------------------------------------------------------------------------------------
		TEST_METHOD(SolvePhysicsTest)
		{
			const string testCollectionName = "TestCollection";

			ComponentCollectionRepository componentCollectionRepository;
			Physics physics(10.0f,10.0f);

			componentCollectionRepository.NewCollection(testCollectionName);

			auto physicsComponent = componentCollectionRepository.NewComponent<PhysicsComponent>(testCollectionName);
			auto transformComponent = componentCollectionRepository.NewComponent<TransformComponent>(testCollectionName);

			physicsComponent->transformComponentId = transformComponent->id;

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
		//------------------------------------------------------------------------------------
		// Name: PhysicsTaskCollisionTest
		// Desc:
		//------------------------------------------------------------------------------------
		TEST_METHOD(PhysicsTaskCollisionTest)
		{
			this->onCollisionSuccess = false; 

			auto collection1Name = string("Collection1");
			auto collection2Name = string("Collection2");

			auto componentCollectionRepository = ComponentCollectionRepository(); 

			componentCollectionRepository.NewCollection(collection1Name);
			componentCollectionRepository.NewCollection(collection2Name); 

			auto trans1 = componentCollectionRepository.NewComponent<TransformComponent>(collection1Name);
			auto phys1 = componentCollectionRepository.NewComponent<PhysicsComponent>(collection1Name);

			auto trans2 = componentCollectionRepository.NewComponent<TransformComponent>(collection2Name);
			auto phys2 = componentCollectionRepository.NewComponent<PhysicsComponent>(collection2Name); 

			trans1->position = Vector2D(0.0f, 1.0f); 
			phys1->radius = 2.0f; 
			phys1->transformComponentId = trans1->id; 
			
			trans2->position = Vector2D(1.0f, 1.0f); 
			phys2->radius = 2.0f; 
			phys2->transformComponentId = trans2->id; 

			auto physics = Physics(10, 10); 

			auto physicsTask = new CollisionPhysicsTask("Collection1", "Collection2"); 

			physics.AddPhysicsTask(physicsTask); 

			physicsTask->RegisterListener<CollisionEventArgs>(bind(&PhysicsTest::OnCollision, this, placeholders::_1));

			physics.ExecuteTasks(&componentCollectionRepository); 

			Assert::IsTrue(this->onCollisionSuccess); 
		}
		//------------------------------------------------------------------------------------
		// Name: PhysicsTaskNoCollisionTest
		// Desc:
		//------------------------------------------------------------------------------------
		TEST_METHOD(PhysicsTaskNoCollisionTest)
		{
			this->onCollisionSuccess = false;

			auto collection1Name = string("Collection1");
			auto collection2Name = string("Collection2");

			auto componentCollectionRepository = ComponentCollectionRepository();

			componentCollectionRepository.NewCollection(collection1Name);
			componentCollectionRepository.NewCollection(collection2Name);

			auto trans1 = componentCollectionRepository.NewComponent<TransformComponent>(collection1Name);
			auto phys1 = componentCollectionRepository.NewComponent<PhysicsComponent>(collection1Name);

			auto trans2 = componentCollectionRepository.NewComponent<TransformComponent>(collection2Name);
			auto phys2 = componentCollectionRepository.NewComponent<PhysicsComponent>(collection2Name);

			trans1->position = Vector2D(0.0f, 0.0f);
			phys1->radius = 0.1f;
			phys1->transformComponentId = trans1->id;

			trans2->position = Vector2D(1.0f, 1.0f);
			phys2->radius = 0.1f;
			phys2->transformComponentId = trans2->id;

			auto physics = Physics(10, 10);

			auto physicsTask = new CollisionPhysicsTask("Collection1", "Collection2"); 

			physics.AddPhysicsTask(physicsTask);

			physicsTask->RegisterListener<CollisionEventArgs>(bind(&PhysicsTest::OnCollision, this, placeholders::_1));

			physics.ExecuteTasks(&componentCollectionRepository);

			Assert::IsTrue(!this->onCollisionSuccess);
		}
		void OnCollision(const CollisionEventArgs& collisionEventArgs)
		{
			if (collisionEventArgs.physicsComponent1 != nullptr) {
				if (collisionEventArgs.physicsComponent2 != nullptr) {
					this->onCollisionSuccess = true;
				}
			}
		}
	};
}