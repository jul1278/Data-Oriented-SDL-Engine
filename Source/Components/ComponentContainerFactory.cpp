#include "Components/Repository/ComponentContainerFactory.h"

#include "Components/BaseComponent.h"
#include "Components/TransformComponent.h"
#include "Components/GraphicsComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/VelocityComponent.h"


//------------------------------------------------------------------------------
// Name: ComponentContainerFactory
// Desc: 
//------------------------------------------------------------------------------
ComponentContainerFactory::ComponentContainerFactory()
{
    // TODO: figure out some way to automate this... 
    this->Register<BaseComponent>(); 
    this->Register<TransformComponent>();
    this->Register<GraphicsComponent>();
    this->Register<PhysicsComponent>();
    this->Register<VelocityComponent>(); 
}