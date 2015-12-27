//
// Created by Julian  on 28/11/15.
//

#ifndef SDLRTS_TESTEVENTS_H
#define SDLRTS_TESTEVENTS_H

#ifdef _WIN32

#include "SDL.h"
#include "SDL_events.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#else

#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#endif

#include "Events/MouseEventHandler.h"
#include "Components/GraphicsComponent.h"
#include "GraphicsResources/RectGraphicsResource.h"
#include "GraphicsResources/CircleFIllGraphicsResource.h"
#include <vector>
#include <random>
#include <string.h>
#include <Events/SimpleButtonEventHandler.h>


class TestEventsSystem
{
private:

    Graphics* graphics;
    //Events* events; 
    std::string testName;

    int windowWidth;
    int windowHeight;

public:

    TestEventsSystem()
    {
#ifdef _WIN32 
#ifdef _DEBUG
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
#endif
        this->testName = "EventsTest";

        this->windowWidth = 800;
        this->windowHeight = 600;

        this->graphics = new Graphics(windowWidth, windowHeight, testName);

        TestEvents();
    }

    ~TestEventsSystem() {}

	void TestEvents()
    {
		// setup components and id's
		TransformComponent parentButtonTransformComponent = TransformComponent(Vector2D(10.0f, 10.0f));
		ClickAbleComponent parentButtonClickAbleComponent = ClickAbleComponent(0, 0, Vector2D(50.0f, 50.0f)); 
		GraphicsComponent parentButtonGraphicsComponent = GraphicsComponent(0, 0); 

		TransformComponent childButtonTransformComponent = TransformComponent(Vector2D(50.0f, 10.0f)); 
		ClickAbleComponent childButtonClickAbleComponent = ClickAbleComponent(3, 1, Vector2D(50.0f, 50.0f));
		GraphicsComponent childButtonGraphicsComponent = GraphicsComponent(1, 3); 

		parentButtonTransformComponent.id = 0;
		childButtonTransformComponent.id = 1;

		parentButtonClickAbleComponent.id = 2;
		childButtonClickAbleComponent.id = 3;

		parentButtonGraphicsComponent.id = 4; 
		childButtonGraphicsComponent.id = 5; 

		map<int, IBaseComponent*> graphicsComponents = map<int, IBaseComponent*>
		{
			pair<int, IBaseComponent*>(parentButtonGraphicsComponent.id, &parentButtonGraphicsComponent),
				pair<int, IBaseComponent*>(childButtonGraphicsComponent.id, &childButtonGraphicsComponent)
		};

		map<int, IBaseComponent*> transformComponents = map<int, IBaseComponent*>
		{
			pair<int, IBaseComponent*>(parentButtonTransformComponent.id, &parentButtonTransformComponent),
				pair<int, IBaseComponent*>(childButtonTransformComponent.id, &childButtonTransformComponent)
		};


		IEventHandler* mouseEventHandler = new MouseEventHandler(0); 

		// register with the mouse handler
		mouseEventHandler->AddComponents(TRANSFORM_COMPONENT, &parentButtonTransformComponent); 
		mouseEventHandler->AddComponents(CLICKABLE_COMPONENT, &parentButtonClickAbleComponent);
		mouseEventHandler->AddComponents(TRANSFORM_COMPONENT, &childButtonTransformComponent); 
		mouseEventHandler->AddComponents(CLICKABLE_COMPONENT, &childButtonClickAbleComponent); 

		// graphics
		this->graphics->AddGraphicsResource(new RectGraphicsResource(0, "", 50.0f, 50.0f, 0xff, 0xff, 0x00, 0x00)); 
		this->graphics->AddGraphicsResource(new RectGraphicsResource(0, "", 50.0f, 50.0f, 0xff, 0x00, 0xff, 0x00));

		IEventHandler* simpleButtonEventHandler = new SimpleButtonEventHandler(1); 

		simpleButtonEventHandler->AddComponents(TRANSFORM_COMPONENT, &parentButtonTransformComponent);
		simpleButtonEventHandler->AddComponents(CLICKABLE_COMPONENT, &parentButtonClickAbleComponent);
		simpleButtonEventHandler->AddComponents(TRANSFORM_COMPONENT, &childButtonTransformComponent);
		simpleButtonEventHandler->AddComponents(CLICKABLE_COMPONENT, &childButtonClickAbleComponent);

		
		while (1)
		{
			SDL_Event event;
			SDL_PollEvent(&event);

			if (event.type == SDL_QUIT) {
				break;
			}

			if (event.type == SDL_MOUSEMOTION)
			{
				Vector2D lastPos = Vector2D(event.motion.x, event.motion.y);
				Vector2D currPos = Vector2D(event.motion.x + event.motion.xrel, event.motion.y + event.motion.yrel);

				IEventInfo* mouseMoveEventInfo = new MouseMoveEvent(lastPos, currPos);
				Event mouseMoveEvent(EVENT_MOUSEMOVE, mouseMoveEventInfo);
				//events->PostEvent(&mouseMoveEvent); 
				//events->Update();
			}

			this->graphics->UpdateGraphics(&event, graphicsComponents, transformComponents);
		}
    }


  //  bool TestEvents()
  //  {
  //      this->events = new Events(); 

  //      int numButtonsX = 2;
  //      int numButtonsY = 2;

  //      // create some components
  //      std::vector<BaseComponent*> clickAbleComponents;
  //      std::vector<BaseComponent*> graphicsComponents;
  //      std::vector<BaseComponent*> transformComponents;

  //      clickAbleComponents.push_back(new ClickAbleComponent(0, 0, Vector2D(100.0f, 100.0f)));
  //      transformComponents.push_back(new TransformComponent(Vector2D(100.0f, 100.0f), Vector2D(0.0f), Vector2D(1.0f, 1.0f)));
  //      graphicsComponents.push_back(new GraphicsComponent(0, 0));

		//clickAbleComponents.push_back(new ClickAbleComponent(1, 0, Vector2D(100.0f, 100.0f)));
		//transformComponents.push_back(new TransformComponent(Vector2D(300.0f, 300.0f), Vector2D(0.0f), Vector2D(1.0f, 1.0f)));
		//graphicsComponents.push_back(new GraphicsComponent(0, 1));

  //      this->graphics->AddGraphicsResource(new RectGraphicsResource(0, "RectGraphicResource", 100.0f, 100.0f, 0xff, 0x8f, 0x00, 0x8f));
  //      this->events->AddHandler(new MouseEventHandler());

  //      while (1)
  //      {
  //          SDL_Event event;
  //          SDL_PollEvent(&event);
  //          
  //          if (event.type == SDL_QUIT) {
  //              break;
  //          }

  //          if (event.type == SDL_MOUSEMOTION)
  //          {
  //              Vector2D lastPos = Vector2D(event.motion.x, event.motion.y);
  //              Vector2D currPos = Vector2D(event.motion.x + event.motion.xrel, event.motion.y + event.motion.yrel);

  //              IEventInfo* mouseMoveEventInfo = new MouseMoveEvent(lastPos, currPos);
  //              Event mouseMoveEvent(EVENT_MOUSEMOVE, mouseMoveEventInfo);
  //              
  //              events->Update(&mouseMoveEvent, transformComponents, clickAbleComponents); 
  //          }

  //          this->graphics->UpdateGraphics(&event, graphicsComponents, transformComponents);
  //      }

  //      for (BaseComponent* component : clickAbleComponents) {
  //          delete component;
  //      }

  //      for (BaseComponent* component : graphicsComponents) {
  //          delete component;
  //      }

  //      for (BaseComponent* component : transformComponents) {
  //          delete component;
  //      }

  //      delete this->graphics;

  //      return true; 
  //  }
};

#endif //SDLRTS_TESTEVENTS_H
