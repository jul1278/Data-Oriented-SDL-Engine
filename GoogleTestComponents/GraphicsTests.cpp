#include "Graphics/Color.h"
#include "Graphics/Graphics.h"
#include "Components/Repository/ComponentRepository.h"
#include "Components/GraphicsComponent.h"
#include "Graphics/RectGraphicsResource.h"
#include "Graphics/BubbleGraphicsResources.h"
#include "Graphics/CircleFIllGraphicsResource.h"
#include "Graphics/CircleOutlineGraphicsResource.h"
#include "Graphics/GridGraphicsResource.h"
#include "Graphics/SpriteGraphicsResource.h"
#include "Graphics/TextGraphicsResource.h"
#include "Graphics/ProceduralAsteroidGraphicsResource.h"
#include "gtest/gtest.h"

#include <iostream>

Graphics* graphics; 

TEST(GraphicsTests, TestColor)
{
	graphics = new Graphics(200, 200, "TestColor");
	ComponentRepository componentRepository("Test");
	auto numComponents = 20U;

	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::AliceBlue)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::Bisque)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::Chocolate)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::DarkCyan)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::Firebrick)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::Gainsboro)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::Honeydew)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::IndianRed)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::Khaki)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::Lavender)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::Magenta)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::NavajoWhite)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::OldLace)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::PaleGoldenrod)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::Red)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::SaddleBrown)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::Tan)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::Violet)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::White)));
	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::Yellow)));

	for (auto i = 0; i < numComponents; i++) {

		auto transformComponent = componentRepository.NewComponent<TransformComponent>(); 
		auto graphicsComponent = componentRepository.NewComponent<GraphicsComponent>();

		graphicsComponent->resourceId = i + 1; 
		graphicsComponent->transformComponentId = transformComponent->id; 

		transformComponent->position = Vector2D((i + 1)*6.0f, (i + 1)*6.0f); 
				
		graphics->Clear();

		auto transformComponents = componentRepository.Select<TransformComponent>();
		auto graphicsComponents = componentRepository.Select<GraphicsComponent>();

		graphics->UpdateGraphics(graphicsComponents, transformComponents);
		graphics->Present();
		SDL_Delay(100); 
	}

	// auto transformComponents = componentRepository.Select<TransformComponent>();
	// auto graphicsComponents = componentRepository.Select<GraphicsComponent>();

	// graphics->Clear();
	// graphics->UpdateGraphics(graphicsComponents, transformComponents);
	// graphics->Present();

	// graphics->AddGraphicsResource(new RectGraphicsResource(200, 40, Color(Color::AliceBlue))); 

	delete graphics; 
}

TEST(GraphicsTests, TestShapes)
{
	graphics = new Graphics(500, 500, "TestShapes");
	ComponentRepository componentRepository("Test");

	graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::AliceBlue)));
	graphics->AddGraphicsResource(new BubbleGraphicsResource(10.0f));
	graphics->AddGraphicsResource(new CircleFillGraphicsResource(30.0f, Color(Color::Chocolate)));
	graphics->AddGraphicsResource(new CircleOutlineGraphicsResource(40.0f, 10.0f, Color(Color::DarkCyan)));
	graphics->AddGraphicsResource(new GridGraphicsResource(15.0f, 5, 5, Color(Color::DeepPink)));
	auto graphicId = graphics->LoadGraphicResource("//Resources//space_ship.png"); 
	graphics->AddGraphicsResource(new TextGraphicsResource("Red Hello World!", 20, Color(Color::IndianRed), "//Resources//Anonymous_Pro.ttf"));
	graphics->AddGraphicsResource(new TextGraphicsResource("HIROSH", 20, Color(Color::Gold), "//Resources//HIROSHT.ttf"));
	graphics->AddGraphicsResource(new BubbleGraphicsResource(100.0f));
	graphics->AddGraphicsResource(new ProceduralAsteroidGraphicsResource(45.0f, 0.6f, 10)); 

	vector<Vector2D> vectors; 

	vectors.push_back(Vector2D(10.0f, 10.0f));
	vectors.push_back(Vector2D(100.0f, 100.0f));
	vectors.push_back(Vector2D(250.0f, 250.0f));
	vectors.push_back(Vector2D(280.0f, 250.0f));
	vectors.push_back(Vector2D(300.0f, 300.0f));
	vectors.push_back(Vector2D(250.0f, 250.0f));
	vectors.push_back(Vector2D(400.0f, 400.0f));
	vectors.push_back(Vector2D(250.0f, 400.0f));
	vectors.push_back(Vector2D(150.0f, 400.0f));
	vectors.push_back(Vector2D(300.0f, 150.0f));

	for (auto i = 0; i < 10; i++) {

		auto graphicsComponent = componentRepository.NewComponent<GraphicsComponent>();
		auto transformComponent = componentRepository.NewComponent<TransformComponent>();
		
		transformComponent->position = vectors[i]; 

		graphicsComponent->resourceId = i + 1; 
		graphicsComponent->transformComponentId = transformComponent->id; 
	}

	auto transformComponents = componentRepository.Select<TransformComponent>();
	auto graphicsComponents = componentRepository.Select<GraphicsComponent>(); 

	//transformComponents[5].scale = Vector2D(0.5f, 0.8f); 
	//transformComponents[5].orientation = Vector2D(5.0f); 
	//transformComponents[6].orientation = Vector2D(2.0f); 

	graphics->Clear();
	graphics->UpdateGraphics(graphicsComponents, transformComponents);
	graphics->Present();

	graphics->AddGraphicsResource(new RectGraphicsResource(200, 40, Color(Color::AliceBlue)));

	SDL_Delay(5000);

	delete graphics;
}
