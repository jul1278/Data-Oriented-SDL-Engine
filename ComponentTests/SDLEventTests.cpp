#include "stdafx.h"
#include "CppUnitTest.h"
#include "SDL.h"
#include "Utility/Vector.h"
#include <Headers/Events/SDLEventCollector.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SDLEventTest
{

	TEST_CLASS(SDLEventTests)
	{
		bool leftMouseButtonPressed = false; 

		TEST_CLASS_INITIALIZE(SDLInitialise)
		{
			auto result = SDL_Init(SDL_INIT_EVENTS); 
			Assert::IsTrue(result == 0, L"SDL_Init() failed."); 
		}

		TEST_CLASS_CLEANUP(SDLCleanup)
		{
			SDL_Quit(); 
		}

		TEST_METHOD(SDLMouseButtonEventTest)
		{
			SDL_Event mouseButtonEvent; 
			SDLEventCollector sdlEventCollector;

			mouseButtonEvent.type = SDL_MOUSEBUTTONDOWN;
			mouseButtonEvent.button.button = SDL_BUTTON_LEFT; 
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
				if (!mouseButtonEventArgs.Released()) {
					this->leftMouseButtonPressed = true;
				}
			}
		}
	};
}