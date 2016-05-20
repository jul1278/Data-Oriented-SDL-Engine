#include "stdafx.h"
#include "CppUnitTest.h"

#include <vector>
#include <Utility/Vector.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace VectorTests
{
	TEST_CLASS(VectorTest)
	{
	public:

		TEST_METHOD(VectorCompoundAdditionTest)
		{
			auto a = Vector2D(10.0f, 5.0f); 
			auto b = Vector2D(1.0f, 2.0f); 

			b += a; 

			Assert::AreEqual(b.x, 11.0f);
			Assert::AreEqual(b.y, 7.0f);
		}

		TEST_METHOD(VectorCompoundScalarMultiplicationTest)
		{
			auto a = Vector2D(5.0f, 5.0f); 
			auto b = 2.0f; 

			a *= b;

			Assert::AreEqual(a.x, 10.0f);
			Assert::AreEqual(a.y, 10.f); 
		}

		TEST_METHOD(VectorEqualityAndInequalityTest)
		{
			auto a = Vector2D(5.0f, 5.0f); 
			auto b = Vector2D(5.0f, 5.0f); 
			auto c = Vector2D(0.0f, 0.0f); 

			Assert::IsTrue(a == b); 
			Assert::IsFalse(a == c); 
		}
	};
}