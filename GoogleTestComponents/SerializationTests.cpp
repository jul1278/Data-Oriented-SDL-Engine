#include "gtest/gtest.h"
#include "Components/Component.h"
#include "Components\TransformComponent.h"
#include "Components\GraphicsComponent.h"
#include "Utility/SerialUtility.h"
#include "Utility/FileUtility.h"
#include "Game/GameStateLoader.h"
#include "Graphics/RectGraphicsResource.h"
#include "Utility/Vector.h"

#include <map>

using namespace std;


//----------------------------------------------------------------
// Name: SerializeBaseComponent
// Desc:
//----------------------------------------------------------------
TEST(SerializationTest, SerializeBaseComponent)
{
    BaseComponent baseComponent; 

    baseComponent.id = 10;
    baseComponent.entityId = 99; 

    SerialUtility::NamedValue namedValue("BaseComponent"); 

    auto result = Component::Serialize(baseComponent, namedValue); 

    EXPECT_TRUE(result); 

	std::string id;
	std::string entityId; 

	EXPECT_TRUE(namedValue.TryGetAttribute("id", id));
	EXPECT_TRUE(namedValue.TryGetAttribute("entityId", entityId));

    EXPECT_EQ(id, "10");
    EXPECT_EQ(entityId, "99");
}
//----------------------------------------------------------------
// Name: DeserializeBaseComponent
// Desc:
//----------------------------------------------------------------
TEST(SerializationTest, DeserializeBaseComponent) 
{
    shared_ptr<Graphics> graphics(nullptr); 
    shared_ptr<ComponentRepository> componentRepository(new ComponentRepository("Test")); 

    ParseContext parseContext(componentRepository, graphics); 

	SerialUtility::NamedValue namedValue("BaseComponent");
	namedValue.AddAttribute("id", "99");
	namedValue.AddAttribute("entityId", "15");

    auto baseComponent = Component::Deserialize<BaseComponent>(namedValue, parseContext);

    EXPECT_TRUE(baseComponent);
    // EXPECT_EQ(baseComponent.id, 99); // ID is assigned by componentrepository
    EXPECT_EQ(baseComponent->entityId, 15);
}
//-----------------------------------------------------------------
// Name: SerializeTransformComponent
// Desc:
//-----------------------------------------------------------------
TEST(SerializationTest, SerializeTransformComponent)
{
    TransformComponent transformComponent; 
    transformComponent.position = Vector2D(12.0001f, 13.3434f);
    transformComponent.orientation = Vector2D(3.10f, 45.34f);
    transformComponent.scale = Vector2D(56.0f, 12.000004f); 

	SerialUtility::NamedValue namedValue("TransformComponent");

    bool result = Component::Serialize(transformComponent, namedValue);

    EXPECT_TRUE(result);

	SerialUtility::NamedValue orientationValue("orientation"), scaleValue("scale"), positionValue("position");

    auto result1 = namedValue.TryGetNamedValue("orientation", orientationValue);
    auto result2 = namedValue.TryGetNamedValue("scale", scaleValue);
    auto result3 = namedValue.TryGetNamedValue("position", positionValue);

	std::string resultStr; 
	orientationValue.TryGetAttribute("x", resultStr);
    EXPECT_EQ(resultStr,  "3.100000");
    
	orientationValue.TryGetAttribute("y", resultStr);
	EXPECT_EQ(resultStr, "45.340000");

	scaleValue.TryGetAttribute("x", resultStr);
    EXPECT_EQ(resultStr, "56.000000");
    
	scaleValue.TryGetAttribute("y", resultStr);
	EXPECT_EQ(resultStr, "12.000004");

	positionValue.TryGetAttribute("x", resultStr);
    EXPECT_EQ(resultStr, "12.000100");

	positionValue.TryGetAttribute("y", resultStr);
    EXPECT_EQ(resultStr, "13.343400");
}
//-----------------------------------------------------------------
// Name: DeserializeTransformComponent
// Desc:
//-----------------------------------------------------------------
TEST(SerializationTest, DeserializeTransformComponent)
{
    shared_ptr<Graphics> graphics(nullptr); 
    shared_ptr<ComponentRepository> componentRepository(new ComponentRepository("Test")); 

    ParseContext parseContext(componentRepository, graphics); 
    
	SerialUtility::NamedValue namedValue("TransformComponent");

    // namedValue.Add("id", "15");
    namedValue.AddAttribute("entityId", "199"); 
    namedValue.AddNamedValue("position", Vector2D(12.0f, 13.0f)); 
    namedValue.AddNamedValue("scale", Vector2D(1.0f, 4.32f));
    namedValue.AddNamedValue("orientation", Vector2D(34.0045f, 3.3443f));

    TransformComponent* transformComponent = Component::Deserialize<TransformComponent>(namedValue, parseContext);

    EXPECT_TRUE(transformComponent != nullptr);

    EXPECT_EQ(transformComponent->entityId, 199);
    EXPECT_EQ(transformComponent->position, Vector2D(12.0f, 13.0f));
    EXPECT_EQ(transformComponent->orientation, Vector2D(34.0045f, 3.3443f));
    EXPECT_EQ(transformComponent->scale, Vector2D(1.0f, 4.32f)); 
}
//-----------------------------------------------------------------
// Name: DeserializeXmlToComponent
// Desc:
//-----------------------------------------------------------------
TEST(SerializationTest, DeserializeXmlToComponent)
{
    ASSERT_TRUE(FileUtility::DirectoryExists("..//Resources//xml"));

    shared_ptr<Graphics> graphics(nullptr); 
    shared_ptr<ComponentRepository> componentRepository(new ComponentRepository("Test")); 

    ParseContext parseContext(componentRepository, graphics); 

    XmlDocument xml("..//Resources//xml//transformComponent.xml"); 

    auto namedValues = SerialUtility::XmlDocumentToNamedValues(xml); 
    auto namedValue = namedValues.front(); 

	auto transformComponent = Component::Deserialize<TransformComponent>(namedValue, parseContext);

    EXPECT_TRUE(transformComponent != nullptr);
    EXPECT_EQ(transformComponent->position, Vector2D(43.21f, 12.34f));
    EXPECT_EQ(transformComponent->scale, Vector2D(34.56f, 56.78f));
    EXPECT_EQ(transformComponent->orientation, Vector2D(9.87f, 76.45));
}
//-----------------------------------------------------------------
// Name: NamedValueToBaseComponent
// Desc:
//-----------------------------------------------------------------
//TEST(SerializationTest, NamedValueToBaseComponent)
//{
//    shared_ptr<Graphics> graphics(nullptr); 
//    shared_ptr<ComponentRepository> componentRepository(new ComponentRepository("Test")); 
//
//    ParseContext parseContext(componentRepository, graphics); 
//
//	SerialUtility::NamedValue namedValue("BaseComponent");
//    namedValue.AddAttribute("name", "base_component_1"); 
//
//    auto baseComponent = GameStateLoader::NamedValueToComponent(namedValue, parseContext);
//
//    EXPECT_TRUE(); 
//}
//-----------------------------------------------------------------
// Name: NamedValueToTransformComponent
// Desc:
//-----------------------------------------------------------------
TEST(SerializationTest, NamedValueToTransformComponent)
{
    shared_ptr<Graphics> graphics(nullptr); 
    shared_ptr<ComponentRepository> componentRepository(new ComponentRepository("Test")); 

    ParseContext parseContext(componentRepository, graphics); 

	SerialUtility::NamedValue namedValue("TransformComponent");
    namedValue.AddAttribute("name", "transform_component_1"); 
    namedValue.AddNamedValue("position", Vector2D(5.0f, 3.0f));
    namedValue.AddNamedValue("orientation", Vector2D(4.0f, 3.105f));
    namedValue.AddNamedValue("scale", Vector2D(2.50f, 1056.67f));

	auto component = Component::Deserialize<TransformComponent>(namedValue, parseContext);

    EXPECT_TRUE(component != nullptr);

    EXPECT_EQ(component->scale, Vector2D(2.50f, 1056.67f));
    EXPECT_EQ(component->position, Vector2D(5.0f, 3.0f));
    EXPECT_EQ(component->orientation, Vector2D(4.0f, 3.105f));
}
//-----------------------------------------------------------------
// Name: LoadGameStateFromXml
// Desc:
//-----------------------------------------------------------------
TEST(SerializationTest, LoadGameStateFromDirectory)
{
    shared_ptr<ComponentRepository> componentRepository(new ComponentRepository("LoadGameStateFromDirectory")); 
    shared_ptr<Graphics> graphics(new Graphics(200, 200, "TestColor"));

	auto tl = graphics->AddGraphicsResource(new RectGraphicsResource(98, 98, Color(Color::AliceBlue)));
	auto tr = graphics->AddGraphicsResource(new RectGraphicsResource(98, 98, Color(Color::Firebrick)));
	auto bl = graphics->AddGraphicsResource(new RectGraphicsResource(98, 98, Color(Color::HotPink)));
	auto br = graphics->AddGraphicsResource(new RectGraphicsResource(98, 98, Color(Color::BlueViolet)));

	GameStateLoader gameStateLoader("..//Resources//xml//scene_test//", componentRepository, graphics); 

	//TransformComponent* tl_t = componentRepository->NewComponent<TransformComponent>();
	//TransformComponent* tr_t = componentRepository->NewComponent<TransformComponent>();
	//TransformComponent* bl_t = componentRepository->NewComponent<TransformComponent>();
	//TransformComponent* br_t = componentRepository->NewComponent<TransformComponent>();

	//GraphicsComponent* tl_g = componentRepository->NewComponent<GraphicsComponent>();
	//GraphicsComponent* tr_g = componentRepository->NewComponent<GraphicsComponent>();
	//GraphicsComponent* bl_g = componentRepository->NewComponent<GraphicsComponent>();
	//GraphicsComponent* br_g = componentRepository->NewComponent<GraphicsComponent>();

	//tl_g->transformComponentId = tl_t->id;
	//tr_g->transformComponentId = tr_t->id;
	//bl_g->transformComponentId = bl_t->id;
	//br_g->transformComponentId = br_t->id;

	//tl_g->resourceId = tl;
	//tr_g->resourceId = tr;
	//bl_g->resourceId = bl;
	//br_g->resourceId = br; 

	//tl_t->position = Vector2D(1.0f, 1.0f); 
	//tr_t->position = Vector2D(101.0f, 1.0f); 
	//bl_t->position = Vector2D(1.0f, 101.0f); 
	//br_t->position = Vector2D(101.0f, 101.0f); 
	
	auto transformComponents = componentRepository->Select<TransformComponent>();
	auto graphicsComponents = componentRepository->Select<GraphicsComponent>();

	graphics->UpdateGraphics(graphicsComponents, transformComponents);
	graphics->Present();

	SDL_Delay(10000); 

}
//-----------------------------------------------------------------
// Name: FilesInDirectory
// Desc:
//-----------------------------------------------------------------
TEST(SerializationTest, FilesInDirectory)
{
    auto xmlFiles = FileUtility::DirectoryContents("Resources//xml//", "xml"); 

    cout << endl << "XML Files: ";

    for (auto xmlFile : xmlFiles) {
        cout << xmlFile << " "; 
    }

    cout << endl; 
}

