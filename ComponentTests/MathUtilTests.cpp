#include "stdafx.h"
#include "CppUnitTest.h"

#include <Utility/MathUtility.h>
#include <vector>
#include <map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std; 

namespace ComponentTests
{
	TEST_CLASS(MathUtilTests)
	{
	public:
	
		//-----------------------------------------------------------------------------
		// Name: StdNormalDistHasZeroMean
		// Desc: 
		//-----------------------------------------------------------------------------
		TEST_METHOD(StdNormalDistHasZeroMean)
		{
			const int numSamples = 10000;
			const float threshold = 0.05f; 

			float cumulativeSum = 0.0f; 
			
			for (auto i = 0; i < numSamples; i++) {
				auto sample = MathUtility::RandomFloatStdNormalDist();
				cumulativeSum += sample;
			}

			cumulativeSum /= numSamples; 
			Assert::IsTrue(cumulativeSum < threshold); 
		}
	};
}