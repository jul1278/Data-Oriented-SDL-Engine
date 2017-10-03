#include "Utility/SpatialHashTable.h"
#include <list>
#include <gtest/gtest.h>

#include <algorithm>
#include <list>
#include <functional>
#include <iostream>

bool wasCalled = false; 

void TestFunction()
{
	wasCalled = true;
}
//-------------------------------------------------------------------------
// Name: TestInsertAndQuery
// Desc:
//-------------------------------------------------------------------------
TEST(SpatialHashTests, TestInsertAndQuery)
{
	SpatialHashTable<int> spatialHashTable(100, 100, 10, 10); 

	spatialHashTable.Hash(15, 15, 10, 10, 25); 

	// we've hashed into buckets (1, 1), (1, 2), (2,1), (2,2)

	auto result1 = spatialHashTable.Query(20, 20, 1, 1); 
	auto result2 = spatialHashTable.Query(26, 26, 1, 1);
	auto result3 = spatialHashTable.Query(30, 22, 1, 1); 
	auto result4 = spatialHashTable.Query(0, 0, 100, 100); 

	EXPECT_EQ(result1.size(), 1);
	EXPECT_EQ(result2.size(), 1);
	EXPECT_EQ(result3.size(), 0);
	EXPECT_EQ(result4.size(), 1);
}
//-------------------------------------------------------------------------
// Name: TestInsertAndQueryFunction
// Desc:
//-------------------------------------------------------------------------
TEST(SpatialHashTests, TestInsertAndQueryFunction)
{
	SpatialHashTable<const std::function<void(void)>> spatialHashTable(100, 100, 10, 10);
	spatialHashTable.Hash(15, 15, 10, 10, TestFunction);

	auto result1 = spatialHashTable.Query(20, 20, 1, 1);
	
	for (auto r : result1) {
		r->obj(); 
	}

	EXPECT_TRUE(wasCalled); 
	EXPECT_EQ(result1.size(), 1);
}
//-------------------------------------------------------------------------
// Name: TestInsertAndQueryPoint
// Desc:
//-------------------------------------------------------------------------
TEST(SpatialHashTests, TestInsertAndQueryPoint)
{
	SpatialHashTable<int> spatialHashTable(100, 100, 10, 10);

	spatialHashTable.Hash(76, 34, 2, 2, 25);

	auto result = spatialHashTable.Query(77, 34);
	
	ASSERT_EQ(result.size(), 1);
	EXPECT_EQ(result.front()->obj, 25); 
}
