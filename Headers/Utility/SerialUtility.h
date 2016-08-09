#ifndef SERIAL_UTILITY_H
#define SERIAL_UTILITY_H

#include "Utility/MathUtility.h"

#include <string>
#include <list>

using namespace std; 

namespace SerialUtility
{
    struct NamedValue
    {
        string value;
        map<string, NamedValue> values; 

        NamedValue(string value = "") : value(value) 
        {
        }

        void Add(string value) 
        {
            this->value = value; 
        }

        void Add(string name, string value) 
        {
            this->values[name].Add(value);
        }

        void Add(string name, Vector2D value) 
        {
            this->values[name].Add("x", to_string(value.x));
            this->values[name].Add("y", to_string(value.y)); 
        }

        string GetNamedValue(const string& name) const
        {
            const auto& namedValue = this->values.at(name); 
            return namedValue.value; 
        }

        NamedValue Value(const string& name) const
        {
            return this->values.at(name); 
        } 
    };

    //-----------------------------------------------------
    // Name: to_string
    // Desc:
    //-----------------------------------------------------
    string to_string(Vector2D vector) 
    {
        auto x = std::to_string(vector.x);
        auto y = std::to_string(vector.y); 

        return string(x + ", " + y); 
    }
}

#endif // SERIAL_UTILITY_H