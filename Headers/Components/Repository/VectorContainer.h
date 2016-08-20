#ifndef VECTOR_CONTAINER_H
#define VECTOR_CONTAINER_H

#include "Components/BaseComponent.h"

#include <vector>
#include <type_traits>
#include <algorithm>
#include <thread>

using namespace std;

const unsigned int vectorContainerReserveSize = 100;

struct IVectorContainer
{
	virtual void RemoveId(unsigned int id) = 0; 
	virtual ~IVectorContainer() {}

	virtual BaseComponent* SelectBase(unsigned int id) = 0;
};

template <typename T, typename = typename enable_if<is_base_of<BaseComponent, T>::value>::type>
struct VectorContainer : IVectorContainer
{
	vector<T> vec;

	void RemoveId(unsigned int id) override final
	{
		auto component = find_if(vec.begin(), vec.end(), [id](const T& t) { return t.id == id; });

		if (component != vec.end()) {
			swap(*component, vec.back()); 
			vec.pop_back(); 
		}
	}

	BaseComponent* SelectBase(unsigned int id) override final
	{
		auto component = find_if(vec.begin(), vec.end(), [id](const T& t) { return t.id == id; });
		return &(*component); 
	}

	VectorContainer()
	{
		vec.reserve(vectorContainerReserveSize);
	}

	typename vector<T>::iterator begin()
	{
		return this->vec.begin(); 
	}

	typename vector<T>::iterator end()
	{
		return this->vec.end(); 
	}
};

#endif // VECTOR_CONTAINER_H