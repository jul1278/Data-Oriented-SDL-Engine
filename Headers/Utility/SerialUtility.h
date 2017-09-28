#ifndef SERIAL_UTILITY_H
#define SERIAL_UTILITY_H

#include "Utility/MathUtility.h"
#include "XmlDocument.h"

#include <map>
#include <string>
#include <algorithm>
#include <list>

namespace SerialUtility
{
    class NamedValue
    {
        std::string name;
		std::list<NamedValue> namedValues;
		std::map<string, string> attributes;

	public:
        //-------------------------------------------------------------------
        // Name: Add
        // Desc:
        //-------------------------------------------------------------------
        void AddAttribute(const string& name, const string& value) 
        {
            this->attributes[name] = value;
        }

        //-------------------------------------------------------------------
        // Name: Add
        // Desc:
        //-------------------------------------------------------------------
        void AddNamedValue(const string& name, const Vector2D& value) 
        {
			NamedValue namedValue(name); 
			namedValue.AddAttribute("x", to_string(value.x));
			namedValue.AddAttribute("y", to_string(value.y));

			this->namedValues.push_back(namedValue); 
        }

		//-------------------------------------------------------------------
		// Name: Add
		// Desc:
		//-------------------------------------------------------------------
		void AddNamedValue(const NamedValue& namedValue)
		{
			this->namedValues.push_back(namedValue);
		}
		//-------------------------------------------------------------------
		// Name: TryGetAttribute
		// Desc:
		//-------------------------------------------------------------------
		bool TryGetNamedValue(const std::string& name, NamedValue& namedValue) const
		{
			auto result = std::find_if(this->namedValues.begin(), this->namedValues.end(), 
			[&name] (const NamedValue& nv)
			{
				return nv.Name() == name;
			});

			if (result != this->namedValues.end()) {
				namedValue = *result;
				return true;
			} 

			return false; 
		}

		//-------------------------------------------------------------------
		// Name: TryGetAttribute
		// Desc:
		//-------------------------------------------------------------------
		bool TryGetNamedVectorValue(const std::string& name, Vector2D& vector) const
		{
			NamedValue nameValue("default");

			if (this->TryGetNamedValue(name, nameValue)) {
				float x, y;
				if (nameValue.TryGetAttribute("x", x)) {
					vector.x = x;
				} else {
					vector.x = 0.0; 
				}

				if (nameValue.TryGetAttribute("y", y)) {
					vector.y = y;
				} else {
					vector.y = 0.0f; 
				}

				return true;
			}

			return false; 
		}

		//-------------------------------------------------------------------
		// Name: TryGetAttribute
		// Desc:
		//-------------------------------------------------------------------
		bool TryGetAttribute(const std::string& name, int& attribute) const
		{
			std::string result; 
			if (this->TryGetAttribute(name, result)) {
				try {
					attribute = std::atoi(result.c_str());
				} catch (std::exception) {
					return false; 
				}
				
				return true; 
			}

			return false; 
		}

		//-------------------------------------------------------------------
		// Name: TryGetAttribute
		// Desc:
		//-------------------------------------------------------------------
		bool TryGetAttribute(const std::string& name, std::string& attribute) const
		{
			if (this->attributes.find(name) != this->attributes.end()) {
				attribute = this->attributes.at(name); 
				return true;
			}

			return false; 
		}

		//-------------------------------------------------------------------
		// Name: TryGetAttribute
		// Desc:
		//-------------------------------------------------------------------
		bool TryGetAttribute(const std::string& name, float& attribute) const
		{
			std::string result;
			if (this->TryGetAttribute(name, result)) {
				try {
					attribute = (float) std::atof(result.c_str());
				}
				catch (std::exception) {
					return false;
				}

				return true;
			}

			return false;
		}

        //-------------------------------------------------------------------
        // Name: Name
        // Desc:
        //-------------------------------------------------------------------
        string Name() const
        {
            return this->name; 
        }

        //-------------------------------------------------------------------
        // Name: NamedValue
        // Desc:
        //-------------------------------------------------------------------
        NamedValue(string name) : name(name) {}

        //-------------------------------------------------------------------
        // Name: NamedValue
        // Desc:
        //-------------------------------------------------------------------
        NamedValue(const XmlTag& xmlTag)
        {
            this->name = xmlTag.name; 

            for(auto pair : xmlTag.attributes) {
                auto attrName = pair.first; 

                auto xmlValue = pair.second; 
				this->attributes[attrName] = xmlValue; 
            }

            for(auto child : xmlTag.children) {
                auto childName = child.name; 
				this->namedValues.push_back(NamedValue(child)); 
            }
        }
    };

    //-------------------------------------------------------------------
    // Name: to_string
    // Desc:
    //-------------------------------------------------------------------
    string to_string(Vector2D vector);

    //--------------------------------------------------------------------
    // Name: XmlDocumentToNamedValues
    // Desc:
    //--------------------------------------------------------------------
    list<NamedValue> XmlDocumentToNamedValues(const XmlDocument& xmlDocument);
}

#endif // SERIAL_UTILITY_H