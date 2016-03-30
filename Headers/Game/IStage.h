#ifndef I_STAGE_H
#define I_STAGE_H

class IGameApp;

class IStage
{
public:

	virtual void Update(IGameApp* gameApp) = 0;
	virtual ~IStage() {}; 
};

#endif // I_STAGE_H