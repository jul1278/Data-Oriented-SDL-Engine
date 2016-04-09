#ifndef SDL_EVENT_COLLECTOR
#define SDL_EVENT_COLLECTOR

#include <SDL.h>
#include "IEventArgs.h"
#include "ButtonEventArgs.h"
#include <list>
#include "ITaskEvent.h"
#include "MouseButtonEventArgs.h"
#include <map>
#include "TaskEvent.h"
#include "EventObserveable.h"
#include <queue>
#include "QuitApplicationEventArgs.h"
#include "MouseMotionEventArgs.h"

using namespace std; 

class SDLEventCollector : public EventObservable
{
private:

	bool quitEvent;   

	list<SDL_Event> sdlEvents;

	map<SDL_Rect, string> mouseOverNames; 
	map<SDL_Rect, string> mouseClickNames; 

	void ButtonEvent(const SDL_Event& sdlEvent)
	{
		if (sdlEvent.type != SDL_KEYUP && sdlEvent.type != SDL_KEYDOWN) {
			return; 
		}

		auto released = (sdlEvent.type == SDL_KEYUP);

		switch (sdlEvent.key.keysym.sym) {
			case SDLK_LEFT:

				this->Invoke<ButtonEventArgs>(ButtonEventArgs(LEFT_ARROW, released)); 
				break;

			case SDLK_RIGHT:
			
				this->Invoke<ButtonEventArgs>(ButtonEventArgs(RIGHT_ARROW, released));
				break;

			case SDLK_UP:

				this->Invoke<ButtonEventArgs>(ButtonEventArgs(UP_ARROW, released)); 
				break;

			case SDLK_DOWN:
				this->Invoke<ButtonEventArgs>(ButtonEventArgs(DOWN_ARROW, released)); 
				break; 

			default:
				break;
		}
	}

	void MouseMotionEvent(const SDL_Event& sdlEvent)
	{
		if (sdlEvent.type != SDL_MOUSEMOTION) {
			return; 
		}

		auto currentPosition = Vector2D(sdlEvent.motion.x + sdlEvent.motion.xrel, sdlEvent.motion.y + sdlEvent.motion.yrel);
		auto lastPosition = Vector2D(sdlEvent.motion.x, sdlEvent.motion.y); 

		this->Invoke<MouseMotionEventArgs>(MouseMotionEventArgs(currentPosition, lastPosition)); 
	}

	void MouseButtonEvent(const SDL_Event& sdlEvent)
	{
		if (sdlEvent.type != SDL_MOUSEBUTTONDOWN && sdlEvent.type != SDL_MOUSEBUTTONUP) {
			return; 
		}

		auto released = (sdlEvent.type == SDL_MOUSEBUTTONUP); 
		auto currentPosition = Vector2D(sdlEvent.motion.x + sdlEvent.motion.xrel, sdlEvent.motion.y + sdlEvent.motion.yrel);
		auto button = (sdlEvent.button.button == SDL_BUTTON_LEFT) ? LEFT_BUTTON : RIGHT_BUTTON; 

		this->Invoke<MouseButtonEventArgs>(MouseButtonEventArgs(button, released, currentPosition)); 
	}

public:

	SDLEventCollector()
	{
		this->quitEvent = false; 
	}

	void Update() 
	{
		 

		SDL_Event sdlEvent;
		while (SDL_PollEvent(&sdlEvent)) {
			this->sdlEvents.push_back(sdlEvent);
		}
		
		// check if there's a quit event
		for (auto event : this->sdlEvents) {
			if (event.type == SDL_QUIT) {
				this->Invoke<QuitApplicationEventArgs>(QuitApplicationEventArgs());
			}


			if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
				this->ButtonEvent(event); 
			}

			if (event.type == SDL_MOUSEMOTION) {
				this->MouseMotionEvent(event); 
			}

			if (event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEBUTTONDOWN) {
				this->MouseButtonEvent(event); 
			}
		}
	}

	void RegisterMouseOverHandler(Vector2D topLeft, Vector2D bottomRight, function<void(const MouseMotionEventArgs&)>)
	{
		// TODO:
	}

	void RegisterMouseClickHandler(Vector2D topLeft, Vector2D bottomRight, function<void(const MouseButtonEventArgs&)>)
	{
		// TODO:  
	}

	bool QuitEvent()
	{
		return this->quitEvent; 
	}

};

#endif // SDL_EVENT_COLLECTOR