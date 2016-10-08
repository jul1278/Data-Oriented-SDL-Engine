#ifndef SERIAL_UTILITY_H
#define SERIAL_UTILITY_H

#include "Utility/MathUtility.h"
#include "XmlDocument.h"

#include <map>
#include <string>
#include <algorithm>
#include <list>

using namespace std; 

namespace SerialUtility
{
    struct NamedValue
    {
        string value;
        map<string, NamedValue> values; 

        //-------------------------------------------------------------------
        // Name: Add
        // Desc:
        //-------------------------------------------------------------------
        void Add(string value) 
        {
            this->value = value; 
        }

        //-------------------------------------------------------------------
        // Name: Add
        // Desc:
        //-------------------------------------------------------------------
        void Add(string name, string value) 
        {
            this->values[name].Add(value);
        }

        //-------------------------------------------------------------------
        // Name: Add
        // Desc:
        //-------------------------------------------------------------------
        void Add(string name, Vector2D value) 
        {
            this->values[name].Add("x", to_string(value.x));
            this->values[name].Add("y", to_string(value.y)); 
        }

        //-------------------------------------------------------------------
        // Name: Name
        // Desc:
        //-------------------------------------------------------------------
        string Named() const
        {
            return this->value; 
        }

        //-------------------------------------------------------------------
        // Name: GetNamedValue
        // Desc:
        //-------------------------------------------------------------------
        string GetNamedValue(const string& name) const
        {
            const auto& namedValue = this->values.at(name); 
            return namedValue.value; 
        }

        //-------------------------------------------------------------------
        // Name: NamedValue
        // Desc:
        //-------------------------------------------------------------------
        NamedValue Value(const string& name) const
        {
            return this->values.at(name); 
        } 

        //-------------------------------------------------------------------
        // Name: HasValue
        // Desc:
        //-------------------------------------------------------------------
        bool HasValue(const string& name) const
        {
            return this->values.find(name) != this->values.end();
        }

        //-------------------------------------------------------------------
        // Name: NamedValue
        // Desc:
        //-------------------------------------------------------------------
        NamedValue(string value = "") : value(value) {}

        //-------------------------------------------------------------------
        // Name: NamedValue
        // Desc:
        //-------------------------------------------------------------------
        NamedValue(const XmlTag& xmlTag)
        {
            this->value = xmlTag.name; 

            // name to lowercase
            std::transform(this->value.begin(), this->value.end(), this->value.begin(), ::tolower); 

            for(auto pair : xmlTag.attributes) {

                auto name = pair.first; 

                // name to lowercase
                std::transform(name.begin(), name.end(), name.begin(), ::tolower); 

                auto xmlValue = pair.second; 
                values[name] = NamedValue(xmlValue); 
            }

            for(auto child : xmlTag.children) {

                auto name = child.name; 
                std::transform(name.begin(), name.end(), name.begin(), ::tolower); 

                values[name] = NamedValue(child); 
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