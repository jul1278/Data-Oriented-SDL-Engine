#include "Components/Repository/ComponentRepository.h"
#include "Components/GraphicsComponent.h"
#include "Components/TransformComponent.h"
#include "Components/PhysicsComponent.h"

#include <list>
#include <gtest/gtest.h>

//-------------------------------------------------------------------------
// Name: MultipleCollections
// Desc:
//-------------------------------------------------------------------------
TEST(ComponentRepositoryTests, MultipleCollections)
{
	ComponentRepository componentRepository("Test1");

	componentRepository.NewCollection("Test2");
	componentRepository.NewCollection("Test3");

	EXPECT_TRUE(componentRepository.ContainsCollection("Test1"));
	EXPECT_TRUE(componentRepository.ContainsCollection("Test2"));
	EXPECT_TRUE(componentRepository.ContainsCollection("Test3"));
	EXPECT_FALSE(componentRepository.ContainsCollection("Test4"));
}
//-------------------------------------------------------------------------
// Name: AddComponent
// Desc:
//-------------------------------------------------------------------------
TEST(ComponentRepositoryTests, AddComponent)
{
	ComponentRepository componentRepository("Test");

	EXPECT_EQ(componentRepository.ContainsCollection("Test"), true);

	for (auto i = 0; i < 100; i++) {

		auto component = componentRepository.NewComponent<TransformComponent>();
		
		EXPECT_NE(component, nullptr);
		EXPECT_EQ(component->id, i);  
	}

	auto result = componentRepository.Select<TransformComponent>();
	EXPECT_EQ(result.Size(), 100); 
}
//-------------------------------------------------------------------------
// Name: AddComponentToNonExistantCollection
// Desc:
//-------------------------------------------------------------------------
TEST(ComponentRepositoryTests, AddComponentToNonExistantCollection)
{
	ComponentRepository componentRepository("Test");

	auto component = componentRepository.NewComponent<TransformComponent>("NonExistantCollection");
	EXPECT_EQ(component, nullptr); 

	auto result = componentRepository.Select<TransformComponent>();
	EXPECT_EQ(result.Size(), 0); 
}
//-------------------------------------------------------------------------
// Name: AddComponentToNonExistantCollection
// Desc:
//-------------------------------------------------------------------------
TEST(ComponentRepositoryTests, AddMultipleComponentTypes)
{
	ComponentRepository componentRepository("Test");

	auto transformComponent = componentRepository.NewComponent<TransformComponent>("Test");
	auto baseComponent = componentRepository.NewComponent<BaseComponent>("Test");
	auto graphicsComponent = componentRepository.NewComponent<GraphicsComponent>("Test");

	EXPECT_TRUE(transformComponent != nullptr);
	EXPECT_TRUE(baseComponent != nullptr);
	EXPECT_TRUE(graphicsComponent != nullptr); 
}
//-------------------------------------------------------------------------
// Name: RemoveId
// Desc:
//-------------------------------------------------------------------------
TEST(ComponentRepositoryTests, RemoveId)
{
	ComponentRepository componentRepository("Test");
	
	for (auto i = 0; i < 100; i++) {

		auto component = componentRepository.NewComponent<TransformComponent>("Test"); 
		auto collection = componentRepository.Select<TransformComponent>();

		EXPECT_EQ(collection.Size(), 1); 

		auto id = component->id; 

		componentRepository.Remove(component->id); 
		EXPECT_EQ(collection.Size(), 0); 
		EXPECT_TRUE(collection.empty());

		auto selectComponent = componentRepository.SelectId(id);
		EXPECT_EQ(selectComponent, nullptr); 
	}
}
//-------------------------------------------------------------------------
// Name: SelectFromChildCollection
// Desc:
//-------------------------------------------------------------------------
TEST(ComponentRepositoryTests, SelectFromChildCollection)
{
	ComponentRepository componentRepository("Test");

	componentRepository.NewCollection("Child1");
	componentRepository.NewCollection("Child2"); 

	componentRepository.NewComponent<GraphicsComponent>("Child1");
	componentRepository.NewComponent<GraphicsComponent>("Child1");

	componentRepository.NewComponent<GraphicsComponent>("Child2");
	componentRepository.NewComponent<GraphicsComponent>("Child2");
	componentRepository.NewComponent<GraphicsComponent>("Child2");

	auto selectionFromChild1 = componentRepository.Select<GraphicsComponent>("Child1"); 
	auto selectionFromChild2 = componentRepository.Select<GraphicsComponent>("Child2");
	auto selectionFromParent = componentRepository.Select<GraphicsComponent>();

	auto invalidSelectionFromChild1 = componentRepository.Select<TransformComponent>("Child1"); 
	auto invalidSelectionFromChild2 = componentRepository.Select<TransformComponent>("Child2"); 
	auto invalidSelectionFromParent = componentRepository.Select<TransformComponent>(); 

	EXPECT_EQ(selectionFromChild1.Size(), 2);
	EXPECT_EQ(selectionFromChild2.Size(), 3);
	EXPECT_EQ(selectionFromParent.Size(), 5);

	EXPECT_EQ(invalidSelectionFromChild1.Size(), 0);
	EXPECT_EQ(invalidSelectionFromChild2.Size(), 0);
	EXPECT_EQ(invalidSelectionFromParent.Size(), 0);
}
//-------------------------------------------------------------------------
// Name: RemoveId
// Desc:
//-------------------------------------------------------------------------
TEST(ComponentRepositoryTests, SelectId)
{
	ComponentRepository componentRepository("Test"); 

	auto component1 = componentRepository.NewComponent<GraphicsComponent>(); 
	auto component2 = componentRepository.SelectId<GraphicsComponent>(component1->id);
	auto component3 = componentRepository.SelectId(100);  

	EXPECT_EQ(component3, nullptr); 
	EXPECT_EQ(component1->id, component2->id);
}
//-------------------------------------------------------------------------
// Name: RemoveEntityId
// Desc:
//-------------------------------------------------------------------------
TEST(ComponentRepositoryTests, RemoveEntityId)
{
	ComponentRepository componentRepository("Test1");

	componentRepository.NewCollection("Test2");
	componentRepository.NewCollection("Test3");

	auto entityId = componentRepository.GenerateId(); 

	auto physicsComponent = componentRepository.NewComponent<PhysicsComponent>("Test2", entityId); 
	auto transformComponent = componentRepository.NewComponent<TransformComponent>("Test2", entityId);
	auto graphicsComponent = componentRepository.NewComponent<GraphicsComponent>("Test2", entityId);

	componentRepository.RemoveEntity(entityId); 

	auto physicsComponents = componentRepository.Select<PhysicsComponent>(); 
	auto transformComponents = componentRepository.Select<TransformComponent>();
	auto graphicsComponents = componentRepository.Select<GraphicsComponent>();

	for (auto physicsComponent : physicsComponents) {}
	for (auto transformComponent : transformComponents) {}
	for (auto graphicsComponent : graphicsComponents) {}

	// TODO: 
	EXPECT_EQ(physicsComponents.Size(), 0);
	EXPECT_EQ(transformComponents.Size(), 0);
	EXPECT_EQ(graphicsComponents.Size(), 0); 
}
//-------------------------------------------------------------------------
// Name: RemoveEntityInsideLoop
// Desc:
//-------------------------------------------------------------------------
TEST(ComponentRepositoryTests, RemoveEntityInsideLoop)
{
	ComponentRepository componentRepository("Test1");

	auto entityId = componentRepository.GenerateId(); 

	auto transformComponent = componentRepository.NewComponent<TransformComponent>("Test2", entityId);
	auto graphicsComponent = componentRepository.NewComponent<GraphicsComponent>("Test2", entityId);

	componentRepository.NewComponent<TransformComponent>();
	componentRepository.NewComponent<GraphicsComponent>();
	componentRepository.NewComponent<TransformComponent>();
	componentRepository.NewComponent<GraphicsComponent>();

	auto transformComponents = componentRepository.Select<TransformComponent>();
	auto graphicsComponents = componentRepository.Select<GraphicsComponent>();

	for (auto transformComponent : transformComponents) {
		componentRepository.RemoveEntity(entityId); 	
	}

	for (auto transformComponent : transformComponents) {}
	for (auto graphicsComponent : graphicsComponents) {}

	// Should have removed 2 from each
	EXPECT_EQ(graphicsComponents.Size(), 2); 
	EXPECT_EQ(transformComponents.Size(), 2);
}
//-------------------------------------------------------------------------
// Name: RemoveEntityId
// Desc:
//-------------------------------------------------------------------------
