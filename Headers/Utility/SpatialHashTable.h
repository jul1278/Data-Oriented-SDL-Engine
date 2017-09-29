#ifndef SPATIAL_HASH_TABLE_H
#define SPATIAL_HASH_TABLE_H

#include <vector>
#include <list>
#include <algorithm>
#include <assert.h>

template<typename T>
class SpatialHashTable 
{
	std::vector<std::list<T>> buckets; 

	unsigned int width; 
	unsigned int height; 

	unsigned int xBuckets; 
	unsigned int yBuckets; 

	unsigned int bucketSizeX; 
	unsigned int bucketSizeY; 

public:

	//-----------------------------------------------------------------------------------------------------------------------
	// Name: SpatialHashTable
	// Desc:
	//-----------------------------------------------------------------------------------------------------------------------
	SpatialHashTable(unsigned int width, unsigned int height, unsigned int xBuckets, unsigned int yBuckets) 
		: width(width), height(height), xBuckets(xBuckets), yBuckets(yBuckets)
	{
		assert(width % xBuckets == 0); 
		assert(height % yBuckets == 0); 

		bucketSizeX = width / xBuckets;
		bucketSizeY = height / yBuckets; 

		this->buckets.resize(xBuckets * yBuckets); 
	}

	//-----------------------------------------------------------------------------------------------------------------------
	// Name: Hash
	// Desc:
	//-----------------------------------------------------------------------------------------------------------------------
	void Hash(unsigned int topLeftX, unsigned int topLeftY, unsigned int width, unsigned int height, const T& obj)
	{
		if (topLeftX > this->width || topLeftY > this->height) {
			return; 
		}

		auto xStart = topLeftX / this->bucketSizeX; 
		auto xEnd = (topLeftX + width) / this->bucketSizeX; 

		auto yStart = topLeftY / this->bucketSizeY;
		auto yEnd = (topLeftY + height) / this->bucketSizeY; 

		for (unsigned int y = yStart; y <= yEnd; y++) {
			for (unsigned int x = xStart; x <= xEnd; x++) {

				auto index = x + y * xBuckets; 

				if (index < buckets.size()) {
					buckets[index].push_back(obj);
				}
			}
		}
	}
	
	//-----------------------------------------------------------------------------------------------------------------------
	// Name: Query
	// Desc:
	//-----------------------------------------------------------------------------------------------------------------------
	std::list<T> Query(unsigned int topLeftX, unsigned int topLeftY, unsigned int width, unsigned int height)
	{
		std::list<T> query; 

		if (topLeftX > this->width || topLeftY > this->height) {
			return std::list<T>();
		}

		auto xStart = topLeftX / this->bucketSizeX;
		auto xEnd = (topLeftX + width) / this->bucketSizeX;

		auto yStart = topLeftY / this->bucketSizeY;
		auto yEnd = (topLeftY + height) / this->bucketSizeY;

		for (unsigned int y = yStart; y <= yEnd; y++) {
			for (unsigned int x = xStart; x <= xEnd; x++) {

				auto index = x + y * xBuckets;

				if (index < buckets.size()) {

					for (auto c : buckets[index]) {
						query.push_back(c);
					}
				}
			}
		}

		return query; 
	}

	//-----------------------------------------------------------------------------------------------------------------------
	// Name: Clear
	// Desc:
	//-----------------------------------------------------------------------------------------------------------------------
	void Clear()
	{
		std::for_each(this->buckets.front(), this->buckets->back(), [](std::list<T>& l) {l.clear(); }); 
	}
};

#endif // SPATIAL_HASH_TABLE_H
