#include "Utility/MathUtility.h"
#include "gtest/gtest.h"

#include <vector>
#include <map>

using namespace std; 

//-----------------------------------------------------------------------------
// Name: StdNormalDistHasZeroMean
// Desc: 
//-----------------------------------------------------------------------------
TEST(MathUtilTests, StdNormalDistHasZeroMean)
{
	const auto numSamples = 10000;
	const auto threshold = 0.05f; 

	auto cumulativeSum = 0.0f; 
			
	for (auto i = 0; i < numSamples; i++) {
		auto sample = MathUtility::RandomFloatStdNormalDist();
		cumulativeSum += sample;
	}

	cumulativeSum /= numSamples; 
	EXPECT_TRUE(cumulativeSum < threshold); 
}
//-----------------------------------------------------------------------------
// Name: StdNormalDistHasZeroMean
// Desc: 
//-----------------------------------------------------------------------------
TEST(MathUtilTests, ParseFloat)
{
	const auto str1 = "43.21"; 
	const auto str2 = "34.12304";

	auto result1 = MathUtility::ParseFloat(str1); 
	auto result2 = MathUtility::ParseFloat(str2); 

	EXPECT_EQ(result1, 43.21f); 
	EXPECT_EQ(result2, 34.12304f); 
}

	
