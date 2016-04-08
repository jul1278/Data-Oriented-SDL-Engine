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

using namespace std; 

class SDLEventCollector
{
private:

	bool quitEvent;   
	list<IEventArgs*> events; 
	map<type_index, ITaskEvent*> eventListeners; 

public:

	SDLEventCollector()
	{
		this->quitEvent = false; 
	}

	IEventArgs* PollEvents()
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT) {
			this->quitEvent = true;
		}

		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {

			bool released = (event.type == SDL_KEYUP);
			ButtonEventArgs* buttonEventArgs = nullptr;

			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				buttonEventArgs = new ButtonEventArgs(LEFT_ARROW, released);
				break;
			case SDLK_RIGHT:
				buttonEventArgs = new ButtonEventArgs(RIGHT_ARROW, released);
				break;
			case SDLK_UP:
				buttonEventArgs = new ButtonEventArgs(UP_ARROW, released);
				break;
			default:
				break;
			}

			if (buttonEventArgs != nullptr) {
				return buttonEventArgs;
			}

		}

		return nullptr;
	}

	bool QuitEvent()
	{
		return this->quitEvent; 
	}

};

#endif // SDL_EVENT_COLLECTOR