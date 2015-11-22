//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_TESTGRAPHICS_H
#define SDLRTS_TESTGRAPHICS_H

#include "../Headers/Graphics.h"
#include "../Headers/GraphicsComponent.h"
#include "../Headers/TransformComponent.h"
#include "../Headers/GameApp.h"

// TestGraphics
class TestGraphics
{
private:

    Graphics* graphics;

    std::vector<GraphicsComponent> graphicsComponents;
    std::vector<TransformComponent> transformComponents;

public:

    TestGraphics()
    {
        this->graphics = new Graphics(640, 480, "GraphicsTest");

        int numComponents = 20;

        for ( int i = 0; i < numComponents; i++) {

            float randX = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/ ((float) 480)));
            float randY = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/((float) 680)));
            float angle = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/((float) 2.0*PI)));
            float scaleX = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/((float) 50.0f)));
            float scaleY = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/((float) 50.0f)));

            ResourceIds resourceId = (i % 2) ? RESOURCE_ID_BLUE_SQUARE : RESOURCE_ID_RED_SQUARE;

            this->graphicsComponents.push_back(GraphicsComponent(i, resourceId, i));
            this->transformComponents.push_back(TransformComponent(i, Vector2D(randX, randY), Vector2D(angle), Vector2D(scaleX,scaleY)));
        }

        this->graphics->UpdateGraphics(this->graphicsComponents, this->transformComponents);
    }

    ~TestGraphics()
    {
        delete this->graphics;
    }

};


#endif //SDLRTS_TESTGRAPHICS_H
