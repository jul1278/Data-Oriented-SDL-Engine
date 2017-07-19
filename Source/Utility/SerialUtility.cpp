// SerialUtility.cpp
#include "Utility/SerialUtility.h"

namespace SerialUtility 
{
	//-------------------------------------------------------------------
	// Name: to_string
	// Desc:
	//-------------------------------------------------------------------
	std::string to_string(Vector2D vector)
	{
	    auto x = std::to_string(vector.x);
	    auto y = std::to_string(vector.y); 

	    return string(x + ", " + y); 
	}

	//--------------------------------------------------------------------
	// Name: XmlDocumentToNamedValues
	// Desc:
	//--------------------------------------------------------------------
	std::list<NamedValue> XmlDocumentToNamedValues(const XmlDocument& xmlDocument)
	{
		std::list<NamedValue> namedValues;

	    for(auto xmlTag : xmlDocument.Tags()) {
	        namedValues.push_back(NamedValue(xmlTag)); 
	    }

	    return namedValues; 
	}	
}
