#ifndef TASK_EVENT_H
#define TASK_EVENT_H

#include "ITaskEvent.h"

#include <list>

using namespace std;

template<typename T>
class TaskEvent : public ITaskEvent
{

	list<function<void(const T&)>> handlers;

public:

	TaskEvent()
	{
		assert(static_cast<bool>(is_base_of<IEventArgs, T>().value) == true);
	}

	void operator+=(function<void(const T&)> handler)
	{
		this->handlers.push_back(handler);
	}

	void operator-=(function<void(const T&)> handler)
	{
		remove_if(handlers.front(), handlers.back(),
			[handler](function<void(const T&)> func) {
			handler == func;
		});
	}

	void Invoke(const IEventArgs& eventArgs) override
	{
		for (auto handler : this->handlers) {
			handler(static_cast<const T&>(eventArgs));
		}
	}

	void RemoveAll()
	{
		this->handlers.clear();
	}
};

#endif // TASK_EVENT_H