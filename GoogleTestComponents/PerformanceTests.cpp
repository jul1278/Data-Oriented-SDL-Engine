#include <Components/ComponentCollectionRepository.h>
#include <Components/GraphicsComponent.h>
#include <Components/TransformComponent.h>
#include <Components/PhysicsComponent.h>
#include <list>
#include <chrono>
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"

#ifdef _WIN32
#include "Windows.h"
#else

#ifdef  __APPLE__

#endif

#endif 

void PerformanceTime(double testTime)
{
	auto currentTestName = ::testing::UnitTest::GetInstance()->current_test_info()->name();

	string fileName; 
	fileName += "..//PerformanceResults//";
	fileName += currentTestName;
	fileName += ".csv";

	// check there exists a file "/PerformanceResults/*currentTestName*.csv"
	ifstream file(fileName); 

	if (!file.good()) {

		//
		CreateDirectory(L"..//PerformanceResults", nullptr); 

		// create the file
		ofstream newFile(fileName); 

		newFile << "Date/Time, Test Time (ms)" << endl; 
		newFile.close(); 
	}

	ofstream writeFile(fileName, ofstream::out | ofstream::app); 

	if (writeFile.good()) {
		char timeBuffer[32]; 
		tm localTimeBuffer; 
		auto currentTime = time(nullptr); 
		
		localtime_s(&localTimeBuffer, &currentTime); 
		asctime_s(timeBuffer, 32, &localTimeBuffer); 

		string currentDateTime(timeBuffer);

		auto newLine = currentDateTime.find('\n');
		currentDateTime.replace(newLine, newLine + 1, ""); 

		writeFile << currentDateTime << ", " << testTime << endl;
	}

	writeFile.close(); 
}
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

	PerformanceTime(t); 
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

	PerformanceTime(t); 
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
		componentCollectionRepository.RemoveComponent(ids[i]);
	}
	
	auto end = chrono::steady_clock::now();
	auto t = chrono::duration<double, milli>(end - start).count();
	
	PerformanceTime(t); 
}
