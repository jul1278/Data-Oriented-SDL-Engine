#ifndef MOUSE_BUTTON_EVENT_ARGS
#define MOUSE_BUTTON_EVENT_ARGS

#include "IEventArgs.h"
#include <Vector.h>
#include "ButtonEventArgs.h"

class MouseButtonEventArgs : public IEventArgs
{
private:

	Key key;
	bool released;
	Vector2D mousePosition; 

public:

	explicit MouseButtonEventArgs(Key key, bool released, Vector2D mousePosition)
		: IEventArgs(MouseButtonEvent), key(key), released(released), mousePosition(mousePosition)
	{}

	Key Key() const
	{
		return this->key; 
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