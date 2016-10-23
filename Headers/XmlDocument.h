#ifndef XML_DOCUMENT_H
#define XML_DOCUMENT_H

#include "Utility/ProcessUtility.h"

#include <list>
#include <stack>
#include <vector>
#include <exception>
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std; 

// XmlTag
struct XmlTag
{
	weak_ptr<XmlTag> parent;
	list<XmlTag> children; 

	string name; 

	unordered_map<string, string> attributes; 

	bool closeTag;

	XmlTag() {}

	XmlTag(const XmlTag& xmlTag) 
	{
		this->parent = xmlTag.parent; 

		for(auto child : xmlTag.children) {
			this->children.push_back(child); 
		}

		this->name = xmlTag.name; 
		this->attributes = xmlTag.attributes; 
		this->closeTag = xmlTag.closeTag;  
	}
};

//
class XmlDocument
{	

	list<XmlTag> tags; 

public:

	//-----------------------------------------------------------------------
	// Name: Filter
	// Desc: removes filterChar from specified string
	//-----------------------------------------------------------------------
	static string Filter(const string& str, char filterChar)
	{
		string result;

		for(auto c : str) {
			if (c != filterChar) {
				result += c; 
			}
		}

		return result; 
	}

	//-----------------------------------------------------------------------
	// Name: Split
	// Desc: split a string based on given vector of chars, splitting chars
	//       are included in final string so:
	//  "<a><b></b></a>" split by '<' and '>' becomes {"<a>", "<b>", "</b>", "</a>"}
	//-----------------------------------------------------------------------
	static list<string> Split(const string& text, const vector<char>& splitChars)
	{
		list<string> strings; 
		string currString;

		for (auto i = 0; i < text.length(); i++) {
			
			if (currString.empty() && text[i] != ' ') {
				currString += text[i];				
			
			} else if (!currString.empty()) {

				currString += text[i];
			}

		
			auto result = find(splitChars.begin(), splitChars.end(), text[i]);

			if (result != splitChars.end()) {

				if (currString.size() > 1) {
						
					strings.push_back(currString); 
					currString.clear(); 					
				}
			}
		}

		return strings; 
	}

	//--------------------------------------------------------------
	// Name: Split
	// Desc: split a string into a list of strings by given character
	//       split character is not included in final string.
	//--------------------------------------------------------------
	static list<string> Split(const string& text, char splitChar)
	{
		list<string> splitStrings; 
		string currString; 

		for (auto i = 0; i < text.length(); i++) {
			
			if (text[i] == splitChar) {
				if (!currString.empty()) {
					splitStrings.push_back(currString);
					currString.clear(); 
				}

			} else {

				currString += text[i]; 

				if (i == text.length() - 1) {
					splitStrings.push_back(currString); 
				}
			}
		}

		return splitStrings;
	}

	//-------------------------------------------------------------
	// Name: ExtractValueStrings
	// Desc: example 
	//       name="Name" a="b" c="abc" -> "Name", "b", "abc"
	// 
	//-------------------------------------------------------------
	static list<string> ExtractValueStrings(const string& text, char separator = '\"')
	{
		list<string> values; 
		string currentValue; 

		bool value = false; 

		for (auto c : text) {

			if (c == separator && currentValue.size() > 0) {
				values.push_back(currentValue); 
				currentValue.clear(); 
				value = false; 
			
			} else if (value == false && c == separator) {
				value = true;
			} else if (value == true) {

				currentValue += c; 
			}
		}

		return values; 
	}
	//-------------------------------------------------------------
	// Name: ExtractNameStrings 
	// Desc: extract names from text
	//-------------------------------------------------------------
	static list<string> ExtractNameStrings(const string& text, char separator = '\"')
	{
		list<string> names; 
		string currentName; 

		bool name = true; 

		for(auto c : text) {

			// if we've found a separator or we're inside a sep
			if ((c == separator && name == true)) {

				if (!currentName.empty()) {
					names.push_back(currentName); 
					currentName.clear(); 
				}

				name = false; 
				continue; 
			} 

			// end of a name
			if (c == separator) {
				name = true;
				continue;  
			}

			// ignore equals and spaces
			if (c != '=' && c != ' ' && name) {
				currentName += c; 	
			}	
		}

		return names; 
	}
	//-------------------------------------------------------------
	// Name: Trim 
	// Desc: Removes all leading and trailing occurences of trimChar
	//-------------------------------------------------------------
	static string Trim(const string& str, char trimChar)
	{
		string trimmedString = ""; 

		auto firstNotOf = str.find_first_not_of(trimChar); 
		auto lastNotOf = str.find_last_not_of(trimChar); 

		trimmedString = str.substr(firstNotOf, lastNotOf - firstNotOf + 1); 
		return trimmedString; 
	}	

	//--------------------------------------------------------------
	// Name: ToXmlTag
	// Desc: Converts a string like < .... > to an xml tag
	//       assumes that there may be whitespace and the beginning 
	//       and end of a string.
	//--------------------------------------------------------------
	static XmlTag ToXmlTag(const string& text) 
	{
		// remove leading and trailing spaces
		auto token = Trim(text, ' '); 
		XmlTag tag; 
		string innerText; 

		if (TokenHasChildren(token)) {
			innerText = token.substr(1, token.length() - 2);
			tag.closeTag = false;
			
		} else {

			innerText = token.substr(1, token.length() - 3); 
			tag.closeTag = true;
		}

		auto strings = Split(innerText, ' '); 

		if (strings.size() > 0) {
			tag.name = XmlDocument::Filter(strings.front(), '/'); 

		} else {
			
			// return empty tag
			return tag; 
		}

		if (!IsClosingToken(token)) {

			auto innerTextNameRemoved = innerText.substr(tag.name.size(), innerText.size() - 1);

			auto names = ExtractNameStrings(innerTextNameRemoved);
			auto values = ExtractValueStrings(innerTextNameRemoved); 

			if (names.size() == values.size()) {
				
				//
				auto valueIter = values.begin(); 
				for(auto nameIter = names.begin(); nameIter != names.end() && valueIter != values.end(); nameIter++) {

					tag.attributes[*nameIter] = *valueIter; 
					valueIter++; 
				}
			}

		} else {

			tag.closeTag = true; 
		}

		return tag; 
	}

	//---------------------------------------------------------------
	// Name: IsClosingToken
	// Desc:
	//---------------------------------------------------------------
	static bool IsClosingToken(const string& tag) 
	{
		if (tag.substr(0, 2) == "</") {
			return true; 
		}

		return false; 
	}

	//---------------------------------------------------------------
	// Name: TokenHasChildren
	// Desc:
	//---------------------------------------------------------------
	static bool TokenHasChildren(const string& token) 
	{
		if (token.substr(token.length() - 2, token.length() - 1) == "/>") {
			return false;
		} 

		return true; 
	}

	//---------------------------------------------------------------
	// Name: ToDocument
	// Desc:
	//---------------------------------------------------------------
	static list<XmlTag> ToDocument(list<string> tokens) 
	{
		// this is a list of all the top level tags
		list<XmlTag> tags;
		stack<XmlTag> tagStack; 

		for(auto token : tokens) {

			auto tag = ToXmlTag(token); 

			// if not a closing tag then push onto the stack
			if (!tag.closeTag || tagStack.empty()) {
				tagStack.push(tag); 	
			
			} else {

				auto& topTag = tagStack.top(); 

				if (topTag.name == tag.name) {
					
					if (tagStack.size() == 1) {
						tags.push_back(topTag); 
						tagStack.pop();	
					
					} else {

						auto topTagCopy = tagStack.top();
						tagStack.pop(); 

						auto& nextTop = tagStack.top();
						nextTop.children.push_back(topTagCopy);
					}
				} else {

					topTag.children.push_back(tag);
				}
			}
		}

		return tags; 
	}

	//---------------------------------------------------------------
	// Name: XmlDocument
	// Desc:
	//---------------------------------------------------------------
	XmlDocument(const string& file) 
	{
		// std::ifstream fileStream;
		// fileStream.open(file, std::fstream::in);
		
		FILE* fp = nullptr;
		fp = fopen(file.c_str(), "r");

		if (fp != nullptr) {

			string fileContent; 
			string line; 

			while (true) {

				auto c = fgetc(fp);

				if (c != EOF) {
					fileContent += c; 	
				
				} else {

					break; 
				}
			}

			// remove all \n and \t
			replace(fileContent.begin(), fileContent.end(), '\n', ' ');
			replace(fileContent.begin(), fileContent.end(), '\t', ' ');

			vector<char> splitChars = {'<','>'};
			auto tokens = XmlDocument::Split(fileContent, splitChars); 
			this->tags = XmlDocument::ToDocument(tokens); 	
		}

		fclose(fp); 
	}

	//-----------------------------------------------------------------
	// Name: Tags
	// Desc:
	//-----------------------------------------------------------------
	list<XmlTag> Tags() const
	{
		return this->tags; 
	}
}; 

#endif // XML_DOCUMENT_H
