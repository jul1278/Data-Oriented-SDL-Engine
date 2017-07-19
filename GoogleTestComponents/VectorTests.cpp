#include "gtest/gtest.h"
#include "Utility/Vector.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

TEST(VectorTest, VectorCompoundAdditionTest)
{
	auto a = Vector2D(10.0f, 5.0f); 
	auto b = Vector2D(1.0f, 2.0f); 

	b += a; 

	EXPECT_EQ(b.x, 11.0f);
    EXPECT_EQ(b.y, 7.0f);
}

TEST(VectorTest, VectorCompoundScalarMultiplicationTest)
{
	auto a = Vector2D(5.0f, 5.0f); 
	auto b = 2.0f; 

	a *= b;

    EXPECT_EQ(a.x, 10.0f);
    EXPECT_EQ(a.y, 10.0f);
}

TEST(VectorTest, VectorEqualityAndInequalityTest)
{
	auto a = Vector2D(5.0f, 5.0f); 
	auto b = Vector2D(5.0f, 5.0f); 
	auto c = Vector2D(0.0f, 0.0f); 

    EXPECT_FALSE(a == c);
    EXPECT_TRUE(a == b);
}
