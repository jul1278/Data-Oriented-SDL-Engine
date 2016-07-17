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
	
