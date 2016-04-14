#include "Events\SDLEventCollector.h"

//-----------------------------------------------------------------------------------------------
// Name: Update
// Desc: 
//-----------------------------------------------------------------------------------------------
void SDLEventCollector::Update()
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

	this->sdlEvents.clear(); 
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

	this->RegisterGroupListener<MouseMotionEventArgs>(name, handler);
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

	auto currentPosition = Vector2D(sdlEvent.motion.x + sdlEvent.motion.xrel, sdlEvent.motion.y + sdlEvent.motion.yrel);
	auto lastPosition = Vector2D(sdlEvent.motion.x, sdlEvent.motion.y);
	auto delta = Vector2D(sdlEvent.motion.xrel, sdlEvent.motion.yrel); 

	// invoke listeners that dont care where the mouse is
	this->Invoke<MouseMotionEventArgs>(MouseMotionEventArgs(currentPosition, lastPosition)); 

	for (auto rectNamePair : this->mouseOverNames) {
		auto rect = get<0>(rectNamePair); 
		auto name = get<1>(rectNamePair);

		if (currentPosition.x > rect.x && currentPosition.x < (rect.x + rect.w) && 
			currentPosition.y > rect.y && currentPosition.y < (rect.y + rect.h)) {

			if (this->mouseOverNameState[name] == false) {
				this->mouseOverNameState[name] = true;
				this->InvokeGroup<MouseMotionEventArgs>(name, MouseMotionEventArgs(currentPosition, lastPosition, true)); 
			}

		} else {

			// if we exit
			if (this->mouseOverNameState[name]) {
				this->InvokeGroup<MouseMotionEventArgs>(name, MouseMotionEventArgs(currentPosition, lastPosition, false));
			}

			this->mouseOverNameState[name] = false;
		}
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

	auto released = (sdlEvent.type == SDL_MOUSEBUTTONUP);
	auto currentPosition = Vector2D(sdlEvent.motion.x + sdlEvent.motion.xrel, sdlEvent.motion.y + sdlEvent.motion.yrel);
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