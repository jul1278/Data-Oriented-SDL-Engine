#include "stdafx.h"
#include "CppUnitTest.h"

#include "Graphics/Color.h"
#include "Graphics/Graphics.h"
#include "Components/ComponentCollectionRepository.h"
#include <Components/GraphicsComponent.h>
#include "Graphics/RectGraphicsResource.h"
#include <iostream>
#include <Graphics/BubbleGraphicsResources.h>
#include "Graphics/CircleFIllGraphicsResource.h"
#include "Graphics/CircleOutlineGraphicsResource.h"
#include <Graphics/GridGraphicsResource.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphicsTest
{
	TEST_CLASS(GraphicsTests)
	{
		Graphics* graphics; 

		TEST_METHOD(TestColor)
		{
			graphics = new Graphics(200, 200, "TestColor");
			ComponentCollectionRepository componentCollection;
			auto numComponents = 20U;

			vector<GraphicsComponent> graphicsComponents; 
			vector<TransformComponent> transformComponents; 
			
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

				graphicsComponents.push_back(GraphicsComponent(i+1, i));

				transformComponents.push_back(TransformComponent(Vector2D((i + 1)*6.0f, (i + 1)*6.0f)));
				transformComponents[i].id = i; 
				
				graphics->Clear();
				graphics->UpdateGraphics(&graphicsComponents, &transformComponents);
				graphics->Present();

				SDL_Delay(500); 
			}

			graphics->Clear();
			graphics->UpdateGraphics(&graphicsComponents, &transformComponents);
			graphics->Present();

			graphics->AddGraphicsResource(new RectGraphicsResource(200, 40, Color(Color::AliceBlue))); 

			SDL_Delay(5000); 

			delete graphics; 
		}

		TEST_METHOD(TestShapes)
		{
			graphics = new Graphics(200, 200, "TestShapes");
			ComponentCollectionRepository componentCollection;
			
			vector<GraphicsComponent> graphicsComponents;
			vector<TransformComponent> transformComponents;

			graphics->AddGraphicsResource(new RectGraphicsResource(20, 20, Color(Color::AliceBlue)));
			graphics->AddGraphicsResource(new BubbleGraphicsResource(10.0f));
			graphics->AddGraphicsResource(new CircleFillGraphicsResource(30.0f, Color(Color::Chocolate)));
			graphics->AddGraphicsResource(new CircleOutlineGraphicsResource(40.0f, 10.0f, Color(Color::DarkCyan)));
			graphics->AddGraphicsResource(new GridGraphicsResource(5.0f, 5, 5, Color(Color::Firebrick)));

			graphicsComponents.push_back(GraphicsComponent(1, 0));
			transformComponents.push_back(TransformComponent(Vector2D(10.0f, 10.0f)));
			
			graphicsComponents.push_back(GraphicsComponent(2, 1));
			transformComponents.push_back(TransformComponent(Vector2D(100.0f, 100.0f)));
			
			graphicsComponents.push_back(GraphicsComponent(3, 2));
			transformComponents.push_back(TransformComponent(Vector2D(50.0f, 50.0f)));

			graphicsComponents.push_back(GraphicsComponent(4, 3));
			transformComponents.push_back(TransformComponent(Vector2D(70.0f, 50.0f)));

			transformComponents[0].id = 0;
			transformComponents[1].id = 1;
			transformComponents[2].id = 2;
			transformComponents[3].id = 3;

			graphics->Clear();
			graphics->UpdateGraphics(&graphicsComponents, &transformComponents);
			graphics->Present();

			graphics->AddGraphicsResource(new RectGraphicsResource(200, 40, Color(Color::AliceBlue)));

			SDL_Delay(5000);

			delete graphics;

		}
	};
}