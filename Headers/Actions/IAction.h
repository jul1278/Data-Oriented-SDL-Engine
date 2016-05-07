#ifndef IACTION_H
#define IACTION_H

class IStage; 

class IAction
{
private:

public:

	IAction(IStage* stage) {};
	virtual ~IAction() {};

	virtual void Update() = 0; 
};

#endif // IACTION_H
