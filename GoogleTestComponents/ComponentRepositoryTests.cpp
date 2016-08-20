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
// Name: AddComponentToNonExistantCollection
// Desc:
//-------------------------------------------------------------------------
TEST(ComponentRepositoryTests, IdsAreCorrect)
{
	ComponentRepository componentRepository("Test");
}
