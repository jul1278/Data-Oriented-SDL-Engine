#ifndef ITRANSFORM_H
#define ITRANSFORM_H

struct TransformComponent;

class ITransform
{
public:
	virtual ~ITransform() {}
	virtual TransformComponent* operator()() = 0;
};

#endif // ITRANSFORM_H