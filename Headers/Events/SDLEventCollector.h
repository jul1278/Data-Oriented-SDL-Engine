#ifndef SDL_EVENT_COLLECTOR_H
#define SDL_EVENT_COLLECTOR_H

#include "SDL.h"
#include "IEventArgs.h"
#include "ButtonEventArgs.h"
#include "ITaskEvent.h"
#include "MouseButtonEventArgs.h"
#include "TaskEvent.h"
#include "EventObserveable.h"
#include "QuitApplicationEventArgs.h"
#include "MouseMotionEventArgs.h"

#include <string>
#include <queue>
#include <unordered_map>
#include <list>
#include <tuple>

using namespace std; 


class SDLEventCollector : public EventObservable
{
private:

	bool quitEvent;   

	list<SDL_Event> sdlEvents;

	list<tuple<SDL_Rect, string>> mouseOverNames; 
	map<string, bool> mouseOverNameState; 
	list<tuple<SDL_Rect, string>> mouseClickNames; 

	void ButtonEvent(const SDL_Event& sdlEvent);
	void MouseButtonEvent(const SDL_Event& sdlEvent); 
	void MouseMotionEvent(const SDL_Event& sdlEvent); 

public:

	SDLEventCollector()
	{
		this->quitEvent = false; 
	}
	
	void Update(); 

	void RegisterMouseOverHandler(Vector2D topLeft, Vector2D size, function<void(const MouseMotionEventArgs&)> handler); 

	void RegisterMouseClickHandler(Vector2D topLeft, Vector2D size, function<void(const MouseButtonEventArgs&)> handler); 

	bool QuitEvent() const
	{
		return this->quitEvent; 
	}

};

#endif // SDL_EVENT_COLLECTOR_H