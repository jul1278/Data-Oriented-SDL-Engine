// ComponentCollectionIteratorTests.cpp
#include "Components/Repository/IComponentContainer.h"
#include "Components/Repository/CComponentCollection.h"
#include "Components/Repository/ComponentCollectionIterator.h"
#include "Components/GraphicsComponent.h"
#include "Components/TransformComponent.h"
#include "Components/PhysicsComponent.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>

//----------------------------------------------------------------
// Name: ForLoopIterate
// Desc:
//----------------------------------------------------------------
TEST(ComponentCollectionIteratorTests, ForLoopIterate)
{
    ComponentContainer<TransformComponent> componentContainer1; 
    ComponentContainer<TransformComponent> componentContainer2; 
    Repository::ComponentCollection<TransformComponent> componentCollection(componentContainer1.components);
    componentCollection.Append(componentContainer2.components);

    componentContainer1.Add();
    componentContainer1.Add();
    componentContainer1.Add();
    componentContainer1.Add();

    componentContainer2.Add();
    componentContainer2.Add();
    componentContainer2.Add();
    componentContainer2.Add();

    int counter = 0;

	for (auto& component : componentCollection) {
		component.id = 5;
		counter++; 
	}

	for (auto& component : componentCollection) {
		EXPECT_EQ(component.id, 5);
	}	

	EXPECT_EQ(counter, 8);
}
//----------------------------------------------------------------
// Name: BeginIsNotEnd
// Desc:
//----------------------------------------------------------------
TEST(ComponentCollectionIteratorTests, BeginIsNotEnd)
{
    ComponentContainer<TransformComponent> componentContainer; 
    Repository::ComponentCollection<TransformComponent> componentCollection(componentContainer.components);

    componentContainer.Add();
    componentContainer.Add();
    componentContainer.Add();
    componentContainer.Add();

    auto begin = componentCollection.begin(); 
    auto end = componentCollection.end(); 

    EXPECT_NE(begin, end); 
}
//----------------------------------------------------------------
// Name: STLFind_if
// Desc:
//----------------------------------------------------------------
TEST(ComponentCollectionIteratorTests, STLFind_if)
{
    ComponentContainer<TransformComponent> componentContainer; 
    Repository::ComponentCollection<TransformComponent> componentCollection(componentContainer.components);

    componentContainer.Add();
    componentContainer.Add();
    auto component = componentContainer.Add();
    componentContainer.Add();

    component->id = 10; 

    auto it = componentCollection.begin();
    it++; 
    it++;

    auto result = find_if(componentCollection.begin(), componentCollection.end(), 
	[](const TransformComponent& t)
	{
		return (t.id == 10);
	});

    EXPECT_NE(result, componentCollection.end()); 
    EXPECT_EQ(result, it);
}

