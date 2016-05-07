#ifndef SDL_EVENT_COLLECTOR_H
#define SDL_EVENT_COLLECTOR_H

#include "Events/EventObserveable.h"
#include <thread>
#include <mutex>
#include <condition_variable>

union SDL_Event;
struct SDL_Rect;

struct Vector2D;
struct SimpleButtonComponent;
class MouseMotionEventArgs;
class MouseButtonEventArgs;

using namespace std; 

class SDLEventCollector : public EventObservable
{
private:

	int lastMouseY; 

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
	void RegisterMouseOverHandler(SimpleButtonComponent* simpleButtonComponent, function<void(const MouseMotionEventArgs&)> handler);

	void RegisterMouseClickHandler(Vector2D topLeft, Vector2D size, function<void(const MouseButtonEventArgs&)> handler); 
	void RegisterMouseClickHandler(SimpleButtonComponent* simpleButtonComponent, function<void(const MouseButtonEventArgs&)> handler);

	bool QuitEvent() const
	{
		return this->quitEvent; 
	}

};

#endif // SDL_EVENT_COLLECTOR_H