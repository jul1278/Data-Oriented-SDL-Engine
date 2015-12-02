//
// Created by Julian  on 28/11/15.
//

#ifndef SDLRTS_TESTEVENTS_H
#define SDLRTS_TESTEVENTS_H

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

        clickAbleComponents.push_back(new ClickAbleComponent(0, Vector2D(100.0f, 80.0f)));
        transformComponents.push_back(new TransformComponent(Vector2D(100.0f, 100.0f), Vector2D(0.0f), Vector2D(1.0f, 1.0f)));
        graphicsComponents.push_back(new GraphicsComponent(0, 0));

        // graphics
        this->graphics->AddGraphicsResource(new RectGraphicsResource(0, "ButtonGraphicResource", 100.0f, 80.0f, 0xff, 0x8f, 0x00, 0x8f ));

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

            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                mouseIsDown = true; 
            }

            if (event.type == SDL_MOUSEBUTTONUP && mouseIsDown) {
                mouseIsDown = false; 
                IEventInfo* mouseEventInfo = new MouseClickEvent(Vector2D(event.button.x, event.button.y));
                Event mouseClickEvent(EVENT_MOUSECLICK, mouseEventInfo);
                eventMap.RaiseEvent(&mouseClickEvent);
                eventMap.ProcessEvents();
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
