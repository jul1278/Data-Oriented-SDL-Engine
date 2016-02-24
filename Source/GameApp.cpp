//
// Created by Julian  on 17/11/15.
//

#include <time.h>
#include <stdlib.h>
#include <memory>
#include <GameApp.h>
#include <typeinfo>
#include <typeindex>
#include <GraphicsResources/CircleFIllGraphicsResource.h>
#include <GraphicsResources/RectGraphicsResource.h>
#include <GraphicsResources/TriangleGraphicsResource.h>
#include <ComponentRepository.h>
#include <GameEntityConstructor.h>
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

	auto spaceShipGraphicResId = this->graphics->LoadGraphicResource("Resources//space_ship.png", "spaceShip"); 
	this->graphics->AddGraphicsResource(new RectGraphicsResource(1, "", 2.0f, 12.0f, 0xff, 0xff, 0x00, 0x00)); 
	auto skullGraphicResId = this->graphics->LoadGraphicResource("Resources//skull_1.png", "skull1");

	auto entityId = EntityConstructor::ConstructBasicPlayerEntity(this->componentRepository, spaceShipGraphicResId, Vector2D(320, 420), 10.0f);
	auto entity = this->componentRepository->SelectEntity(entityId); 

	this->InsertEventMapAction(new PlayerActions(entity, this->componentRepository), type_index(typeid(ButtonEventArgs))); 
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

	for (auto eventActionsPair : this->eventMap) {
		eventActionsPair.second.remove_if([](IAction* action) {delete action; return true; });
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

			if (typeid(*event) == typeid(ButtonEventArgs)) {
				for (auto actions : this->eventMap[type_index(typeid(ButtonEventArgs))]) {
					actions->Update(event); 
				}
			}


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
