#ifndef IACTION_H
#define IACTION_H

#include <ComponentCollectionRepository.h>
#include <functional>

class IAction
{
private:

public:

	IAction() {}; 
	virtual ~IAction() {};

	virtual void Update(ComponentCollectionRepository* componentCollectionRepository) = 0; 
};

#endif // IACTION_H
