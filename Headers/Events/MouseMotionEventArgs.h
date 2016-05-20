#ifndef MOUSE_MOTION_EVENT_ARGS
#define MOUSE_MOTION_EVENT_ARGS

#include "Events/IEventArgs.h"
#include "Utility/Vector.h"

class MouseMotionEventArgs : public IEventArgs
{
	Vector2D currentPosition;
	Vector2D lastPosition;
	Vector2D size; 
	bool mouseOver; 

	Vector2D GetNormalized(Vector2D vector) const
	{
		return Vector2D(vector.x / this->size.x, vector.y / this->size.y); 
	}

public:

	explicit MouseMotionEventArgs(Vector2D currentPosition, Vector2D lastPosition, Vector2D size = Vector2D(1.0f, 1.0f), bool mouseOver = false)
		: currentPosition(currentPosition), lastPosition(lastPosition), size(size), mouseOver(mouseOver)
	{}

	Vector2D CurrentPosition() const
	{
		return this->currentPosition; 
	}

	Vector2D CurrentPositionNormalized() const
	{
		return this->GetNormalized(this->currentPosition);
	}

	Vector2D LastPosition() const
	{
		return this->lastPosition; 
	}

	Vector2D LastPositionNormalized() const
	{
		return this->GetNormalized(this->lastPosition); 
	}

	Vector2D Delta() const
	{
		return (this->currentPosition - this->lastPosition);
	}

	Vector2D DeltaNormalized() const
	{
		return this->GetNormalized(this->Delta()); 
	}

	bool MouseOver() const
	{
		return this->mouseOver; 
	}
};

#endif // MOUSE_EVENT_ARGS