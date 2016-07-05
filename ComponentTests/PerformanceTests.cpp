#include "stdafx.h"
#include "CppUnitTest.h"
#include <Components/ComponentCollectionRepository.h>
#include <Components/GraphicsComponent.h>
#include <Components/TransformComponent.h>
#include <Components/PhysicsComponent.h>
#include <list>
#include <chrono>
#include <iostream>
#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PerformanceTests
{
	TEST_CLASS(PerformanceTest)
	{
	public:

		//-----------------------------------------------------------------------------
		// Name: InsertComponentsPerfTest
		// Desc: 		
		//-----------------------------------------------------------------------------
		TEST_METHOD(InsertComponentsPerfTest)
		{
			const auto numComponents = 5000; 

			auto start = chrono::steady_clock::now();

			ComponentCollectionRepository componentCollectionRepository;
			auto entityId = componentCollectionRepository.NewEntityId();
			componentCollectionRepository.NewCollection("TestCollection");

			for (auto i = 0; i < numComponents; ++i)
			{
				auto transformComponent = componentCollectionRepository.NewComponent<TransformComponent>("TestCollection");
			}

			auto end = chrono::steady_clock::now(); 

			auto t = chrono::duration<double, milli>(end - start).count(); 

			cout << t << endl;
		}
		//-----------------------------------------------------------------------------
		// Name: InsertMultipleTypeComponentsPerfTest
		// Desc: 		
		//-----------------------------------------------------------------------------
		TEST_METHOD(InsertMultipleTypeComponentsPerfTest)
		{
			const auto numComponents = 5000;

			auto start = chrono::steady_clock::now();

			ComponentCollectionRepository componentCollectionRepository;
			auto entityId = componentCollectionRepository.NewEntityId();
			componentCollectionRepository.NewCollection("TestCollection");

			for (auto i = 0; i < numComponents; ++i)
			{
				auto transformComponent = componentCollectionRepository.NewComponent<TransformComponent>("TestCollection");
				auto graphicsComponent = componentCollectionRepository.NewComponent<GraphicsComponent>("TestCollection"); 
			}

			auto end = chrono::steady_clock::now();

			auto t = chrono::duration<double, milli>(end - start).count();

			cout << t << endl;
		}
		//-----------------------------------------------------------------------------
		// Name: InsertMultipleTypeComponentsPerfTest
		// Desc: 		
		//-----------------------------------------------------------------------------
		TEST_METHOD(DeleteComponentsPerfTest)
		{
			const auto numComponents = 5000;

			auto start = chrono::steady_clock::now();

			ComponentCollectionRepository componentCollectionRepository;

			vector<int> ids; 

			auto entityId = componentCollectionRepository.NewEntityId();
			componentCollectionRepository.NewCollection("TestCollection");

			for (auto i = 0; i < numComponents; ++i) {
				auto transformComponent = componentCollectionRepository.NewComponent<TransformComponent>("TestCollection");
				ids.push_back(transformComponent->id); 
			}

			for (auto i = 0; i < numComponents; i++) {
				auto wstr = to_wstring(ids[i]);
				Logger::WriteMessage(wstr.c_str());
				componentCollectionRepository.RemoveComponent(ids[i]); 
			}

			auto end = chrono::steady_clock::now();
			auto t = chrono::duration<double, milli>(end - start).count();
			cout << t << endl;
		}
	};
}