//
// Created by Julian  on 28/11/15.
//

#ifndef SDLRTS_TESTEVENTS_H
#define SDLRTS_TESTEVENTS_H

#ifdef _WIN32
    #include "SDL.h"
    #include "SDL_events.h"
#elif
    #include "SDL2/SDL.h"
    #include "SDL2/SDL_events.h"
#endif

#include "Events/EventMap.h"
#include "Events/SimpleButtonClickEventHandler.h"
#include "Events/SimpleButtonEventHandler.h"
#include <vector>
#include <string.h>
#include <Components/GraphicsComponent.h>
#include <GraphicsResources/RectGraphicsResource.h>

class TestEvents
{
private:

    Graphics* graphics;
    std::string testName;

public:

    TestEvents()
    {
        this->testName = "EventsTest";
        TestEventMap();
    }

    ~TestEvents() {}

    bool TestEventMap()
    {
        this->graphics = new Graphics(640, 480, testName);

        // create the event map
        EventMap eventMap;

        // create some components
        std::vector<BaseComponent*> clickAbleComponents;
        std::vector<BaseComponent*> graphicsComponents;
        std::vector<BaseComponent*> transformComponents;

        clickAbleComponents.push_back(new ClickAbleComponent(0, Vector2D(50.0f, 50.0f)));
        transformComponents.push_back(new TransformComponent(Vector2D(5.0f, 5.0f), Vector2D(0.0f), Vector2D(1.0f, 1.0f)));
        graphicsComponents.push_back(new GraphicsComponent(0, 0));

        clickAbleComponents.push_back(new ClickAbleComponent(1, Vector2D(50.0f, 50.0f)));
        transformComponents.push_back(new TransformComponent(Vector2D(5.0f, 60.0f), Vector2D(0.0f), Vector2D(1.0f, 1.0f)));
        graphicsComponents.push_back(new GraphicsComponent(1, 1));

        clickAbleComponents.push_back(new ClickAbleComponent(2, Vector2D(50.0f, 50.0f)));
        transformComponents.push_back(new TransformComponent(Vector2D(60.0f, 5.0f), Vector2D(0.0f), Vector2D(1.0f, 1.0f)));
        graphicsComponents.push_back(new GraphicsComponent(2, 2));

        clickAbleComponents.push_back(new ClickAbleComponent(3, Vector2D(50.0f, 50.0f)));
        transformComponents.push_back(new TransformComponent(Vector2D(60.0f, 60.0f), Vector2D(0.0f), Vector2D(1.0f, 1.0f)));
        graphicsComponents.push_back(new GraphicsComponent(3, 3));

        transformComponents[1]->id = 1;
        transformComponents[2]->id = 2;
        transformComponents[3]->id = 3;

        
        // graphics
        this->graphics->AddGraphicsResource(new RectGraphicsResource(0, "RedButtonGraphicResource", 50.0f, 50.0f, 0xff, 0xff, 0x00, 0x00 ));
        this->graphics->AddGraphicsResource(new RectGraphicsResource(0, "GreenButtonGraphicResource", 50.0f, 50.0f, 0xff, 0x00, 0xff, 0x00));
        this->graphics->AddGraphicsResource(new RectGraphicsResource(0, "BlueButtonGraphicResource", 50.0f, 50.0f, 0xff, 0x00, 0x00, 0xff));
        this->graphics->AddGraphicsResource(new RectGraphicsResource(0, "PurpleButtonGraphicResource", 50.0f, 50.0f, 0xff, 0x8f, 0x00, 0x8f));


        // create the buttonEventHandler
        SimpleButtonEventHandler* simpleButtonEventHandler = new SimpleButtonEventHandler();

        // insert the required components
        simpleButtonEventHandler->InsertComponents(clickAbleComponents, CLICKABLE_COMPONENT);
        simpleButtonEventHandler->InsertComponents(transformComponents, TRANSFORM_COMPONENT);

        eventMap.AddEventMap(EVENT_MOUSEMOVE, simpleButtonEventHandler);
        
        bool mouseIsDown = false; 

        while (1) {

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

                eventMap.RaiseEvent(&mouseMoveEvent); 
                eventMap.ProcessEvents();
            }

            this->graphics->UpdateGraphics(graphicsComponents, transformComponents);
        }

        return true;
    }
};

#endif //SDLRTS_TESTEVENTS_H
