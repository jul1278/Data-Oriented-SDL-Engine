#ifndef XML_DOCUMENT_H
#define XML_DOCUMENT_H

#include <exception>
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>
#include <fstream>


using namespace std; 

class XmlTag
{
private:

	unordered_map<string, string> nameValuePairs; 
	list<XmlTag> children; 
	shared_ptr<XmlTag> parent;

public:

	XmlTag() {}

	XmlTag(shared_ptr<XmlTag> parent)
	{
		this->parent = parent; 
	}

	list<XmlTag>& Children()
	{
		return this->children; 
	}

	void AddChild(const XmlTag& xmlTag)
	{
		this->children.push_back(xmlTag); 
	}

	shared_ptr<XmlTag> Parent() const
	{
		return this->parent; 
	}

	bool HasParent() const
	{
		return this->parent.operator* == nullptr; 
	}

	bool NameExists(const string& name)
	{
		return (this->nameValuePairs.find(name) != this->nameValuePairs.end());

	}

	bool TryGetValueAs(const string& name, string* value);
	bool TryGetValueAs(const string& name, int* value);
	bool TryGetValueAs(const string& name, float* value);

};

class XmlDocument : public XmlTag
{
private:

public:

	XmlDocument(string fileName)
	{
		std::ifstream file(fileName);

		
	}
};

#endif // XML_DOCUMENT_H