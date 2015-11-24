//
// Created by Julian  on 17/11/15.
//

#include "../Headers/GameApp.h"
#include "../Headers/Transforms/PlayerMoveTransform.h"
#include "../Headers/GraphicsResources/CircleGraphicsResource.h"
#include <time.h>
#include <stdlib.h>
//------------------------------------------------------------------------------------
// Name: GameApp
// Desc:
//------------------------------------------------------------------------------------
GameApp::GameApp()
{
    this->windowHeight = 480;
    this->windowWidth = 640;
    this->appName = "SDL RTS";

    this->graphics = new Graphics(this->windowWidth, this->windowHeight, this->appName);

    // TODO: move most of this out somewhere else

    Entity* playerEntity = new Entity;

    this->componentSpecs = new ComponentSpecs;
    this->componentSpecs->RegisterEntitySpec("BasicPlayer", std::vector<ComponentType>({TRANSFORM_COMPONENT, GRAPHICS_COMPONENT}));

    this->entityTransforms.push_back(new PlayerMoveTransform(this->componentSpecs));


    int id = this->graphics->AddGraphicsResource(new CircleGraphicsResource(0, "resource", 10.0f, 0xff, 0x8f, 0x00, 0x8f));

    this->graphicsComponents.push_back(GraphicsComponent(0,id,0));
    this->transformComponents.push_back(TransformComponent(0, Vector2D(100.0f, 100.0f), Vector2D(0.0f), Vector2D(1.0f, 1.0f)));

    playerEntity->AddComponent(TRANSFORM_COMPONENT, &this->transformComponents[0]);
    playerEntity->AddComponent(GRAPHICS_COMPONENT, &this->graphicsComponents[0]);

    this->entityList.push_back(playerEntity);
}
//------------------------------------------------------------------------------------
// Name: ~GameApp
// Desc:
//------------------------------------------------------------------------------------
GameApp::~GameApp()
{
    for (Entity* entity : this->entityList) {
        delete entity;
    }

    delete this->graphics;
}
//------------------------------------------------------------------------------------
// Name: Run
// Desc:
//------------------------------------------------------------------------------------
bool GameApp::Run()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        return true;
    }

    for (IEntityTransform* entityTransform : this->entityTransforms) {

        this->entityList = entityTransform->Transform(this->entityList, &event);
    }

    this->graphics->UpdateGraphics(this->graphicsComponents, this->transformComponents);

    return false;
}
