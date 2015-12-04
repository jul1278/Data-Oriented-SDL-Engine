//
// Created by Julian  on 28/11/15.
//

#ifndef SDLRTS_TESTEVENTS_H
#define SDLRTS_TESTEVENTS_H

#ifdef _WIN32

    #include "SDL.h"
    #include "SDL_events.h"
#else

    #include "SDL2/SDL.h"
    #include "SDL2/SDL_events.h"
#endif

#include "Events/EventMap.h"
#include "Events/SimpleButtonClickEventHandler.h"
#include "Events/SimpleButtonEventHandler.h"
#include <vector>
#include <random>
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
        int windowWidth = 604;
        int windowHeight = 604;

        int numButtonsX = 30;
        int numButtonsY = 30;

        float space = 4.0f;

        this->graphics = new Graphics(windowWidth, windowHeight, testName);

        // create the event map
        EventMap eventMap;

        std::default_random_engine generator;
        std::default_random_engine normalGenerator;
        std::uniform_int_distribution<int> distribution(0, 255);
        std::normal_distribution<float> normalDistribution(300.0f, 100.0f);

        // create some components
        std::vector<BaseComponent*> clickAbleComponents;
        std::vector<BaseComponent*> graphicsComponents;
        std::vector<BaseComponent*> transformComponents;

        float buttonWidth = windowWidth / numButtonsX;
        float buttonHeight = windowHeight / numButtonsY;

        // build an array of buttons
        for ( int i = 0; i < numButtonsY; i++ ) {

            for (int j = 0; j < numButtonsX; j++) {

                int index = i*numButtonsX + j;

                clickAbleComponents.push_back(new ClickAbleComponent(index, Vector2D(buttonWidth - space, buttonHeight - space)));

                float x = j*buttonWidth + space;
                float y = i*buttonHeight + space;

                transformComponents.push_back(new TransformComponent(Vector2D(x, y), Vector2D(0.0f), Vector2D(1.0f, 1.0f)));
                graphicsComponents.push_back(new GraphicsComponent(index, index));

                uint8_t r = distribution(generator);
                uint8_t g = distribution(generator);
                uint8_t b = distribution(generator);

                this->graphics->AddGraphicsResource(new RectGraphicsResource(index, "SimpleButtonGraphicResource", buttonWidth - space, buttonHeight - space, 0xff, r, g, b));
                transformComponents[index]->id = index;
            }

        }

        // create the buttonEventHandler
        SimpleButtonEventHandler* simpleButtonEventHandler = new SimpleButtonEventHandler();

        // insert the required components
        simpleButtonEventHandler->InsertComponents(clickAbleComponents, CLICKABLE_COMPONENT);
        simpleButtonEventHandler->InsertComponents(transformComponents, TRANSFORM_COMPONENT);

        eventMap.AddEventMap(EVENT_MOUSEMOVE, simpleButtonEventHandler);

        bool mouseIsDown = false; 

        while (1) {

            SDL_Event event;
            SDL_WaitEventTimeout(&event, 1);

//            event.type = SDL_MOUSEMOTION;
//            event.motion.x = normalDistribution(normalGenerator);
//            event.motion.y = normalDistribution(normalGenerator);
//            event.motion.xrel = 0;
//            event.motion.yrel = 0;

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
