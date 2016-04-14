#ifndef MOUSE_MOTION_EVENT_ARGS
#define MOUSE_MOTION_EVENT_ARGS

#include "Events/IEventArgs.h"
#include "Utility/Vector.h"

class MouseMotionEventArgs : public IEventArgs
{
	Vector2D currentPosition;
	Vector2D lastPosition; 
	bool mouseOver; 

public:

	explicit MouseMotionEventArgs(Vector2D currentPosition, Vector2D lastPosition, bool mouseOver = false)
		: IEventArgs(MouseMotionEvent), currentPosition(currentPosition), lastPosition(lastPosition), mouseOver(mouseOver)
	{}

	Vector2D CurrentPosition() const
	{
		return this->currentPosition; 
	}

	Vector2D LastPosition() const
	{
		return this->lastPosition; 
	}

	Vector2D Delta() const
	{
		return (this->currentPosition - this->lastPosition);
	}

	bool MouseOver() const
	{
		return this->mouseOver; 
	}
};

#endif // MOUSE_EVENT_ARGS