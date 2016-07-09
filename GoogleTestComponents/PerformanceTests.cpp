#include <Components/ComponentCollectionRepository.h>
#include <Components/GraphicsComponent.h>
#include <Components/TransformComponent.h>
#include <Components/PhysicsComponent.h>
#include <list>
#include <chrono>
#include <iostream>
#include "gtest/gtest.h"


//-----------------------------------------------------------------------------
// Name: InsertComponentsPerfTest
// Desc: 		
//-----------------------------------------------------------------------------
TEST(PerformanceTest, InsertComponentsPerfTest)
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
TEST(PerformanceTest, InsertMultipleTypeComponentsPerfTest)
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
TEST(PerformanceTest, DeleteComponentsPerfTest)
{
	const auto numComponents = 5000;

	auto start = chrono::steady_clock::now();

	ComponentCollectionRepository componentCollectionRepository;

	vector<int> ids;

	componentCollectionRepository.NewCollection("TestCollection");

	for (auto i = 0; i < numComponents; ++i) {
		auto transformComponent = componentCollectionRepository.NewComponent<TransformComponent>("TestCollection");
		ids.push_back(transformComponent->id);
	}

	for (auto i = 0; i < numComponents; i++) {
		//auto str = to_string(ids[i]);
		//cout << str << endl;
		componentCollectionRepository.RemoveComponent(ids[i]);
	}
	
	auto end = chrono::steady_clock::now();
	auto t = chrono::duration<double, milli>(end - start).count();
	cout << t << endl;
}
