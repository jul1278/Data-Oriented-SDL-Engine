#include "Components/Repository/IComponentContainer.h"
#include "Components/GraphicsComponent.h"
#include "Components/TransformComponent.h"
#include "Components/PhysicsComponent.h"

#include <list>
#include <gtest/gtest.h>

//-------------------------------------------------------------------------
// Name: Initialise
// Desc:
//-------------------------------------------------------------------------
TEST(ComponentContainerTests, Initialise)
{
	ComponentContainer<TransformComponent> componentContainer; 

	EXPECT_EQ(componentContainer.components->capacity(), 100); 
}
//-------------------------------------------------------------------------
// Name: AddComponent
// Desc:
//-------------------------------------------------------------------------
TEST(ComponentContainerTests, AddComponent)
{
	ComponentContainer<TransformComponent> componentContainer; 

	componentContainer.Add();
	componentContainer.Add();
	componentContainer.Add();
	componentContainer.Add();

	EXPECT_EQ(componentContainer.components->size(), 4); 
}
//-------------------------------------------------------------------------
// Name: RemoveComponent
// Desc:
//-------------------------------------------------------------------------
TEST(ComponentContainerTests, RemoveComponent)
{
	ComponentContainer<TransformComponent> componentContainer; 

	auto component = componentContainer.Add();
	component->id = 56; 

	componentContainer.Remove(56); 

	EXPECT_EQ(componentContainer.components->size(), 0); 
}
