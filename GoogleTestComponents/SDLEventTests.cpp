#include "stdafx.h"
#include "Utility/Vector.h"
#include "Events/SDLEventCollector.h"
#include "Events/MouseButtonEventArgs.h"
#include "Events/MouseMotionEventArgs.h"
#include "gtest/gtest.h"
#include "SDL.h"

bool leftMouseButtonPressed = false; 
bool mouseMotionEvent = false; 
bool mouseOverRect = false; 
bool mouseOffRect = false; 
bool mouseClickRect = false; 

void MouseOffHandler(const MouseMotionEventArgs& mouseMotionEventArgs)
{
    mouseOffRect = mouseMotionEventArgs.MouseOver();
}

void MouseMotionHandler(const MouseMotionEventArgs& mouseMotionEventArgs)
{
    if (mouseMotionEventArgs.CurrentPosition().x == 15.0f && mouseMotionEventArgs.CurrentPosition().y == 15.0f)
    {
        if (mouseMotionEventArgs.Delta().x == 5.0f && mouseMotionEventArgs.Delta().y == 5.0f) {
            mouseMotionEvent = true;
        }
    }
}

void MouseOverHandler(const MouseMotionEventArgs& mouseMotionEventArgs)
{
    mouseOverRect = true;
}

void MouseClickOverHandler(const MouseButtonEventArgs& mouseButtonEventArgs)
{
    mouseClickRect = true;
}

void MouseButtonHandler(const MouseButtonEventArgs& mouseButtonEventArgs)
{
    if (mouseButtonEventArgs.MouseButton() == LEFT_BUTTON) {
        if (mouseButtonEventArgs.Released()) {
            leftMouseButtonPressed = true;
        }
    }
}

class SdlEventTest : public testing::Test
{
    virtual void SetUp() override
    {
        auto result = SDL_Init(SDL_INIT_EVENTS);
        EXPECT_TRUE(result == 0, L"SDL_Init() failed.");
    }

    virtual void TearDown() override
    {
        SDL_Quit();
    }
};
//-----------------------------------------------------------------------------
// Name: SDL_MouseButtonEventTest
// Desc: 		
//-----------------------------------------------------------------------------
TEST_F(SdlEventTest, SDL_MouseButtonEventTest)
{
	SDL_Event mouseButtonEvent; 
	SDLEventCollector sdlEventCollector(100, 100);

	mouseButtonEvent.type = SDL_MOUSEBUTTONDOWN;
	mouseButtonEvent.button.button = SDL_BUTTON_LEFT; 
	mouseButtonEvent.button.state = SDL_RELEASED; 
	mouseButtonEvent.motion.x = 10; 
	mouseButtonEvent.motion.y = 10; 

	SDL_PushEvent(&mouseButtonEvent); 

	sdlEventCollector.RegisterListener<MouseButtonEventArgs>(bind(&MouseButtonHandler, placeholders::_1));
	sdlEventCollector.Update(); 

	EXPECT_TRUE(leftMouseButtonPressed); 
}
//-----------------------------------------------------------------------------
// Name: SDL_MouseMotionEventTest
// Desc: 		
//-----------------------------------------------------------------------------
TEST_F(SdlEventTest, SDL_MouseMotionEventTest)
{
	SDL_Event mouseMotionSdlEvent; 
	SDLEventCollector sdlEventCollector(100, 100); 

	mouseMotionSdlEvent.type = SDL_MOUSEMOTION; 
	mouseMotionSdlEvent.motion.x = 10; 
	mouseMotionSdlEvent.motion.y = 10; 
	mouseMotionSdlEvent.motion.xrel = 5; 
	mouseMotionSdlEvent.motion.yrel = 5; 

	SDL_PushEvent(&mouseMotionSdlEvent); 

	sdlEventCollector.RegisterListener<MouseMotionEventArgs>(bind(&MouseMotionHandler, placeholders::_1)); 
	sdlEventCollector.Update(); 

	EXPECT_TRUE(mouseMotionEvent); 
}
//-----------------------------------------------------------------------------
// Name: SDL_MouseButtonOverEvent
// Desc: when the mouse clicks within a certain area	
//-----------------------------------------------------------------------------
TEST_F(SdlEventTest, SDL_MouseButtonOverEvent)
{
	mouseClickRect = false; 

	SDL_Event mouseButtonEvent;
	SDLEventCollector sdlEventCollector(100, 100); 
			
	mouseButtonEvent.type = SDL_MOUSEBUTTONDOWN;
	mouseButtonEvent.motion.state = SDL_RELEASED; 
	mouseButtonEvent.motion.x = 12;
	mouseButtonEvent.motion.y = 12;
	mouseButtonEvent.motion.xrel = 0;
	mouseButtonEvent.motion.yrel = 0; 

	SDL_PushEvent(&mouseButtonEvent);

	sdlEventCollector.RegisterMouseClickHandler(Vector2D(10.0, 10.0), Vector2D(5.0, 5.0), bind(&MouseClickOverHandler, placeholders::_1));
	sdlEventCollector.Update(); 

	EXPECT_TRUE(mouseClickRect);
}
//-----------------------------------------------------------------------------
// Name: SDL_MouseOverEvent
// Desc: 		
//-----------------------------------------------------------------------------
TEST_F(SdlEventTest, SDL_MouseOverEvent)
{
	mouseOverRect = false;

	SDL_Event mouseMotionEvent;
	SDLEventCollector sdlEventCollector(100, 100);

	mouseMotionEvent.type = SDL_MOUSEMOTION;
	mouseMotionEvent.motion.x = 10;
	mouseMotionEvent.motion.y = 10;
	mouseMotionEvent.motion.xrel = 5;
	mouseMotionEvent.motion.yrel = 5;

	SDL_PushEvent(&mouseMotionEvent);

	sdlEventCollector.RegisterMouseOverHandler(Vector2D(12.0, 12.0), Vector2D(5.0, 5.0), bind(&MouseOverHandler, placeholders::_1));
	sdlEventCollector.Update();

	EXPECT_TRUE(mouseOverRect);
}
//-----------------------------------------------------------------------------
// Name: SDL_MouseOverEvent
// Desc: 		
//-----------------------------------------------------------------------------
TEST_F(SdlEventTest, SDL_MouseOffEvent)
{
	mouseOverRect = false;

	SDL_Event mouseMotionEvent1;
	SDL_Event mouseMotionEvent2;
	SDL_Event mouseMotionEvent3;

	SDLEventCollector sdlEventCollector(100, 100);

	mouseMotionEvent1.type = SDL_MOUSEMOTION;
	mouseMotionEvent1.motion.x = 0;
	mouseMotionEvent1.motion.y = 0;
	mouseMotionEvent1.motion.xrel = 10;
	mouseMotionEvent1.motion.yrel = 10;

	mouseMotionEvent2.type = SDL_MOUSEMOTION;
	mouseMotionEvent2.motion.x = 10;
	mouseMotionEvent2.motion.y = 10;
	mouseMotionEvent2.motion.xrel = -10;
	mouseMotionEvent2.motion.yrel = -10;

	mouseMotionEvent3.type = SDL_MOUSEMOTION;
	mouseMotionEvent3.motion.x = 0;
	mouseMotionEvent3.motion.y = 0;
	mouseMotionEvent3.motion.xrel = 10;
	mouseMotionEvent3.motion.yrel = 10;

	SDL_PushEvent(&mouseMotionEvent1);
	SDL_PushEvent(&mouseMotionEvent2);

	sdlEventCollector.RegisterMouseOverHandler(Vector2D(5.0, 5.0), Vector2D(10.0, 10.0), bind(&MouseOffHandler, placeholders::_1));
	sdlEventCollector.Update();

	EXPECT_TRUE(!mouseOffRect);

	SDL_PushEvent(&mouseMotionEvent3); 
	sdlEventCollector.Update();

	EXPECT_TRUE(mouseOffRect); 
}

