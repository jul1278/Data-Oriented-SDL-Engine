#include "Events\SDLEventCollector.h"
#include "Events\ButtonEventArgs.h"
#include "Events\ITaskEvent.h"
#include "Events\MouseButtonEventArgs.h"
#include "Events\EventObserveable.h"
#include "Events\QuitApplicationEventArgs.h"
#include "Events\MouseMotionEventArgs.h"
#include "Components\SimpleButtonComponent.h"
#include "SDL.h"

#include <string>
#include <list>
#include <tuple>
#include <thread>

//-----------------------------------------------------------------------------------------------
// Name: Update
// Desc: 
//-----------------------------------------------------------------------------------------------
void SDLEventCollector::Update()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {

		this->sdlEvents.push_back(event);

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

		if (event.type == SDL_CONTROLLERBUTTONDOWN) {
			this->GameControllerButtonEvent(event); 
		}
	}
}
//-----------------------------------------------------------------------------------------------
// Name: InitGameControllers
// Desc: 
//-----------------------------------------------------------------------------------------------
void SDLEventCollector::InitGameControllers()
{
	if (SDL_NumJoysticks() > 0) {
		this->gameController = SDL_GameControllerOpen(0); 
	}
}
//-----------------------------------------------------------------------------------------------
// Name: RegisterMouseOverHandler
// Desc: 
//-----------------------------------------------------------------------------------------------
void SDLEventCollector::RegisterMouseOverHandler(Vector2D topLeft, Vector2D size, function<void(const MouseMotionEventArgs&)> handler)
{
	SDL_Rect rect = { topLeft.x, topLeft.y, size.x, size.y };

	auto name = to_string(this->mouseOverNames.size());
	
	this->mouseOverNames.push_back(tuple<SDL_Rect, string>(rect, name)); 
	this->mouseOverNameState[name] = false; 

	// wtf is a group listener?
	this->RegisterGroupListener<MouseMotionEventArgs>(name, handler);
}
//-----------------------------------------------------------------------------------------------
// Name: RegisterMouseOverHandler
// Desc: 
//-----------------------------------------------------------------------------------------------
void SDLEventCollector::RegisterMouseOverHandler(SimpleButtonComponent* simpleButtonComponent, function<void(const MouseMotionEventArgs&)> handler)
{
	auto size = Vector2D(simpleButtonComponent->size.x * simpleButtonComponent->transformComponent->scale.x, simpleButtonComponent->size.y * simpleButtonComponent->transformComponent->scale.y);
	auto topLeft = Vector2D(simpleButtonComponent->transformComponent->position.x - 0.5f*size.x, simpleButtonComponent->transformComponent->position.y - 0.5f*size.y);

	this->RegisterMouseOverHandler(topLeft, size, handler); 
}
//-----------------------------------------------------------------------------------------------
// Name: RegisterMouseClickHandler
// Desc: 
//-----------------------------------------------------------------------------------------------
void SDLEventCollector::RegisterMouseClickHandler(Vector2D topLeft, Vector2D size, function<void(const MouseButtonEventArgs&)> handler)
{
	SDL_Rect rect = { topLeft.x, topLeft.y, size.x, size.y };

	auto name = to_string(this->mouseClickNames.size());
	this->mouseClickNames.push_back(tuple<SDL_Rect, string>(rect, name));
	this->RegisterGroupListener<MouseButtonEventArgs>(name, handler);
}
//-----------------------------------------------------------------------------------------------
// Name: RegisterMouseClickHandler
// Desc: 
//-----------------------------------------------------------------------------------------------
void SDLEventCollector::RegisterMouseClickHandler(SimpleButtonComponent* simpleButtonComponent, function<void(const MouseButtonEventArgs&)> handler)
{
	auto size = Vector2D(simpleButtonComponent->size.x * simpleButtonComponent->transformComponent->scale.x, simpleButtonComponent->size.y * simpleButtonComponent->transformComponent->scale.y);
	auto topLeft = Vector2D(simpleButtonComponent->transformComponent->position.x - 0.5f*size.x, simpleButtonComponent->transformComponent->position.y - 0.5f*size.y);

	this->RegisterMouseClickHandler(topLeft, size, handler); 
}
//-----------------------------------------------------------------------------------------------
// Name: ButtonEvent
// Desc: 
//-----------------------------------------------------------------------------------------------
void SDLEventCollector::ButtonEvent(const SDL_Event& sdlEvent)
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
		case SDLK_SPACE:
			this->Invoke<ButtonEventArgs>(ButtonEventArgs(SPACE, released)); 
			break;
		default:
			break;
	}
}
//-----------------------------------------------------------------------------------------------
// Name: MouseMotionEvent
// Desc: 
//-----------------------------------------------------------------------------------------------
void SDLEventCollector::MouseMotionEvent(const SDL_Event& sdlEvent)
{
	if (sdlEvent.type != SDL_MOUSEMOTION) {
		return;
	}

	auto size = Vector2D(this->width, this->height);

	auto currentPosition = Vector2D(sdlEvent.motion.x + sdlEvent.motion.xrel, sdlEvent.motion.y + sdlEvent.motion.yrel);
	auto lastPosition = Vector2D(sdlEvent.motion.x, sdlEvent.motion.y);
	auto delta = Vector2D(sdlEvent.motion.xrel, sdlEvent.motion.yrel);

	// invoke listeners that dont care where the mouse is
	this->Invoke<MouseMotionEventArgs>(MouseMotionEventArgs(currentPosition, lastPosition, size));

	for (auto rectNamePair : this->mouseOverNames) {
		auto rect = get<0>(rectNamePair);
		auto name = get<1>(rectNamePair);

		if (currentPosition.x > rect.x && currentPosition.x < (rect.x + rect.w) &&
			currentPosition.y > rect.y && currentPosition.y < (rect.y + rect.h)) {

			if (this->mouseOverNameState[name] == false) {
				this->mouseOverNameState[name] = true;
				this->InvokeGroup<MouseMotionEventArgs>(name, MouseMotionEventArgs(currentPosition, lastPosition, size, true));
			}
		}
		else {

			// if we exit
			if (this->mouseOverNameState[name]) {
				this->InvokeGroup<MouseMotionEventArgs>(name, MouseMotionEventArgs(currentPosition, lastPosition, size, false));
			}

			this->mouseOverNameState[name] = false;
		}
	}
}
//-----------------------------------------------------------------------------------------------
// Name: MouseButtonEvent
// Desc: 
//-----------------------------------------------------------------------------------------------
void SDLEventCollector::GameControllerButtonEvent(const SDL_Event& sdlEvent)
{
	/*if (sdlEvent.type != SDL_CONTROLLERBUTTONDOWN || sdlEvent.type != SDL_CONTROLLERBUTTONUP) {
		return; 
	}
	*/

	auto released = sdlEvent.cbutton.state; 

	switch (sdlEvent.cbutton.button) {

	case 2: // d pad left
		this->Invoke<ButtonEventArgs>(ButtonEventArgs(LEFT_ARROW, released));
		break;
	case 3: // d pad right
		this->Invoke<ButtonEventArgs>(ButtonEventArgs(RIGHT_ARROW, released));
		break;
	case 0: // d pad up
		this->Invoke<ButtonEventArgs>(ButtonEventArgs(UP_ARROW, released));
		break;
	case 1: // d pad down
		this->Invoke<ButtonEventArgs>(ButtonEventArgs(DOWN_ARROW, released));
		break;
	default:
		break;
	}
}
//-----------------------------------------------------------------------------------------------
// Name: MouseButtonEvent
// Desc: 
//-----------------------------------------------------------------------------------------------
void SDLEventCollector::MouseButtonEvent(const SDL_Event& sdlEvent)
{
	if (sdlEvent.type != SDL_MOUSEBUTTONDOWN && sdlEvent.type != SDL_MOUSEBUTTONUP) {
		return;
	}

	Vector2D currentPosition; 

	currentPosition = Vector2D(sdlEvent.button.x, sdlEvent.button.y);

	auto released = (sdlEvent.button.state == SDL_RELEASED);
	auto button = (sdlEvent.button.button == SDL_BUTTON_LEFT) ? LEFT_BUTTON : RIGHT_BUTTON;

	// need to invoke listeners who dont care where the mouse is
	this->Invoke<MouseButtonEventArgs>(MouseButtonEventArgs(button, released, currentPosition));

	for (auto rectNamePair : this->mouseClickNames) {
		auto rect = get<0>(rectNamePair);
		auto name = get<1>(rectNamePair); 

		if (currentPosition.x > rect.x && currentPosition.x < (rect.x + rect.w) &&
			currentPosition.y > rect.y && currentPosition.y < (rect.y + rect.h)) {
			this->InvokeGroup<MouseButtonEventArgs>(name, MouseButtonEventArgs(button, released, currentPosition)); 
		}
	}
}