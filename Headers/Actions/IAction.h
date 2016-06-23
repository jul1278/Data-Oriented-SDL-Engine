#ifndef IACTION_H
#define IACTION_H

class IStage; 

class IAction
{
private:

	IStage* parentStage; 

public:

	IAction(IStage* stage)
	{
		this->parentStage = stage; 
	};

	virtual ~IAction() {};

	virtual void Update() = 0; 

	IStage* GetParentStage() const
	{
		return this->parentStage; 
	}
};

#endif // IACTION_H
