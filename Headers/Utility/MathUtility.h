//
// Created by Julian  on 27/02/16.
//

#ifndef MATH_UTILITY_H
#define MATH_UTILITY_H

#include <math.h>
#include <random>

using namespace std;

namespace MathUtility
{
	//---------------------------------------------------------------------------
	// Name: RandomFloatUniformDist
	// Desc: returns a float from [0.0, 1.0]
	//---------------------------------------------------------------------------
	static float RandomFloatUniformDist()
	{
		static random_device randomDevice;
		static default_random_engine defaultRandomEngine(randomDevice()); 

		uniform_real_distribution<float> uniformFloatDistribution(0.0f, 1.0f); 
		
		return uniformFloatDistribution(defaultRandomEngine); 
	}
	//---------------------------------------------------------------------------
	// Name: RandomFloatStdNormalDist
	// Desc: returns a float from [0.0, 1.0]
	//---------------------------------------------------------------------------
	static float RandomFloatStdNormalDist()
	{
		static random_device randomDevice; 
		static default_random_engine defaultRandomEngine(randomDevice()); 

		normal_distribution<float> stdNormalDistribution(0.0f, 1.0f); 

		return stdNormalDistribution(defaultRandomEngine); 
	}

};

#endif // MATH_UTILITY_H