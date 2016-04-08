#ifndef MOUSE_MOTION_EVENT_ARGS
#define MOUSE_MOTION_EVENT_ARGS

#include "IEventArgs.h"
#include "Vector.h"

class MouseMotionEventArgs : public IEventArgs
{
	Vector2D currentPosition;
	Vector2D lastPosition; 

public:

	explicit MouseMotionEventArgs(Vector2D currentPosition, Vector2D lastPosition)
		: IEventArgs(MouseMotionEvent), currentPosition(currentPosition), lastPosition(lastPosition)
	{
	}

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

};

#endif // MOUSE_EVENT_ARGS