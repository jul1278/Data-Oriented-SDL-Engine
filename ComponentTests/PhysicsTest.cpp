#include "stdafx.h"
#include "CppUnitTest.h"
#include "Utility/Vector.h"
#include "Components/ComponentCollectionRepository.h"
#include "Physics/Physics.h"
#include "Components/PhysicsComponent.h"
#include "Components/TransformComponent.h"
#include "Components/VelocityComponent.h"
#include <Physics/CollisionPhysicsTask.h>
#include <Physics/VelocityTask.h>

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
		// Name: VelocityTaskTest
		// Desc:
		//------------------------------------------------------------------------------------
		TEST_METHOD(VelocityTaskTest)
		{
			ComponentCollectionRepository components; 
			Physics physics = Physics(1000, 1000); 

			components.NewCollection("Collection1");
			components.NewCollection("Collection2");

			for (auto i = 0; i < 100; i++) {
				auto transform = components.NewComponent<TransformComponent>("Collection1");
				auto physicsComponent = components.NewComponent<PhysicsComponent>("Collection1");
				
				transform->position = Vector2D(i*5.0f, i*5.0f); 
				transform->orientation = Vector2D(i*5.0f, i*5.0f);

				physicsComponent->transformComponentId = transform->id; 
				physicsComponent->acceleration = Vector2D(1.5f, 1.5f);
				physicsComponent->velocity = Vector2D(1.0f, 1.0f); 
				physicsComponent->angularAcceleration = 1.0f; 
				physicsComponent->angularVelocity = 2.0f; 
			}

			for (auto i = 0; i < 20; i++) {
				auto transform = components.NewComponent<TransformComponent>("Collection2");
				auto physicsComponent = components.NewComponent<PhysicsComponent>("Collection2");

				transform->position = Vector2D(i*5.0f, i*5.0f);
				transform->orientation = Vector2D(i*5.0f, i*5.0f);

				physicsComponent->transformComponentId = transform->id;
				physicsComponent->acceleration = Vector2D(1.0f, 1.0f);
				physicsComponent->velocity = Vector2D(1.0f, 1.0f);
				//physicsComponent->angularAcceleration = 1.0f;
				//physicsComponent->angularVelocity = 2.0f;
			}

			physics.AddPhysicsTask(new VelocityTask("Collection1"));
			physics.AddPhysicsTask(new VelocityTask("Collection2"));

			physics.ExecuteTasks(&components); 

			auto transformComponents1 = components.SelectFromCollection<TransformComponent>("Collection1"); 
			auto transformComponents2 = components.SelectFromCollection<TransformComponent>("Collection2"); 

			for (auto i = 0; i < 100; i++) {

				auto component = (*transformComponents1)[i];
				auto expected = Vector2D((i*5.0f) + 1.0f + 1.5f, (i*5.0f) + 1.0f + 1.5f); 

				auto expectedAngle = Vector2D((i*5.0f), (i*5.0f)); 
				expectedAngle += (2.0f + 1.0f); 

				Assert::AreEqual(component.position.x, expected.x);
				Assert::AreEqual(component.position.y, expected.y);

				Assert::AreEqual(component.orientation.Angle(), expectedAngle.Angle()); 
			}

			for (auto i = 0; i < 20; i++) {

				auto component = (*transformComponents2)[i];
				auto expected = Vector2D((i*5.0f) + 1.0f + 1.0f, (i*5.0f) + 1.0f + 1.0f);

				Assert::AreEqual(component.position.x, expected.x);
				Assert::AreEqual(component.position.y, expected.y);
			}

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
			this->onCollisionSuccess = true;
		}
	};
}