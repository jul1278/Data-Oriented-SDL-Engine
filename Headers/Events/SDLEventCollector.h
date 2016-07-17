#ifndef SDL_EVENT_COLLECTOR_H
#define SDL_EVENT_COLLECTOR_H

#include "Events/EventObserveable.h"
#include "SDL.h"

struct TransformComponent;
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

	unsigned int width;
	unsigned int height; 

	int lastMouseY; 

	bool quitEvent;   

	SDL_GameController* gameController; 

	list<SDL_Event> sdlEvents;

	list<tuple<SDL_Rect, string>> mouseOverNames; 
	map<string, bool> mouseOverNameState; 
	list<tuple<SDL_Rect, string>> mouseClickNames; 

	void ButtonEvent(const SDL_Event& sdlEvent);
	void MouseButtonEvent(const SDL_Event& sdlEvent); 
	void MouseMotionEvent(const SDL_Event& sdlEvent); 
	void GameControllerButtonEvent(const SDL_Event& sdlEvent);

	void InitGameControllers(); 

public:

	SDLEventCollector() : SDLEventCollector(0, 0) {}

	SDLEventCollector(unsigned int width, unsigned int height)
	{
		this->width = width;
		this->height = height; 

		this->quitEvent = false; 
		this->InitGameControllers(); 
	}

	~SDLEventCollector()
	{
		// TODO: store the actual joystick that was opened and close
		SDL_GameControllerClose(0); 
	}

	void Update(); 

	void RegisterMouseOverHandler(Vector2D topLeft, Vector2D size, function<void(const MouseMotionEventArgs&)> handler); 
	void RegisterMouseOverHandler(const SimpleButtonComponent& simpleButtonComponent, const TransformComponent& transformComponent, function<void(const MouseMotionEventArgs&)> handler);

	void RegisterMouseClickHandler(Vector2D topLeft, Vector2D size, function<void(const MouseButtonEventArgs&)> handler); 
	void RegisterMouseClickHandler(const SimpleButtonComponent& simpleButtonComponent, const TransformComponent& transform, function<void(const MouseButtonEventArgs&)> handler);

	bool QuitEvent() const
	{
		return this->quitEvent; 
	}

};

#endif // SDL_EVENT_COLLECTOR_H