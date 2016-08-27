// XmlTest.cpp
#include "XmlDocument.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>

using namespace std; 

//----------------------------------------------------------------
// Name: StringSplit
// Desc:
//----------------------------------------------------------------
TEST(XmlTests, StringSplit)
{
	XmlDocument xmlDocument(""); 

	auto xml = "<a><b><c></c></b></a>    ";
	vector<char> splitChars = {'<', '>'};

	auto split = xmlDocument.Split(xml, splitChars); 
	list<string> expectedResults = {"<a>","<b>","<c>","</c>","</b>","</a>"}; 

	EXPECT_EQ(expectedResults, split);
}
//----------------------------------------------------------------
// Name: CharSplit
// Desc:
//----------------------------------------------------------------
TEST(XmlTests, CharSplit)
{
	XmlDocument xmlDocument(""); 

	auto xml = "a = \"10.0f\" b = \"10.0f\"    ";
	auto split = xmlDocument.Split(xml, ' '); 

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


