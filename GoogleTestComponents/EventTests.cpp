#include "gtest/gtest.h"
#include "Events/IEventArgs.h"
#include <Events/EventObserveable.h>
#include <functional>
#include <Events/ButtonEventArgs.h>

bool testEventWasCalledFirst;
bool testEventWasCalledSecond; 
bool testButtonEventCalled;

class TestEventArgs : public IEventArgs
{

public:

    explicit TestEventArgs(int eventData)
    {
        this->eventData = eventData;
    }

    int eventData;
};


void OnTestEventFirst(const TestEventArgs& testEventArgs)
{
    if (testEventArgs.eventData == 10) {
        testEventWasCalledFirst = true;
    }
}

void OnTestEventSecond(const TestEventArgs& testEventArgs)
{
    if (testEventArgs.eventData == 10) {
        testEventWasCalledSecond = true;

    }
}

void OnButtonEvent(const ButtonEventArgs& buttonEventArgs)
{
    if (buttonEventArgs.Key() == UP_ARROW && buttonEventArgs.Released()) {
        testButtonEventCalled = true;
    }
}


TEST(EventTests, EventObservableTest)
{
	testEventWasCalledFirst = false;
	testEventWasCalledSecond = false; 
	testButtonEventCalled = false; 

	EventObservable eventObservable; 


    auto onTestEventFirstHandler = [](const TestEventArgs& testEventArgs){OnTestEventFirst(testEventArgs); };
    auto onTestEventSecondHandler = [](const TestEventArgs& testEventArgs){OnTestEventSecond(testEventArgs); };
    auto onButtonEvent = [](const ButtonEventArgs& buttonEventArgs){OnButtonEvent(buttonEventArgs); };

	eventObservable.RegisterListener<TestEventArgs>(bind(onTestEventFirstHandler, placeholders::_1));
    eventObservable.RegisterListener<TestEventArgs>(bind(onTestEventSecondHandler, placeholders::_1));
    eventObservable.RegisterListener<ButtonEventArgs>(bind(onButtonEvent, placeholders::_1));

	eventObservable.Invoke(TestEventArgs(10));  
	eventObservable.Invoke(ButtonEventArgs(UP_ARROW, true)); 

	EXPECT_TRUE(testEventWasCalledFirst);
	EXPECT_TRUE(testEventWasCalledSecond); 
}
