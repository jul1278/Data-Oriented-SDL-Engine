#ifndef XML_DOCUMENT_H
#define XML_DOCUMENT_H

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
};

//
class XmlDocument
{	
public:

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
			
			currString += text[i];
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
	// Name: Trim 
	// Desc: Removes all leading and trailing occurences of trimChar
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
			tag.name = strings.front(); 
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
		list<XmlTag> tags; 
		stack<XmlTag> tagStack; 

		for(auto token : tokens) {

			if (tagStack.empty()) {
				tagStack.push(ToXmlTag(token));
			
			} else {

				auto tag = ToXmlTag(token); 

				if (tag.closeTag && tagStack.size() > 1) {
					tagStack.pop(); 

				} else if (tag.closeTag && tagStack.size() == 1) {
					auto tag = tagStack.top(); 
					tags.push_back(tag);

				} else {

					auto lastTag = tagStack.top(); 
					lastTag.children.push_back(tag);
				}
			}
		}
	}

	//---------------------------------------------------------------
	// Name: XmlDocument
	// Desc:
	//---------------------------------------------------------------
	XmlDocument(const string& file) 
	{
		// ifstream fileStream(file); 
		// stringstream buffer; 
		// buffer << fileStream; 

		// auto fileText = buffer.str(); 

		// vector<char> splitChars = {'<', '>'};

		// auto tokens = this.Split(); 
	}


}; 

#endif // XML_DOCUMENT_H