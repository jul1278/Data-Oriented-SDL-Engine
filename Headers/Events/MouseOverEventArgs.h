#ifndef MOUSE_OVER_EVENT_ARGS
#define MOUSE_OVER_EVENT_ARGS

#include "Events/MouseMotionEventArgs.h"
#include "Utility/Vector.h"

class MouseOverEventArgs : public IEventArgs
{
	unsigned int transformId; 
	MouseMotionEventArgs mouseMotionEventArgs; 

public:

	MouseOverEventArgs(unsigned int id, const MouseMotionEventArgs& mouseMotionEvent)
		: transformId(id), mouseMotionEventArgs(mouseMotionEvent)
	{}

	unsigned int TransformId() { return this->transformId; }
	MouseMotionEventArgs& MouseMotionEventArgs() { return this->mouseMotionEventArgs;  }
}; 

#endif // MOUSE_OVER_EVENT_ARGS