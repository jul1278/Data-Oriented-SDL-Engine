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

#include "Events/Events.h"
#include "Events/ClickEventHandler.h"
#include "Components/GraphicsComponent.h"
#include "GraphicsResources/RectGraphicsResource.h"
#include "GraphicsResources/CircleFIllGraphicsResource.h"
#include <vector>
#include <random>
#include <string.h>


class TestEventsSystem
{
private:

    Graphics* graphics;
    Events* events; 
    std::string testName;

public:

    TestEventsSystem()
    {
#ifdef _WIN32 
#ifdef _DEBUG
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
#endif
        this->testName = "EventsTest";

        int windowWidth = 604;
        int windowHeight = 604;

        int numButtonsX = 30;
        int numButtonsY = 30;

        float space = 4.0f;

        this->graphics = new Graphics(windowWidth, windowHeight, testName);

       
        
        TestEvents();
    }

    ~TestEventsSystem() {}

    bool TestEvents()
    {
        this->events = new Events(); 

        // create some components
        std::vector<BaseComponent*> clickAbleComponents;
        std::vector<BaseComponent*> graphicsComponents;
        std::vector<BaseComponent*> transformComponents;

        clickAbleComponents.push_back(new ClickAbleComponent(0, 0, Vector2D(100.0f, 100.0f))); 
        graphicsComponents.push_back(new GraphicsComponent(0, 0)); 
        transformComponents.push_back(new TransformComponent(Vector2D(100.0f, 100.0f), Vector2D(0.0f), Vector2D(1.0f, 1.0f))); 

        this->graphics->AddGraphicsResource(new RectGraphicsResource(0, "RectGraphicResource", 100.0f, 100.0f, 0xff, 0x8f, 0x00, 0x8f));
        this->events->AddHandler(new ClickEventHandler());

        while (1)
        {
            SDL_Event event;
            SDL_WaitEventTimeout(&event, 1);
            
            if (event.type == SDL_QUIT) {
                break;
            }

            if (event.type == SDL_MOUSEMOTION)
            {
                Vector2D lastPos = Vector2D(event.motion.x, event.motion.y);
                Vector2D currPos = Vector2D(event.motion.x + event.motion.xrel, event.motion.y + event.motion.yrel);

                IEventInfo* mouseMoveEventInfo = new MouseMoveEvent(lastPos, currPos);
                Event mouseMoveEvent(EVENT_MOUSEMOVE, mouseMoveEventInfo);
                
                events->Update(&mouseMoveEvent, transformComponents, clickAbleComponents); 
            }

            this->graphics->UpdateGraphics(graphicsComponents, transformComponents);
        }

        for (BaseComponent* component : clickAbleComponents) {
            delete component;
        }

        for (BaseComponent* component : graphicsComponents) {
            delete component;
        }

        for (BaseComponent* component : transformComponents) {
            delete component;
        }

        delete this->graphics;

        return true; 
    }
};

#endif //SDLRTS_TESTEVENTS_H
