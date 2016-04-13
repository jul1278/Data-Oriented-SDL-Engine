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
	map<type_index, map<string, ITaskEvent*>> namedListenerMap; 

public:

	EventObservable() {}

	~EventObservable()
	{
		for (auto pair : this->listenerMap) {
			delete pair.second; 
		}

		for (auto map : this->namedListenerMap) {
			for (auto pair : map.second) {
				delete pair.second; 
			}
		}
	}

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
	void RegisterGroupListener(string groupName, function<void(const T&)> handler)
	{
		auto& group = this->namedListenerMap[type_index(typeid(T))];
		auto result = group.find(groupName); 

		if (result == group.end()) {
			group[groupName] = new TaskEvent<T>(); 
		}

		TaskEvent<T>* taskEvent = dynamic_cast<TaskEvent<T>*>(group[groupName]); 
		taskEvent->operator+=(handler); 
	}

	template<typename T>
	void InvokeGroup(string groupName, T eventArgs)
	{
		auto group = this->namedListenerMap[type_index(typeid(T))]; 

		ITaskEvent* task = group[groupName]; 
		TaskEvent<T>* taskEvent = dynamic_cast<TaskEvent<T>*>(task); 
		taskEvent->Invoke(eventArgs); 		
	}

	template<typename T>
	void Invoke(T eventArgs)
	{
		if (listenerMap.find(type_index(typeid(T))) == listenerMap.end()) {
			return; 
		}

		TaskEvent<T>* taskEvent = dynamic_cast<TaskEvent<T>*>(listenerMap[type_index(typeid(T))]);
		taskEvent->Invoke(eventArgs);
	}

};

#endif // EVENT_OBSERVEABLE_H