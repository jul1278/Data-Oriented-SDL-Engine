#ifndef ITASK_EVENT_H
#define ITASK_EVENT_H

#include "Events/IEventArgs.h"

#include <list>
#include <functional>
#include <algorithm>
#include <assert.h>

using namespace std; 

class ITaskEvent
{

public:

	virtual ~ITaskEvent() {}
	virtual void Invoke(const IEventArgs& eventArgs) = 0; 
};

#endif // ITASK_EVENT_H