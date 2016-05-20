#ifndef PHYSICS_H
#define PHYSICS_H

#include "Events\CollisionEventArgs.h"
#include "Components\ComponentCollectionRepository.h"

class IPhysicsTask;

class Physics
{
private:

	list<IPhysicsTask*> tasks; 
	unordered_map<string, IPhysicsTask*> namedTasks; 

	int width; 
	int height;

public:

	Physics(int width, int height) 
	{
		this->width = width; 
		this->height = height;
	}

	~Physics();

	void AddPhysicsTask(IPhysicsTask* physicsTask); 

	void ExecuteTasks(ComponentCollectionRepository* componentCollectionRepository); 
	void SolveAsteroidPhysics(ComponentCollectionRepository* componentCollectionRepository) const;
	static void SolvePhysics(ComponentCollectionRepository* componentCollectionRepository, const string& collectionName);
	static void SolveSimplePhysics(ComponentCollectionRepository* componentCollectionRepository, const string& collectionName);  
};

#endif // PHYSICS_H