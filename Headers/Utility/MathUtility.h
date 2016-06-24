//
// Created by Julian  on 27/02/16.
//

#ifndef MATH_UTILITY_H
#define MATH_UTILITY_H

#include "Utility/Vector.h"

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
	//---------------------------------------------------------------------------
	// Name: RandomIntUniformDist
	// Desc: returns a random integer
	//---------------------------------------------------------------------------
	static int RandomIntUniformDist()
	{
		static random_device randomDevice;
		static default_random_engine defaultRandomEngine(randomDevice()); 

		uniform_int_distribution<int> uniformIntDistribution(0, INT_MAX); 

		return uniformIntDistribution(defaultRandomEngine); 
	}
	//---------------------------------------------------------------------------
	// Name: RotateVector
	// Desc: 
	//---------------------------------------------------------------------------
	static Vector2D RotateVector(const Vector2D& vector, const float angle)
	{
		Vector2D v = Vector2D(vector.x*cosf(angle) + vector.y*sinf(angle), -vector.x*sinf(angle) + vector.y*cosf(angle)); 
		return v; 
	}
	//---------------------------------------------------------------------------
	// Name: Generate Id
	// Desc: 
	//---------------------------------------------------------------------------
	static unsigned int GenerateId()
	{
		static unsigned id = 0;
		return id++; 
	}

};

#endif // MATH_UTILITY_H