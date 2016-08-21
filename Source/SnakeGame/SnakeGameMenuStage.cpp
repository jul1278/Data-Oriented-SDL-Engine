#include "Game/IGameApp.h"
#include "Graphics/Graphics.h"
#include "Components/Repository/ComponentCollectionRepository.h"
#include "Events/SDLEventCollector.h"
#include "Demos/SnakeGame/SnakeGameMenuStage.h"
#include "Graphics/TextGraphicsResource.h"
#include "Events/MouseButtonEventArgs.h"
#include "Events/MouseMotionEventArgs.h"
#include "Events/QuitApplicationEventArgs.h"
#include "Components/GraphicsComponent.h"
#include "Components/SimpleButtonComponent.h"
#include "Components/TransformComponent.h"
#include "Demos/SnakeGame/SnakeGameStage.h"

//----------------------------------------------------------------------------------------
// Name: SnakeGameMenuStage
// Desc: 
//----------------------------------------------------------------------------------------
SnakeGameMenuStage::SnakeGameMenuStage(IGameApp* gameApp) 
	: IStage(gameApp, new ComponentCollectionRepository, 
	new Physics(gameApp->GetGraphics()->WindowWidth(), gameApp->GetGraphics()->WindowHeight()))
{
	this->gameApp = gameApp;
	this->Setup();
}
//----------------------------------------------------------------------------------------
// Name: Setup
// Desc: 
//----------------------------------------------------------------------------------------
void SnakeGameMenuStage::Setup()
{
	auto componentCollectionRepository = this->GetComponentCollectionRepository(); 

	auto graphics = this->GetGameApp()->GetGraphics(); 
	
	this->stageHeight = graphics->WindowHeight();
	this->stageWidth = graphics->WindowWidth();

	this->sdlEventCollector = new SDLEventCollector(this->stageHeight, this->stageWidth);

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

	this->sdlEventCollector->RegisterMouseClickHandler(
		*newGameButtonComponent, *newGameTextTransform, bind(&SnakeGameMenuStage::OnMenuStartGameClick, this, placeholders::_1));
	
	this->sdlEventCollector->RegisterMouseOverHandler(
		*newGameButtonComponent, *newGameTextTransform, bind(&SnakeGameMenuStage::OnMenuStartGameMouseOver, this, placeholders::_1));
	
	this->sdlEventCollector->RegisterListener<QuitApplicationEventArgs>(
		bind(&SnakeGameMenuStage::OnQuitApplication, this, placeholders::_1));
}
//----------------------------------------------------------------------------------------
// Name: ~SnakeGameMenuStage
// Desc: 
//----------------------------------------------------------------------------------------
SnakeGameMenuStage::~SnakeGameMenuStage()
{
	for (auto action : this->actions) {
		delete action;
	}
}
//----------------------------------------------------------------------------------------
// Name: Update
// Desc: 
//----------------------------------------------------------------------------------------
void SnakeGameMenuStage::Update()
{
	auto graphics = gameApp->GetGraphics();
	auto componentCollectionRepository = this->GetComponentCollectionRepository();

	auto transformComponents = componentCollectionRepository->SelectFromCollection<TransformComponent>("MainMenu");
	auto graphicsComponents = componentCollectionRepository->SelectFromCollection<GraphicsComponent>("MainMenu");

	this->sdlEventCollector->Update();

	graphics->Clear();
	graphics->UpdateGraphics(graphicsComponents, transformComponents);
	graphics->Present();
}
//----------------------------------------------------------------------------------------
// Name: OnMenuStartGameClick
// Desc: 
//----------------------------------------------------------------------------------------
void SnakeGameMenuStage::OnMenuStartGameClick(const MouseButtonEventArgs& mouseButtonEventArgs) const
{
	if (mouseButtonEventArgs.MouseButton() == LEFT_BUTTON && mouseButtonEventArgs.Released()) {
		this->gameApp->PopStage();
		this->gameApp->PushStage(new SnakeGameStage(this->gameApp));
	}
}
//----------------------------------------------------------------------------------------
// Name: OnMenuStartGameMouseOver
// Desc: 
//----------------------------------------------------------------------------------------
void SnakeGameMenuStage::OnMenuStartGameMouseOver(const MouseMotionEventArgs& mouseMotionEventArgs) const
{
	auto startGameButtonComponents = this->GetComponentCollectionRepository()->SelectFromCollection<SimpleButtonComponent>("MainMenu");

	if (startGameButtonComponents->empty()) {
		return; 
	}

	auto& startGameButton = startGameButtonComponents->front(); 

	auto startButtonTransform = this->GetComponentCollectionRepository()->Select<TransformComponent>(startGameButton.transformComponentId); 

	if (mouseMotionEventArgs.MouseOver()) {
		startButtonTransform->scale = Vector2D(1.2f, 1.2f);
	}
	else {
		startButtonTransform->scale = Vector2D(1.0f, 1.0f);
	}
}
//----------------------------------------------------------------------------------------
// Name: OnQuitApplication
// Desc: 
//----------------------------------------------------------------------------------------
void SnakeGameMenuStage::OnQuitApplication(const QuitApplicationEventArgs& quitApplicationEventArgs) const
{
	this->gameApp->PopStage(); 
}
