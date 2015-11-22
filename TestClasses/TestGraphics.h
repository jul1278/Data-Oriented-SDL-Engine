//
// Created by Julian  on 22/11/15.
//

#ifndef SDLRTS_TESTGRAPHICS_H
#define SDLRTS_TESTGRAPHICS_H

#include "../Headers/Graphics.h"
#include "../Headers/GraphicsComponent.h"
#include "../Headers/TransformComponent.h"
#include "../Headers/GameApp.h"
#include "../Headers/RectGraphicsResource.h"

// TestGraphics
class TestGraphics
{
private:

    Graphics* graphics;

    std::vector<IGraphicsResource*> graphicsResources;

    std::vector<GraphicsComponent> graphicsComponents;
    std::vector<TransformComponent> transformComponents;

public:

    TestGraphics()
    {
        this->graphics = new Graphics(640, 480, "GraphicsTest");

        int numComponents = 100;

        srand(time(0));

        for ( int i = 0; i < numComponents; i++) {

            float randX  = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/((float) 640)));
            float randY  = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/((float) 480)));
            float angle  = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/((float) 2.0*PI)));
            float scaleX = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/((float) 50.0f)));
            float scaleY = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/((float) 50.0f)));

            int graphicsId;
            int transformId = i;
            
            graphicsId = this->graphics->AddGraphicsResource(new RectGraphicsResource(i, "rectGraphicsResource", 10.0f, 10.0f, 0xff, 0x8f, 0x00, i*0x08));

            this->graphicsComponents.push_back(GraphicsComponent(i, graphicsId, transformId));
            this->transformComponents.push_back(TransformComponent(transformId, Vector2D(randX, randY), Vector2D(angle), Vector2D(scaleX,scaleY)));
        }

        this->graphics->UpdateGraphics(this->graphicsComponents, this->transformComponents);
    }

    ~TestGraphics()
    {
        delete this->graphics;

        for (IGraphicsResource* graphicsResource : this->graphicsResources) {
            delete graphicsResource;
        }
    }

};


#endif //SDLRTS_TESTGRAPHICS_H
