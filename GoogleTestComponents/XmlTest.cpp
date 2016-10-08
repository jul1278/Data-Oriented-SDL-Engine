// XmlTest.cpp
#include "XmlDocument.h"
#include "Utility/SerialUtility.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>

using namespace std; 

void PrintTags(list<XmlTag> tags, int depth) 
{
	for(auto tag : tags) {

		// print our indents
		for (auto i = 0; i < depth; i++) {
			cout << "  "; 
		}

		cout << tag.name << " : ";

		for(auto attr : tag.attributes) {
			auto key = attr.first; 

			cout << key << " " ; 
		}

		cout << endl; 

		if (!tag.children.empty()) {
			PrintTags(tag.children, depth + 1); 
		} 
	} 
}

//----------------------------------------------------------------
// Name: StringSplit
// Desc:
//----------------------------------------------------------------
TEST(XmlTests, StringSplit)
{
	auto xml = "<a><b><c></c></b></a>    ";
	vector<char> splitChars = {'<', '>'};

	auto split = XmlDocument::Split(xml, splitChars); 
	list<string> expectedResults = {"<a>","<b>","<c>","</c>","</b>","</a>"}; 

	EXPECT_EQ(expectedResults, split);
}
//----------------------------------------------------------------
// Name: CharSplit
// Desc:
//----------------------------------------------------------------
TEST(XmlTests, CharSplit)
{
	auto xml = "a = \"10.0f\" b = \"10.0f\"    ";
	auto split = XmlDocument::Split(xml, ' '); 

	list<string> expectedResults = {"a", "=", "\"10.0f\"", "b", "=", "\"10.0f\""}; 

	EXPECT_EQ(expectedResults, split);
}

//----------------------------------------------------------------
// Name: Trim
// Desc:
//----------------------------------------------------------------
TEST(XmlTests, CharTrim) 
{
	auto str1 = "   hey   "; 
	auto str2 = "hey";
	auto str3 = "   hey"; 

	auto expected = "hey"; 

	auto result1 = XmlDocument::Trim(str1, ' '); 
	auto result2 = XmlDocument::Trim(str2, ' '); 
	auto result3 = XmlDocument::Trim(str3, ' '); 

	EXPECT_EQ(result1, expected); 
	EXPECT_EQ(result2, expected); 
	EXPECT_EQ(result3, expected); 
}
//----------------------------------------------------------------
// Name: ToXmlTag
// Desc:
//----------------------------------------------------------------
TEST(XmlTests, StringToXmlTag)
{
	auto closedTag = XmlDocument::ToXmlTag("<TransformComponent name=\"component\" x=\"50.0f\" y=\"20.0f\"/>");
	auto tag = XmlDocument::ToXmlTag("<TransformComponent name = \"component\" x = \"50.0f\" y = \"20.0f\">");

	ASSERT_EQ(closedTag.attributes.size(), 3); 
	ASSERT_EQ(tag.attributes.size(), 3);

	EXPECT_EQ(closedTag.name, "TransformComponent"); 
	EXPECT_EQ(tag.name, "TransformComponent"); 

	ASSERT_NE(closedTag.attributes.find("name"), closedTag.attributes.end()); 
	EXPECT_EQ(closedTag.attributes["name"], "component"); 

	ASSERT_NE(closedTag.attributes.find("x"), closedTag.attributes.end()); 
	EXPECT_EQ(closedTag.attributes["x"], "50.0f"); 

	ASSERT_NE(closedTag.attributes.find("y"), closedTag.attributes.end());
	EXPECT_EQ(closedTag.attributes["y"], "20.0f"); 
}
//----------------------------------------------------------------
// Name: ExtractValueStrings
// Desc:
//----------------------------------------------------------------
TEST(XmlTests, ExtractValueStrings) 
{
	auto values = XmlDocument::ExtractValueStrings("  name=\"component\" x=\"50.0f\" y=\"25.5f\""); 

	list<string> expected = { "component", "50.0f", "25.5f" }; 

	EXPECT_EQ(values, expected); 
}
//----------------------------------------------------------------
// Name: ExtractNameStrings
// Desc:
//----------------------------------------------------------------
TEST(XmlTests, ExtractNameStrings) 
{
	auto names1 = XmlDocument::ExtractNameStrings("  name=\"component\" x=\"50.0f\" y=\"25.5f\""); 
	auto names2 = XmlDocument::ExtractNameStrings("  name = \"component\" x = \"50.0f\" y = \"25.5f\" z = \"123.0f\""); 
	auto names3 = XmlDocument::ExtractNameStrings("  name=\"component"); 

	list<string> expected1 = { "name", "x", "y" }; 
	list<string> expected2 = { "name", "x", "y", "z" };
	list<string> expected3 = { "name" };

	EXPECT_EQ(names1, expected1); 
	EXPECT_EQ(names2, expected2); 
	EXPECT_EQ(names3, expected3); 
}
//----------------------------------------------------------------
// Name: XmlReadDocument
// Desc:
//----------------------------------------------------------------
TEST(XmlTests, XmlReadSimpleDocument)
{	
	//auto xmlDoc = XmlDocument("/Users/P/Documents/Projects/SimpleComponents/Build/test1.xml"); 
	auto xmlDoc = XmlDocument("test1.xml"); 
	auto tags = xmlDoc.Tags(); 

	auto tag = tags.front(); 

	//EXPECT_EQ(tags.size(), 1); 
	//EXPECT_EQ(tag.name, "GraphicsComponent"); 
	//EXPECT_EQ(tag.children.size(), 1); 
	cout << "Printing xml structure..." << endl;
	PrintTags(tags, 0);
}
//------------------------------------------------------------------
// Name: 
// Desc:
//------------------------------------------------------------------
TEST(XmlTests, XmlToNamedValues)
{
	auto xmlDoc = XmlDocument("test1.xml"); 
	auto namedValues = SerialUtility::XmlDocumentToNamedValues(xmlDoc);
}




