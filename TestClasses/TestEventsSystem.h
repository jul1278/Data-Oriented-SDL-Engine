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
#include "Events/MouseEventHandler.h"
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

        this->windowWidth = 604;
        this->windowHeight = 604;

        this->graphics = new Graphics(windowWidth, windowHeight, testName);

       
        
        TestEvents();
    }

    ~TestEventsSystem() {}

    bool TestEvents()
    {
        this->events = new Events(); 

        int numButtonsX = 2;
        int numButtonsY = 2;

        // create some components
        std::vector<BaseComponent*> clickAbleComponents;
        std::vector<BaseComponent*> graphicsComponents;
        std::vector<BaseComponent*> transformComponents;

        float space = 30.0f;
        float buttonWidth = this->windowWidth / numButtonsX;
        float buttonHeight = this->windowHeight / numButtonsY;

        //// build an array of buttons
        //for (int i = 0; i < numButtonsY; i++) {

        //    for (int j = 0; j < numButtonsX; j++) {

        //        int index = i*numButtonsX + j;

        //        clickAbleComponents.push_back(new ClickAbleComponent(index, 0, Vector2D(buttonWidth - space, buttonHeight - space)));

        //        float x = j*buttonWidth + space;
        //        float y = i*buttonHeight + space;

        //        transformComponents.push_back(new TransformComponent(Vector2D(x, y), Vector2D(0.0f), Vector2D(1.0f, 1.0f)));
        //        graphicsComponents.push_back(new GraphicsComponent(index, index));

        //        uint8_t r = 0x8f;
        //        uint8_t g = 0x8f;
        //        uint8_t b = 0x8f;

        //        this->graphics->AddGraphicsResource(new RectGraphicsResource(index, "SimpleButtonGraphicResource", (buttonWidth - space), (buttonWidth - space), 0xff, r, g, b));
        //        transformComponents[index]->id = index;
        //    }
        //}

        clickAbleComponents.push_back(new ClickAbleComponent(0, 0, Vector2D(100.0f, 100.0f)));
        transformComponents.push_back(new TransformComponent(Vector2D(100.0f, 100.0f), Vector2D(0.0f), Vector2D(1.0f, 1.0f)));
        graphicsComponents.push_back(new GraphicsComponent(0, 0));

        this->graphics->AddGraphicsResource(new RectGraphicsResource(0, "RectGraphicResource", 100.0f, 100.0f, 0xff, 0x8f, 0x00, 0x8f));
        this->events->AddHandler(new MouseEventHandler());

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
