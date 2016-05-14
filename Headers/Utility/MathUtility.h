//
// Created by Julian  on 27/02/16.
//

#ifndef MATH_UTILITY_H
#define MATH_UTILITY_H

#include "Utility/Vector.h"

#include <math.h>
#include <random>
#include <algorithm>

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
	// Name: RandInt
	// Desc: returns a random integer from an interval
	//---------------------------------------------------------------------------
	static int RandInt(int left, int right, int step = 1) 
	{ 

		if (left > right)
			swap(left, right);
	
		if (step <= 0 || left == right || abs(left) + abs(right) < step)
			return left;
	
		int aright = abs(right);
		int aleft = abs(left);
	
		if (aleft > aright)
			swap(aleft, aright);
	
		int r = 1;
		int c = 0;
	
		if (right <= 0 || left >= 0) {
			left >= 0 ? r = 1 : r = -1;
			r *= rand() % (aright - aleft) + aleft;
		}
		else {
			aright += aleft;
			aleft = 0;
			r *= rand() % (aright - aleft) - abs(left);
			c = abs(left);
		}
	
		r += c;
	
		if (rand() % 2) {
			r = (r / step) * step;
			r = max(r, left);
		}
		else {
			r = (r / step + 1) * step;
			r = min(r, right + c);
		}
	
		r -= c;
	
		return r;
	}
};

#endif // MATH_UTILITY_H
