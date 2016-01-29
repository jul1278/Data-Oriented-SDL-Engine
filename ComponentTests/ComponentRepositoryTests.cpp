#include "stdafx.h"
#include "CppUnitTest.h"
#include "Headers/Vector.h"
#include "Headers/ComponentRepository.h"
#include "Headers/Components/TransformComponent.h"
#include "Headers/Components/BaseComponent.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ComponentTests
{		
	TEST_CLASS(ComponentRepositoryTests)
	{
	public:
		
		TEST_METHOD(InsertRemoveComponents)
		{
			ComponentRepository componentRepository;
			vector<int> ids;

			componentRepository.RegisterComponentType<TransformComponent>();

			for (int i = 0; i < 1000; i++) {

				auto newComponent = componentRepository.NewComponent<TransformComponent>();
				ids.push_back(newComponent->id);
			}

			for (auto id : ids) {

				componentRepository.DeleteComponent(id);
			}

			Assert::AreEqual(0, componentRepository.Count()); 
		}
	};
}