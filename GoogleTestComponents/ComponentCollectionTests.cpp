#include "Components/Repository/IComponentContainer.h"
#include "Components/Repository/CComponentCollection.h"
#include "Components/GraphicsComponent.h"
#include "Components/TransformComponent.h"
#include "Components/PhysicsComponent.h"

#include <list>
#include <gtest/gtest.h>

//-------------------------------------------------------------------------------
// Name: CollectionSizeAfterAdd 
// Desc:
//-------------------------------------------------------------------------------
TEST(ComponentCollectionTests, CollectionSizeAfterAdd)
{
    ComponentContainer<TransformComponent> componentContainer; 
    Repository::ComponentCollection<TransformComponent> componentCollection(componentContainer);

    EXPECT_EQ(componentCollection.Size(), componentContainer.components->size());   

    componentContainer.Add();
    componentContainer.Add();
    componentContainer.Add();
    componentContainer.Add();

    EXPECT_EQ(componentContainer.components->size(), 4);
    EXPECT_EQ(componentCollection.Size(), componentContainer.components->size());   
}
//-------------------------------------------------------------------------------
// Name: CollectionSizeAfterRemove 
// Desc:
//-------------------------------------------------------------------------------
TEST(ComponentCollectionTests, CollectionSizeAfterRemove)
{
    auto componentContainer1 = new ComponentContainer<TransformComponent>(); 
    ComponentContainer<TransformComponent> componentContainer2;

    Repository::ComponentCollection<TransformComponent> componentCollection(*componentContainer1);
    componentCollection.Append(componentContainer2.components);

    componentContainer1->Add();
    componentContainer1->Add();
    componentContainer1->Add();

    componentContainer2.Add();
    componentContainer2.Add();
    componentContainer2.Add();
    componentContainer2.Add(); 

    EXPECT_EQ(componentContainer1->components->size() + componentContainer2.components->size(), 7);
    EXPECT_EQ(componentCollection.Size(), componentContainer1->components->size() + componentContainer2.components->size());

    delete componentContainer1; 

    EXPECT_EQ(componentCollection.Size(), componentContainer2.components->size());
}
//-------------------------------------------------------------------------------
// Name: SubscriptOperatorTest  
// Desc:
//-------------------------------------------------------------------------------
TEST(ComponentCollectionTests, SubscriptOperatorTest)
{
	ComponentContainer<TransformComponent> componentContainer; 
    Repository::ComponentCollection<TransformComponent> componentCollection1(componentContainer.components);
    Repository::ComponentCollection<TransformComponent> componentCollection2(componentContainer.components); 

    auto component1 = componentContainer.Add();
    auto component2 = componentContainer.Add();
    auto component3 = componentContainer.Add();
    auto component4 = componentContainer.Add();

    component1->id = 0;
    component2->id = 1; 
    component3->id = 2; 
    component4->id = 3; 

    EXPECT_EQ(componentCollection1[0].id, 0);
    EXPECT_EQ(componentCollection1[1].id, 1);
    EXPECT_EQ(componentCollection2[2].id, 2);
    EXPECT_EQ(componentCollection2[3].id, 3);

    component1->id = 4;
    component2->id = 5; 
    component3->id = 6; 
    component4->id = 7;     

    EXPECT_EQ(componentCollection1[0].id, 4);
    EXPECT_EQ(componentCollection1[1].id, 5);
    EXPECT_EQ(componentCollection2[2].id, 6);
    EXPECT_EQ(componentCollection2[3].id, 7);
}
//-------------------------------------------------------------------------------
// Name: CollectionCacheTest 
// Desc:
//-------------------------------------------------------------------------------
TEST(ComponentCollectionTests, CollectionCacheTest)
{
    ComponentContainer<TransformComponent> componentContainer1; 
    ComponentContainer<TransformComponent> componentContainer2;

    Repository::ComponentCollection<TransformComponent> componentCollection(componentContainer1.components);
    componentCollection.Append(componentContainer2.components);

    componentContainer1.Add();
    componentContainer1.Add();
    componentContainer1.Add();

    auto result1 = componentContainer2.Add();
    componentContainer2.Add();
    componentContainer2.Add();
    componentContainer2.Add(); 

    result1->id = 1; 

    auto result2 = componentCollection[3]; 

    EXPECT_EQ(componentCollection.Size(), 7);
    EXPECT_EQ(result1->id, result2.id); 
}


