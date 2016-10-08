#include "gtest/gtest.h"
#include "Components/Component.h"
#include "Utility/SerialUtility.h"
#include "Utility/FileUtility.h"

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

    NamedValue namedValue; 

    auto result = Component::Serialize(baseComponent, &namedValue); 

    EXPECT_TRUE(result); 
    EXPECT_EQ(namedValue.GetNamedValue("id"), "10");
    EXPECT_EQ(namedValue.GetNamedValue("entityId"), "99");
}
//----------------------------------------------------------------
// Name: DeserializeBaseComponent
// Desc:
//----------------------------------------------------------------
TEST(SerializationTest, DeserializeBaseComponent) 
{
    BaseComponent baseComponent; 

    NamedValue namedValue; 
    namedValue.Add("id", "99");
    namedValue.Add("entityId", "15");

    auto result = Component::Deserialize(namedValue, &baseComponent);

    EXPECT_TRUE(result);
    // EXPECT_EQ(baseComponent.id, 99);
    // EXPECT_EQ(baseComponent.entityId, 15);
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

    NamedValue namedValue;

    auto result = Component::Serialize(transformComponent, &namedValue);

    EXPECT_TRUE(result);

    auto orientationValue = namedValue.Value("orientation");
    auto scaleValue = namedValue.Value("scale"); 
    auto positionValue = namedValue.Value("position"); 

    EXPECT_EQ(orientationValue.GetNamedValue("x"),  "3.100000");
    EXPECT_EQ(orientationValue.GetNamedValue("y"), "45.340000");

    EXPECT_EQ(scaleValue.GetNamedValue("x"), "56.000000");
    EXPECT_EQ(scaleValue.GetNamedValue("y"), "12.000004");

    EXPECT_EQ(positionValue.GetNamedValue("x"), "12.000100");
    EXPECT_EQ(positionValue.GetNamedValue("y"), "13.343400");
}
//-----------------------------------------------------------------
// Name: DeserializeTransformComponent
// Desc:
//-----------------------------------------------------------------
TEST(SerializationTest, DeserializeTransformComponent)
{
    TransformComponent transformComponent;
    
    NamedValue namedValue; 

    // namedValue.Add("id", "15");
    // namedValue.Add("entityId", "199"); 
    namedValue.Add("position", Vector2D(12.0f, 13.0f)); 
    namedValue.Add("scale", Vector2D(1.0f, 4.32f)); 
    namedValue.Add("orientation", Vector2D(34.0045f, 3.3443f)); 

    auto result = Component::Deserialize(namedValue, &transformComponent); 

    EXPECT_TRUE(result);

    EXPECT_EQ(transformComponent.id, 0);
    EXPECT_EQ(transformComponent.entityId, 0);
    EXPECT_EQ(transformComponent.position, Vector2D(12.0f, 13.0f));
    EXPECT_EQ(transformComponent.orientation, Vector2D(34.0045f, 3.3443f));
    EXPECT_EQ(transformComponent.scale, Vector2D(1.0f, 4.32f)); 
}
//-----------------------------------------------------------------
// Name: DeserializeXmlToComponent
// Desc:
//-----------------------------------------------------------------
TEST(SerializationTest, DeserializeXmlToComponent)
{
    TransformComponent transformComponent; 
    XmlDocument xml("xml/transformComponent.xml"); 

    auto namedValues = SerialUtility::XmlDocumentToNamedValues(xml); 
    auto namedValue = namedValues.front(); 

    EXPECT_TRUE(Component::Deserialize(namedValue, &transformComponent));
    EXPECT_EQ(transformComponent.position, Vector2D(43.21f, 12.34f));
    EXPECT_EQ(transformComponent.scale, Vector2D(34.56f, 56.78f));
    EXPECT_EQ(transformComponent.orientation, Vector2D(9.87f, 76.45));
}
//-----------------------------------------------------------------
// Name: FilesInDirectory
// Desc:
//-----------------------------------------------------------------
TEST(SerializationTest, FilesInDirectory)
{
    auto files = FileUtility::DirectoryContents("./"); 

    for (auto file : files) {
        cout << file << endl; 
    }
}

