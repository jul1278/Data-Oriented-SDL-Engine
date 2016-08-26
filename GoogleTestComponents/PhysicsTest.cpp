#include "Utility/Vector.h"
#include "Components/Repository/ComponentRepository.h"
#include "Physics/Physics.h"
#include "Components/PhysicsComponent.h"
#include "Components/TransformComponent.h"
#include "Components/VelocityComponent.h"
#include "Physics/CollisionPhysicsTask.h"
#include "Physics/VelocityTask.h"
#include "gtest/gtest.h"

using namespace std; 

bool onCollisionSuccess = false; 

void OnCollision(const CollisionEventArgs& collisionEventArgs)
{
    onCollisionSuccess = true;
}

//------------------------------------------------------------------------------------
// Name: SolveSimplePhysicsTest
// Desc:
//------------------------------------------------------------------------------------
TEST(PhysicsTest, SolveSimplePhysicsTest)
{
	const string testCollectionName = "TestCollection";

	ComponentRepository componentRepository(testCollectionName); 
	Physics physics(10.0f, 10.0f); 
			
	auto simplePhysicsComponent = componentRepository.NewComponent<VelocityComponent>(testCollectionName);
	auto transformComponent = componentRepository.NewComponent<TransformComponent>(testCollectionName); 

	simplePhysicsComponent->transformComponentId = transformComponent->id; 

	transformComponent->position = Vector2D(1.0f, 1.0f); 
	simplePhysicsComponent->velocity = Vector2D(1.0f, 1.0f); 

	physics.SolveSimplePhysics(&componentRepository, testCollectionName); 

	EXPECT_EQ(transformComponent->position.x, 2.0f); 
	EXPECT_EQ(transformComponent->position.y, 2.0f); 
}
//------------------------------------------------------------------------------------
// Name: SolvePhysicsTest
// Desc:
//------------------------------------------------------------------------------------
TEST(PhysicsTest, SolvePhysicsTest)
{
	const string testCollectionName = "TestCollection";

	ComponentRepository componentRepository("PhysicsTest");
	Physics physics(10.0f,10.0f);

	componentRepository.NewCollection(testCollectionName);

	auto physicsComponent = componentRepository.NewComponent<PhysicsComponent>(testCollectionName);
	auto transformComponent = componentRepository.NewComponent<TransformComponent>(testCollectionName);

	physicsComponent->transformComponentId = transformComponent->id;

	transformComponent->position = Vector2D(1.0f, 1.0f);
	transformComponent->orientation = Vector2D(0.0f, 0.0f); 

	physicsComponent->velocity = Vector2D(1.0f, 1.0f);
	physicsComponent->angularVelocity = 1.0f; 

	physics.SolvePhysics(&componentRepository, testCollectionName);
			
	auto angle = transformComponent->Angle(); 
			
	EXPECT_EQ(transformComponent->position.x, 2.0f);
	EXPECT_EQ(transformComponent->position.y, 2.0f);
	EXPECT_EQ(angle, 1.0f); 
}
//------------------------------------------------------------------------------------
// Name: PhysicsTaskCollisionTest
// Desc:
//------------------------------------------------------------------------------------
TEST(PhysicsTest, PhysicsTaskCollisionTest)
{
	onCollisionSuccess = false; 

	auto collection1Name = string("Collection1");
	auto collection2Name = string("Collection2");

	auto componentRepository = ComponentRepository("Test"); 

	componentRepository.NewCollection(collection1Name);
	componentRepository.NewCollection(collection2Name); 

	auto trans1 = componentRepository.NewComponent<TransformComponent>(collection1Name);
	auto phys1 = componentRepository.NewComponent<PhysicsComponent>(collection1Name);

	auto trans2 = componentRepository.NewComponent<TransformComponent>(collection2Name);
	auto phys2 = componentRepository.NewComponent<PhysicsComponent>(collection2Name); 

	trans1->position = Vector2D(0.0f, 1.0f); 
	phys1->radius = 2.0f; 
	phys1->transformComponentId = trans1->id; 
			
	trans2->position = Vector2D(1.0f, 1.0f); 
	phys2->radius = 2.0f; 
	phys2->transformComponentId = trans2->id; 

	auto physics = Physics(10, 10); 

	auto transCollection1 = componentRepository.Select<TransformComponent>(collection2Name);
	auto physCollection1 = componentRepository.Select<PhysicsComponent>(collection2Name);

	EXPECT_EQ(transCollection1.Size(), 1);
	EXPECT_EQ(physCollection1.Size(), 1); 

	// NOTE: Physics will clean this up
	auto physicsTask = new CollisionPhysicsTask(collection1Name, collection2Name); 
	physics.AddPhysicsTask(physicsTask); 

	physicsTask->RegisterListener<CollisionEventArgs>(bind(&OnCollision, placeholders::_1));

	physics.ExecuteTasks(&componentRepository); 

	EXPECT_TRUE(onCollisionSuccess); 
}
//------------------------------------------------------------------------------------
// Name: VelocityTaskTest
// Desc:
//------------------------------------------------------------------------------------
TEST(PhysicsTest, VelocityTaskTest)
{
	ComponentRepository components("Test"); 
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

	auto transformComponents1 = components.Select<TransformComponent>("Collection1"); 
	auto transformComponents2 = components.Select<TransformComponent>("Collection2"); 

	for (auto i = 0; i < 100; i++) {

		auto component = transformComponents1[i];
		auto expected = Vector2D((i*5.0f) + 1.0f + 1.5f, (i*5.0f) + 1.0f + 1.5f); 

		//auto expectedAngle = Vector2D((i*5.0f), (i*5.0f)); 
		//expectedAngle += (2.0f + 1.0f); 

		EXPECT_EQ(component.position.x, expected.x);
		EXPECT_EQ(component.position.y, expected.y);
		//EXPECT_EQ(component.orientation.Angle(), expectedAngle.Angle()); 
	}

	for (auto i = 0; i < 20; i++) {

		auto component = transformComponents2[i];
		auto expected = Vector2D((i*5.0f) + 1.0f + 1.0f, (i*5.0f) + 1.0f + 1.0f);

		EXPECT_EQ(component.position.x, expected.x);
		EXPECT_EQ(component.position.y, expected.y);
	}

}
//------------------------------------------------------------------------------------
// Name: PhysicsTaskNoCollisionTest
// Desc:
//------------------------------------------------------------------------------------
TEST(PhysicsTest, PhysicsTaskNoCollisionTest)
{
	onCollisionSuccess = false;

	auto collection1Name = string("Collection1");
	auto collection2Name = string("Collection2");

	ComponentRepository componentRepository("Test");

	componentRepository.NewCollection(collection1Name);
	componentRepository.NewCollection(collection2Name);

	auto trans1 = componentRepository.NewComponent<TransformComponent>(collection1Name);
	auto phys1 = componentRepository.NewComponent<PhysicsComponent>(collection1Name);

	auto trans2 = componentRepository.NewComponent<TransformComponent>(collection2Name);
	auto phys2 = componentRepository.NewComponent<PhysicsComponent>(collection2Name);

	trans1->position = Vector2D(0.0f, 0.0f);
	phys1->radius = 0.1f;
	phys1->transformComponentId = trans1->id;

	trans2->position = Vector2D(1.0f, 1.0f);
	phys2->radius = 0.1f;
	phys2->transformComponentId = trans2->id;

	auto physics = Physics(10, 10);

	auto physicsTask = new CollisionPhysicsTask("Collection1", "Collection2"); 

	physics.AddPhysicsTask(physicsTask);

	physicsTask->RegisterListener<CollisionEventArgs>(bind(&OnCollision, placeholders::_1));

	physics.ExecuteTasks(&componentRepository);

	EXPECT_FALSE(onCollisionSuccess);
}

