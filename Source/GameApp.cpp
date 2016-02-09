//
// Created by Julian  on 17/11/15.
//

#include <time.h>
#include <stdlib.h>
#include <GameApp.h>
#include <GraphicsResources/CircleFIllGraphicsResource.h>
#include <ComponentRepository.h>
#include <EntityConstructor.h>
#include <Components/SimplePhysicsComponent.h>
#include "Events\ButtonEventArgs.h"
#include "PlayerActions.h"

//------------------------------------------------------------------------------------
// Name: GameApp
// Desc:
//------------------------------------------------------------------------------------
GameApp::GameApp()
{
    this->windowHeight = 480;
    this->windowWidth = 640;
    this->appName = "Game";
	
	this->componentRepository = new ComponentRepository; 
	this->graphics = new Graphics(this->windowWidth, this->windowHeight, this->appName); 

	this->sdlEventCollector = new SDLEventCollector(); 

	this->componentRepository->RegisterComponentType<TransformComponent>();
	this->componentRepository->RegisterComponentType<GraphicsComponent>(); 
	this->componentRepository->RegisterComponentType<SimplePhysicsComponent>(); 

	this->graphics->AddGraphicsResource(new CircleFillGraphicsResource(0, "", 10.0f, 0xff, 0x8f, 0x0, 0x8f));
	
	auto entityId = EntityConstructor::ConstructBasicPlayerEntity(this->componentRepository, 0, Vector2D(400, 320), 10.0f); 
	auto entity = this->componentRepository->SelectEntity(entityId); 

	this->eventMap[type_index(typeid(ButtonEventArgs))] = new PlayerActions(entity); 
}
//------------------------------------------------------------------------------------
// Name: ~GameApp
// Desc:
//------------------------------------------------------------------------------------
GameApp::~GameApp()
{
	if (this->graphics) {
		delete this->graphics; 
	}

	if (this->componentRepository) {
		delete this->componentRepository; 
	}
}
//------------------------------------------------------------------------------------
// Name: Run
// Desc:
//------------------------------------------------------------------------------------
bool GameApp::Run()
{
	while (1)
	{
		IEventArgs* event = this->sdlEventCollector->PollEvents(); 
		
		if (this->sdlEventCollector->QuitEvent()) {
			break; 
		}

		auto graphicsComponents = this->componentRepository->Select<GraphicsComponent>(); 
		auto transformComponents = this->componentRepository->Select<TransformComponent>(); 
		auto physicsComponents = this->componentRepository->Select<SimplePhysicsComponent>(); 

		if (event != nullptr) {
			this->eventMap[type_index(typeid(ButtonEventArgs))]->Update(event);
		}

		for (auto component : *physicsComponents) {
			auto simplePhysicsComponent = component->As<SimplePhysicsComponent*>();
			simplePhysicsComponent->transformComponent->position.x += simplePhysicsComponent->velocity.x; 
			simplePhysicsComponent->transformComponent->position.y += simplePhysicsComponent->velocity.y;
		}

		this->graphics->UpdateGraphics(nullptr, graphicsComponents, transformComponents);
	}

	return false; 
}
