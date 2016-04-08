#include "stdafx.h"
#include "CppUnitTest.h"
#include "Headers/Vector.h"
#include "Headers/ComponentCollectionRepository.h"
#include "Headers/Physics.h"
#include "Headers/Components/BaseComponent.h"
#include "Headers/Components/TransformComponent.h"
#include "Headers/Components/VelocityComponent.h"
#include <vector>
#include <Headers/Events/EventObserveable.h>
#include <Headers/Events/ButtonEventArgs.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EventTest
{
	class TestEventArgs : public IEventArgs
	{

	public:

		explicit TestEventArgs(int eventData)
			: IEventArgs(ButtonEvent)
		{
			this->eventData = eventData; 
		}

		int eventData; 

	};


	TEST_CLASS(EventTests)
	{
	private:

		bool testEventWasCalledFirst;
		bool testEventWasCalledSecond; 
		bool testButtonEventCalled;

	public:

		TEST_METHOD(EventObservableTest)
		{
			this->testEventWasCalledFirst = false;
			this->testEventWasCalledSecond = false; 
			this->testButtonEventCalled = false; 

			EventObservable eventObservable; 

			eventObservable.RegisterListener<TestEventArgs>(bind(&EventTests::OnTestEventFirst, this, placeholders::_1));
			eventObservable.RegisterListener<TestEventArgs>(bind(&EventTests::OnTestEventSecond, this, placeholders::_1));
			eventObservable.RegisterListener<ButtonEventArgs>(bind(&EventTests::OnButtonEvent, this, placeholders::_1)); 

			eventObservable.Invoke(TestEventArgs(10));  
			eventObservable.Invoke(ButtonEventArgs(UP_ARROW, true)); 

			Assert::IsTrue(this->testEventWasCalledFirst);
			Assert::IsTrue(this->testEventWasCalledSecond); 
		}

		void OnTestEventFirst(const TestEventArgs& testEventArgs)
		{
			if (testEventArgs.eventData == 10) {
				this->testEventWasCalledFirst = true;
			}
		}

		void OnTestEventSecond(const TestEventArgs& testEventArgs)
		{
			if (testEventArgs.eventData == 10) {
				this->testEventWasCalledSecond = true;

			}
		}

		void OnButtonEvent(const ButtonEventArgs& buttonEventArgs)
		{
			if (buttonEventArgs.Key() == UP_ARROW && buttonEventArgs.Released()) {
				this->testButtonEventCalled = true; 
			}

		}

	};

}