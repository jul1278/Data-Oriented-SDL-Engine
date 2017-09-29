#include "Utility/SpatialHashTable.h"
#include <list>
#include <gtest/gtest.h>

#include <algorithm>
#include <list>
#include <iostream>

//-------------------------------------------------------------------------
// Name: MultipleCollections
// Desc:
//-------------------------------------------------------------------------
TEST(SpatialHashTests, TestInsertAndQuery)
{
	SpatialHashTable<int> spatialHashTable(100, 100, 10, 10); 

	spatialHashTable.Hash(15, 15, 10, 10, 25); 

	auto result1 = spatialHashTable.Query(20, 20, 1, 1); 
	auto result2 = spatialHashTable.Query(26, 26, 1, 1);

	EXPECT_EQ(result1.size(), 1);
	EXPECT_EQ(result2.size(), 0);
}