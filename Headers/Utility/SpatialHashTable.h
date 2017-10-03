#ifndef SPATIAL_HASH_TABLE_H
#define SPATIAL_HASH_TABLE_H

#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <memory>
#include <assert.h>


//-----------------------------------------------------------------------------------------------------------------------
// Name: Quad
// Desc:
//-----------------------------------------------------------------------------------------------------------------------
template<typename T>
struct Quad {
	
	const T obj;
	
	unsigned int topLeftX; 
	unsigned int topLeftY;

	unsigned int width; 
	unsigned int height; 

	//-----------------------------------------------------------------------------------------------------------------------
	// Name: Quad
	// Desc:
	//-----------------------------------------------------------------------------------------------------------------------
	Quad(unsigned int topLeftX, unsigned int topLeftY, unsigned int width, unsigned int height, const T& setObj) :
		obj(setObj), topLeftX(topLeftX), topLeftY(topLeftY), width(width), height(height) 
	{
	} 

	//-----------------------------------------------------------------------------------------------------------------------
	// Name: ContainsPoint
	// Desc:
	//-----------------------------------------------------------------------------------------------------------------------
	bool ContainsPoint(unsigned int x, unsigned int y) 
	{
		if (x >= this->topLeftX && y >= this->topLeftY) {
			
			if (x <= (this->width + this->topLeftX)
				&& y <= (this->height + this->topLeftY)) {
				
				return true; 
			}
		}

		return false; 
	}
};

//-----------------------------------------------------------------------------------------------------------------------
// Name: SpatialHashTable
// Desc:
//-----------------------------------------------------------------------------------------------------------------------
template<typename T>
class SpatialHashTable 
{
	std::vector<std::list<std::shared_ptr<Quad<T>>>> buckets;


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

		auto quadPtr = std::shared_ptr<Quad<T>>(new Quad<T>(topLeftX, topLeftY, width, height, obj)); 

		for (unsigned int y = yStart; y <= yEnd; y++) {
			for (unsigned int x = xStart; x <= xEnd; x++) {

				auto index = x + y * xBuckets;
				if (index < buckets.size()) {

					buckets[index].push_back(quadPtr);
				}
			}
		}
	}
	
	//-----------------------------------------------------------------------------------------------------------------------
	// Name: Query
	// Desc:
	//-----------------------------------------------------------------------------------------------------------------------
	std::list<std::shared_ptr<Quad<T>>> Query(unsigned int topLeftX, unsigned int topLeftY, unsigned int width, unsigned int height)
	{
		std::list<std::shared_ptr<Quad<T>>> query;

		if (topLeftX > this->width || topLeftY > this->height) {
			return query;
		}

		std::set<std::shared_ptr<Quad<T>>> querySet;

		auto xStart = topLeftX / this->bucketSizeX;
		auto xEnd = (topLeftX + width) / this->bucketSizeX;

		auto yStart = topLeftY / this->bucketSizeY;
		auto yEnd = (topLeftY + height) / this->bucketSizeY;

		for (unsigned int y = yStart; y <= yEnd; y++) {
			for (unsigned int x = xStart; x <= xEnd; x++) {

				auto index = x + y * xBuckets;

				if (index < buckets.size()) {
					for (auto& c : buckets[index]) {

						// is c in the set? if not insert it
						if (querySet.find(c) == querySet.end()) {
							query.push_back(c);
							querySet.insert(c); 
						}
					}
				}
			}
		}

		return query; 
	}

	//-----------------------------------------------------------------------------------------------------------------------
	// Name: Query
	// Desc:
	//-----------------------------------------------------------------------------------------------------------------------
	std::list<std::shared_ptr<Quad<T>>> Query(unsigned int x, unsigned int y)
	{
		std::list<std::shared_ptr<Quad<T>>> query;

		if (x > this->width || y > this->height) {
			return query;
		}

		std::set<std::shared_ptr<Quad<T>>> querySet; 

		auto xIndex = x / xBuckets; 
		auto yIndex = y / yBuckets; 

		auto index = xIndex + yIndex * xBuckets;

		if (index < buckets.size()) {

			for (auto& c : buckets[index]) {
						
				if (c->ContainsPoint(x, y)) {

					if (querySet.find(c) == querySet.end()) {
						query.push_back(c);
						querySet.insert(c); 
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
		std::for_each(this->buckets.front(), this->buckets->back(), [] (std::list<Quad<T>>& l) { l.clear(); });
	}
};

#endif // SPATIAL_HASH_TABLE_H
