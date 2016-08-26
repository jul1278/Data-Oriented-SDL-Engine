#ifndef PHYSICS_H
#define PHYSICS_H

#include "Events/CollisionEventArgs.h"
#include "Components/Repository/ComponentRepository.h"

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

	void ExecuteTasks(ComponentRepository* componentRepository); 
	void SolveAsteroidPhysics(ComponentRepository* componentRepository) const;
	static void SolvePhysics(ComponentRepository* componentRepository, const string& collectionName);
	static void SolveSimplePhysics(ComponentRepository* componentRepository, const string& collectionName);  
};

#endif // PHYSICS_H