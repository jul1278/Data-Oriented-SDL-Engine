#include "SpaceGame/SpaceGameMenuStage.h"
#include <Components/GraphicsComponent.h>
#include <Components/SimpleButtonComponent.h>
#include <Graphics/Graphics.h>
#include <Events/MouseButtonEventArgs.h>
#include <SpaceGame/SpaceGameStage.h>
#include <Graphics/TextGraphicsResource.h>

//--------------------------------------------------------------------------
// Name: SpaceGameMenuStage
// Desc: 
//--------------------------------------------------------------------------
SpaceGameMenuStage::SpaceGameMenuStage(IGameApp* gameApp) 
	: IStage(gameApp, new ComponentCollectionRepository, new Physics(gameApp->GetGraphics()->WindowWidth(), gameApp->GetGraphics()->WindowHeight()))
{
	auto graphics = gameApp->GetGraphics();
	auto componentCollectionRepository = this->GetComponentCollectionRepository(); 
	
	this->stageHeight = gameApp->GetGraphics()->WindowHeight();
	this->stageWidth = gameApp->GetGraphics()->WindowWidth();

	this->sdlEventCollector = new SDLEventCollector(this->stageWidth, this->stageHeight);

	// graphics owns this memory
	auto buttonGraphicsComponent = new TextGraphicsResource("Start Game", 25, Color(Color::White));
	auto newGameTextGraphicResId = graphics->AddGraphicsResource(buttonGraphicsComponent);

	componentCollectionRepository->NewCollection("MainMenu");

	auto newGameTextTransform = componentCollectionRepository->NewComponent<TransformComponent>("MainMenu");
	auto newGameTextGraphicComponent = componentCollectionRepository->NewComponent<GraphicsComponent>("MainMenu");
	auto newGameButtonComponent = componentCollectionRepository->NewComponent<SimpleButtonComponent>("MainMenu");

	newGameTextTransform->position = Vector2D(this->stageWidth / 2, this->stageHeight / 2);
	newGameTextTransform->scale = Vector2D(1.0f, 1.0f);

	newGameTextGraphicComponent->transformComponentId = newGameTextTransform->id;
	newGameTextGraphicComponent->resourceId = newGameTextGraphicResId;

	newGameButtonComponent->transformComponentId = newGameTextTransform->id;
	newGameButtonComponent->size = buttonGraphicsComponent->GetSize();

	this->sdlEventCollector->RegisterMouseClickHandler(*newGameButtonComponent, *newGameTextTransform, bind(&SpaceGameMenuStage::OnMenuStartGameClick, this, placeholders::_1));
	this->sdlEventCollector->RegisterMouseOverHandler(*newGameButtonComponent, *newGameTextTransform, bind(&SpaceGameMenuStage::OnMenuStartGameMouseOver, this, placeholders::_1));
}
//--------------------------------------------------------------------------
// Name: Update
// Desc: 
//--------------------------------------------------------------------------
void SpaceGameMenuStage::Update()
{
	auto graphics = this->GetGameApp()->GetGraphics();
	auto componentCollectionRepository = this->GetComponentCollectionRepository();

	auto transformComponents = componentCollectionRepository->SelectFromCollection<TransformComponent>("MainMenu");
	auto graphicsComponents = componentCollectionRepository->SelectFromCollection<GraphicsComponent>("MainMenu");

	this->sdlEventCollector->Update();

	graphics->Clear();
	graphics->UpdateGraphics(graphicsComponents, transformComponents);
	graphics->Present();
}
//--------------------------------------------------------------------------
// Name: OnMenuStartGameMouseOver
// Desc: 
//--------------------------------------------------------------------------
void SpaceGameMenuStage::OnMenuStartGameMouseOver(const MouseMotionEventArgs& mouseMotionEventArgs) const
{
	auto componentCollectionRepository = this->GetComponentCollectionRepository();
	auto startGameButtonComponents = componentCollectionRepository->SelectFromCollection<SimpleButtonComponent>("MainMenu");

	if (startGameButtonComponents->empty()) {
		return; 
	}

	auto& startGameButton = startGameButtonComponents->front(); 
	auto buttonTransformComponent = componentCollectionRepository->Select<TransformComponent>(startGameButton.transformComponentId); 

	if (mouseMotionEventArgs.MouseOver()) {
		buttonTransformComponent->scale = Vector2D(1.2f, 1.2f);
	}
	else {
		buttonTransformComponent->scale = Vector2D(1.0f, 1.0f);
	}
}
//--------------------------------------------------------------------------
// Name: OnMenuStartGameClick
// Desc: 
//--------------------------------------------------------------------------
void SpaceGameMenuStage::OnMenuStartGameClick(const MouseButtonEventArgs& mouseButtonEventArgs) const
{
	if (mouseButtonEventArgs.MouseButton() == LEFT_BUTTON && mouseButtonEventArgs.Released()) {
		// this->GetGameApp()->PushStage(new SpaceGameStage(this->GetGameApp()));
		this->GetGameApp()->PopStage();
	}
}