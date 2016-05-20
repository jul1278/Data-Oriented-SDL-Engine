#include "stdafx.h"
#include "CppUnitTest.h"
#include "Utility/Vector.h"
#include "Events/SDLEventCollector.h"
#include "Events/MouseButtonEventArgs.h"
#include "Events/MouseMotionEventArgs.h"
#include "SDL.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SDLEventTest
{

	TEST_CLASS(SDLEventTests)
	{
		bool leftMouseButtonPressed = false; 
		bool mouseMotionEvent = false; 
		bool mouseOverRect = false; 
		bool mouseOffRect = false; 
		bool mouseClickRect = false; 

		TEST_CLASS_INITIALIZE(SDLInitialise)
		{
			auto result = SDL_Init(SDL_INIT_EVENTS); 
			Assert::IsTrue(result == 0, L"SDL_Init() failed."); 
		}

		TEST_CLASS_CLEANUP(SDLCleanup)
		{
			SDL_Quit(); 
		}
		//-----------------------------------------------------------------------------
		// Name: SDL_MouseButtonEventTest
		// Desc: 		
		//-----------------------------------------------------------------------------
		TEST_METHOD(SDL_MouseButtonEventTest)
		{
			SDL_Event mouseButtonEvent; 
			SDLEventCollector sdlEventCollector(100, 100);

			mouseButtonEvent.type = SDL_MOUSEBUTTONDOWN;
			mouseButtonEvent.button.button = SDL_BUTTON_LEFT; 
			mouseButtonEvent.button.state = SDL_RELEASED; 
			mouseButtonEvent.motion.x = 10; 
			mouseButtonEvent.motion.y = 10; 

			SDL_PushEvent(&mouseButtonEvent); 

			sdlEventCollector.RegisterListener<MouseButtonEventArgs>(bind(&SDLEventTests::MouseButtonHandler, this, placeholders::_1));
			sdlEventCollector.Update(); 

			Assert::IsTrue(this->leftMouseButtonPressed); 
		}

		void MouseButtonHandler(const MouseButtonEventArgs& mouseButtonEventArgs)
		{
			if (mouseButtonEventArgs.MouseButton() == LEFT_BUTTON) {
				if (mouseButtonEventArgs.Released()) {
					this->leftMouseButtonPressed = true;
				}
			}
		}
		//-----------------------------------------------------------------------------
		// Name: SDL_MouseMotionEventTest
		// Desc: 		
		//-----------------------------------------------------------------------------
		TEST_METHOD(SDL_MouseMotionEventTest)
		{
			SDL_Event mouseMotionEvent; 
			SDLEventCollector sdlEventCollector(100, 100); 

			mouseMotionEvent.type = SDL_MOUSEMOTION; 
			mouseMotionEvent.motion.x = 10; 
			mouseMotionEvent.motion.y = 10; 
			mouseMotionEvent.motion.xrel = 5; 
			mouseMotionEvent.motion.yrel = 5; 

			SDL_PushEvent(&mouseMotionEvent); 

			sdlEventCollector.RegisterListener<MouseMotionEventArgs>(bind(&SDLEventTests::MouseMotionHandler, this, placeholders::_1)); 
			sdlEventCollector.Update(); 

			Assert::IsTrue(this->mouseMotionEvent); 
		}

		void MouseMotionHandler(const MouseMotionEventArgs& mouseMotionEventArgs)
		{
			if (mouseMotionEventArgs.CurrentPosition().x == 15.0f && mouseMotionEventArgs.CurrentPosition().y == 15.0f)
			{
				if (mouseMotionEventArgs.Delta().x == 5.0f && mouseMotionEventArgs.Delta().y == 5.0f) {
					this->mouseMotionEvent = true; 
				}
			}
		}

		//-----------------------------------------------------------------------------
		// Name: SDL_MouseButtonOverEvent
		// Desc: when the mouse clicks within a certain area	
		//-----------------------------------------------------------------------------
		TEST_METHOD(SDL_MouseButtonOverEvent)
		{
			this->mouseClickRect = false; 

			SDL_Event mouseButtonEvent;
			SDLEventCollector sdlEventCollector(100, 100); 
			
			mouseButtonEvent.type = SDL_MOUSEBUTTONDOWN;
			mouseButtonEvent.motion.state = SDL_RELEASED; 
			mouseButtonEvent.motion.x = 12;
			mouseButtonEvent.motion.y = 12;
			mouseButtonEvent.motion.xrel = 0;
			mouseButtonEvent.motion.yrel = 0; 

			SDL_PushEvent(&mouseButtonEvent);

			sdlEventCollector.RegisterMouseClickHandler(Vector2D(10.0, 10.0), Vector2D(5.0, 5.0), bind(&SDLEventTests::MouseClickOverHandler, this, placeholders::_1));
			sdlEventCollector.Update(); 

			Assert::IsTrue(this->mouseClickRect);
		}

		void MouseClickOverHandler(const MouseButtonEventArgs& mouseButtonEventArgs)
		{
			this->mouseClickRect = true; 
		}

		//-----------------------------------------------------------------------------
		// Name: SDL_MouseOverEvent
		// Desc: 		
		//-----------------------------------------------------------------------------
		TEST_METHOD(SDL_MouseOverEvent)
		{
			this->mouseOverRect = false;

			SDL_Event mouseMotionEvent;
			SDLEventCollector sdlEventCollector(100, 100);

			mouseMotionEvent.type = SDL_MOUSEMOTION;
			mouseMotionEvent.motion.x = 10;
			mouseMotionEvent.motion.y = 10;
			mouseMotionEvent.motion.xrel = 5;
			mouseMotionEvent.motion.yrel = 5;

			SDL_PushEvent(&mouseMotionEvent);

			sdlEventCollector.RegisterMouseOverHandler(Vector2D(12.0, 12.0), Vector2D(5.0, 5.0), bind(&SDLEventTests::MouseOverHandler, this, placeholders::_1));
			sdlEventCollector.Update();

			Assert::IsTrue(this->mouseOverRect);
		}

		void MouseOverHandler(const MouseMotionEventArgs& mouseMotionEventArgs)
		{
			this->mouseOverRect = true;
		}

		//-----------------------------------------------------------------------------
		// Name: SDL_MouseOverEvent
		// Desc: 		
		//-----------------------------------------------------------------------------
		TEST_METHOD(SDL_MouseOffEvent)
		{
			this->mouseOverRect = false;

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

			sdlEventCollector.RegisterMouseOverHandler(Vector2D(5.0, 5.0), Vector2D(10.0, 10.0), bind(&SDLEventTests::MouseOffHandler, this, placeholders::_1));
			sdlEventCollector.Update();

			Assert::IsTrue(!this->mouseOffRect);

			SDL_PushEvent(&mouseMotionEvent3); 
			sdlEventCollector.Update();

			Assert::IsTrue(this->mouseOffRect); 
		}

		void MouseOffHandler(const MouseMotionEventArgs& mouseMotionEventArgs)
		{
			this->mouseOffRect = mouseMotionEventArgs.MouseOver(); 
		}


	};
}