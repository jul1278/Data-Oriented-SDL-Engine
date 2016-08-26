#include "Components/Repository/ComponentCollectionRepository.h"
#include "Components/Repository/ComponentRepository.h"
#include "Components/GraphicsComponent.h"
#include "Components/TransformComponent.h"
#include "Components/PhysicsComponent.h"
#include "Utility/ProcessUtility.h"
#include "gtest/gtest.h"

#include <list>
#include <chrono>
#include <iostream>
#include <fstream>

#ifdef _WIN32
    #include "Windows.h"
#else

#ifdef  __APPLE__
    #include <sys/types.h>
    #include <sys/stat.h>
#endif

#endif 

void PerformanceTime(double testTime)
{
	auto currentTestName = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    string csvHeaders = "Date/Time, Test Time (ms)";
    string fileName;

#ifdef _WIN32

	fileName += "//PerformanceResults//";
	fileName += currentTestName;
	fileName += ".csv";

	// check there exists a file "/PerformanceResults/*currentTestName*.csv"
	ifstream file(fileName);

    if (!file.good()) {
		CreateDirectory(L"//PerformanceResults", nullptr);

        		// create the file
		ofstream newFile(fileName);

		newFile << csvHeaders << endl;
		newFile.close();
	}
#else
    #ifdef __APPLE__

    auto filePath = ProcessUtility::CurrentApplicationDirectory();
    filePath += "/PerformanceResults/";

    fileName = filePath;
    fileName += currentTestName;
    fileName += ".csv";

    ifstream file(fileName);

    if (!file.good()) {
        // apparently this creates a directory with:
        // "read/write/search permissions for owner and group, and with read/search permissions for others."
	    auto result = mkdir(filePath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

        ofstream newFile(fileName);

        if (newFile.good()) {
            newFile << csvHeaders << endl;
            newFile.close();
        } else {
            return;
        }
    }
    #endif
#endif

	ofstream writeFile(fileName, ofstream::out | ofstream::app);

	if (writeFile.good()) {
        auto currentTime = time(nullptr);
        tm localTimeBuffer;
        char timeBuffer[32];

#ifdef _WIN32
		localtime_s(&localTimeBuffer, &currentTime); 
		asctime_s(timeBuffer, 32, &localTimeBuffer);
#else
    #ifdef __APPLE__
        localtime_r(&currentTime, &localTimeBuffer);
        asctime_r(&localTimeBuffer, timeBuffer);
    #endif
#endif
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

	for (auto i = 0; i < numComponents; ++i) {
		auto transformComponent = componentCollectionRepository.NewComponent<TransformComponent>("TestCollection");
	}

	auto end = chrono::steady_clock::now();
	auto t = chrono::duration<double, milli>(end - start).count();

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

	for (auto i = 0; i < numComponents; ++i) {
		auto transformComponent = componentCollectionRepository.NewComponent<TransformComponent>("TestCollection");
		auto graphicsComponent = componentCollectionRepository.NewComponent<GraphicsComponent>("TestCollection");
	}

	auto end = chrono::steady_clock::now();
	auto t = chrono::duration<double, milli>(end - start).count();

	PerformanceTime(t); 
}
//-----------------------------------------------------------------------------
// Name: DeleteComponentsPerfTest
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
//-----------------------------------------------------------------------------
// Name: DeleteComponentsPerfTest
// Desc: 		
//-----------------------------------------------------------------------------
TEST(PerformanceTest, RetrieveByIdPerfTest)
{
	const auto numComponents = 5000;
	ComponentCollectionRepository componentCollectionRepository;

	vector<int> ids;
	componentCollectionRepository.NewCollection("TestCollection");

	for (auto i = 0; i < numComponents; ++i) {
		auto transformComponent = componentCollectionRepository.NewComponent<TransformComponent>("TestCollection");
		ids.push_back(transformComponent->id);
	}

	auto start = chrono::steady_clock::now();

	for (auto i = 0; i < numComponents; i++) {
		auto component = componentCollectionRepository.Select<TransformComponent>(ids[i]);
	}
	
	auto end = chrono::steady_clock::now();
	auto t = chrono::duration<double, milli>(end - start).count();
	
	PerformanceTime(t); 
}
//-----------------------------------------------------------------------------
// Name: ComponentRepositoryInsertComponentsPerfTest
// Desc: 		
//-----------------------------------------------------------------------------
TEST(PerformanceTest, ComponentRepositoryInsertComponentsPerfTest)
{
	const auto numComponents = 5000;
	auto start = chrono::steady_clock::now();

	ComponentRepository componentRepository("PerformanceTest");

	auto entityId = componentRepository.GenerateId();
	componentRepository.NewCollection("TestCollection");

	for (auto i = 0; i < numComponents; ++i) {
		auto transformComponent = componentRepository.NewComponent<TransformComponent>("TestCollection");
	}

	auto end = chrono::steady_clock::now();
	auto t = chrono::duration<double, milli>(end - start).count();

	PerformanceTime(t); 
}
//-----------------------------------------------------------------------------
// Name: ComponentRepositoryInsertMultipleTypeComponentsPerfTest
// Desc: 		
//-----------------------------------------------------------------------------
TEST(PerformanceTest, ComponentRepositoryInsertMultipleTypeComponentsPerfTest)
{
	const auto numComponents = 5000;

	auto start = chrono::steady_clock::now();

	ComponentRepository componentRepository("PerformanceTest");

	auto entityId = componentRepository.GenerateId();
	componentRepository.NewCollection("TestCollection");

	for (auto i = 0; i < numComponents; ++i) {
		auto transformComponent = componentRepository.NewComponent<TransformComponent>("TestCollection");
		auto graphicsComponent = componentRepository.NewComponent<GraphicsComponent>("TestCollection");
	}

	auto end = chrono::steady_clock::now();
	auto t = chrono::duration<double, milli>(end - start).count();

	PerformanceTime(t); 
}
//-----------------------------------------------------------------------------
// Name: ComponentRepositoryDeleteComponentsPerfTest
// Desc: 		
//-----------------------------------------------------------------------------
TEST(PerformanceTest, ComponentRepositoryDeleteComponentsPerfTest)
{
	const auto numComponents = 5000;
	auto start = chrono::steady_clock::now();

	ComponentRepository componentRepository("PerformanceTest");

	vector<int> ids;
	componentRepository.NewCollection("TestCollection");

	for (auto i = 0; i < numComponents; ++i) {
		auto transformComponent = componentRepository.NewComponent<TransformComponent>("TestCollection");
		ids.push_back(transformComponent->id);
	}

	for (auto i = 0; i < numComponents; i++) {
		componentRepository.Remove(ids[i]);
	}
	
	auto end = chrono::steady_clock::now();
	auto t = chrono::duration<double, milli>(end - start).count();
	
	PerformanceTime(t); 
}
//-----------------------------------------------------------------------------
// Name: ComponentRepositoryRetrieveByIdPerfTest
// Desc: 		
//-----------------------------------------------------------------------------
TEST(PerformanceTest, ComponentRepositoryRetrieveByIdPerfTest)
{
	const auto numComponents = 5000;
	ComponentRepository componentRepository("PerformanceTest");

	vector<int> ids;
	componentRepository.NewCollection("TestCollection");

	for (auto i = 0; i < numComponents; ++i) {
		auto transformComponent = componentRepository.NewComponent<TransformComponent>("TestCollection");
		ids.push_back(transformComponent->id);
	}

	auto start = chrono::steady_clock::now();
	
	for (auto i = 0; i < numComponents; i++) {
		auto selectComponent = componentRepository.SelectId<TransformComponent>(ids[i]);
	}
	
	auto end = chrono::steady_clock::now();
	auto t = chrono::duration<double, milli>(end - start).count();
	
	PerformanceTime(t); 
}
