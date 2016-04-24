#ifndef IACTION_H
#define IACTION_H

class IGameApp; 

class IAction
{
private:

public:

	IAction() {}; 
	virtual ~IAction() {};

	virtual void Update(IGameApp* gameApp) = 0; 
};

#endif // IACTION_H
