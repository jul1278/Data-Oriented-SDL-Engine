#ifndef MOUSE_BUTTON_EVENT_ARGS
#define MOUSE_BUTTON_EVENT_ARGS

#include "Events/IEventArgs.h"
#include "Utility/Vector.h"

enum MouseButton
{
	LEFT_BUTTON,
	RIGHT_BUTTON
};

class MouseButtonEventArgs : public IEventArgs
{
private:

	MouseButton mouseButton;
	bool released;
	Vector2D mousePosition; 

public:

	explicit MouseButtonEventArgs(MouseButton mouseButton, bool released, Vector2D mousePosition)
		: mouseButton(mouseButton), released(released), mousePosition(mousePosition)
	{}

	MouseButton MouseButton() const
	{
		return this->mouseButton; 
	}

	bool Released() const
	{
		return this->released; 
	}

	Vector2D MousePosition() const
	{
		return this->mousePosition; 
	}
};

#endif // MOUSE_BUTTON_EVENT_ARGS