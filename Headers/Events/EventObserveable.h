#ifndef EVENT_OBSERVEABLE_H
#define EVENT_OBSERVEABLE_H
#include <map>
#include <typeindex>
#include "TaskEvent.h"

using namespace std;

class EventObservable
{
private:

	map<type_index, ITaskEvent*> listenerMap; 

public:

	EventObservable() {}

	template<typename T>
	void RegisterListener(function<void(const T&)> listener)
	{
		if (listenerMap.find(type_index(typeid(T))) == listenerMap.end()) {
			listenerMap[type_index(typeid(T))] = new TaskEvent<T>(); 
		}

		TaskEvent<T>* taskEvent = dynamic_cast<TaskEvent<T>*>(listenerMap[type_index(typeid(T))]); 
		taskEvent->operator+=(listener); 
	}

	template<typename T>
	void Invoke(T event)
	{
		if (listenerMap.find(type_index(typeid(T))) == listenerMap.end()) {
			return; 
		}

		TaskEvent<T>* taskEvent = dynamic_cast<TaskEvent<T>*>(listenerMap[type_index(typeid(T))]);
		taskEvent->Invoke(event); 
	}

};

#endif // EVENT_OBSERVEABLE_H