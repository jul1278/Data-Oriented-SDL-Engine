#ifndef FUN_TEST_MENU_STAGE_H
#define FUN_TEST_MENU_STAGE_H

#include "Game/IStage.h"
#include "Game/IGameApp.h"
#include "Events/SDLEventCollector.h"
#include "Events/MouseMotionEventArgs.h"
#include "Graphics/RectGraphicsResource.h"
#include "Components\SimpleButtonComponent.h"
#include "Utility/MathUtility.h"

class FunTestMenuStage : public IStage
{
	int stageHeight;
	int stageWidth;

	SDLEventCollector* sdlEventCollector;

	void OnMenuStartGameMouseOver(const MouseMotionEventArgs& mouseMotionEventArgs) const
	{
		
	}

	void OnMenuStartGameClick(const MouseButtonEventArgs& mouseButtonEventArgs) const;

public:

	FunTestMenuStage(IGameApp* gameApp)
		: IStage(gameApp, new ComponentRepository("FunTestMenuStage"), 
			new Physics(gameApp->GetGraphics()->WindowWidth(), gameApp->GetGraphics()->WindowHeight()))
	{
		auto graphics = gameApp->GetGraphics();
		auto componentRepository = this->GetComponentRepository();

		this->stageHeight = gameApp->GetGraphics()->WindowHeight();
		this->stageWidth = gameApp->GetGraphics()->WindowWidth();

		this->sdlEventCollector = new SDLEventCollector(this->stageWidth, this->stageHeight); 

		componentRepository->NewCollection("Squares");

		auto numVertical = 10;
		auto numHorizontal = 10; 

		for (auto i = 0; i < numVertical; i++) {
			for (auto j = 0; j < numHorizontal; j++) {

				auto height = this->stageHeight / numVertical;
				auto width = this->stageWidth / numHorizontal; 

				// graphics owns this memory
				auto rectangleGraphicsComponent = new RectGraphicsResource(width, height, Color(MathUtility::RandomIntUniformDist()));
				auto rectangleGraphicsId = graphics->AddGraphicsResource(rectangleGraphicsComponent);

				auto transform = componentRepository->NewComponent<TransformComponent>("Squares");
				auto graphicComponent = componentRepository->NewComponent<GraphicsComponent>("Squares");
				auto buttonComponent = componentRepository->NewComponent<SimpleButtonComponent>("Squares");

				graphicComponent->resourceId = rectangleGraphicsId;
				graphicComponent->transformComponentId = transform->id; 

				buttonComponent->transformComponentId = transform->id;
				buttonComponent->size = Vector2D(width, height); 

				transform->position = Vector2D((i * height) - 0.5f*height, (j * width) - 0.5f*width); 

				this->sdlEventCollector->RegisterMouseOverHandler(*buttonComponent, *transform, bind(&FunTestMenuStage::OnMenuStartGameMouseOver, this, placeholders::_1)); 
			}
		}
	}

	~FunTestMenuStage()
	{
		delete this->sdlEventCollector; 
	}

	void Update() override final
	{
		auto graphics = this->GetGameApp()->GetGraphics();
		auto componentRepository = this->GetComponentRepository();

		auto transformComponents = componentRepository->Select<TransformComponent>("Squares");
		auto graphicsComponents = componentRepository->Select<GraphicsComponent>("Squares");

		this->sdlEventCollector->Update();

		graphics->Clear();
		graphics->UpdateGraphics(graphicsComponents, transformComponents);
		graphics->Present();
	}
};

#endif // SPACE_GAME_MENU_STAGE_H