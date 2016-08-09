#ifndef COMPONENT_H
#define COMPONENT_H

#include "Components/BaseComponent.h"
#include "Components/TransformComponent.h"
#include "Utility/SerialUtility.h"

#include <map>
#include <exception>

using namespace std;
using namespace SerialUtility;

namespace Component 
{
    //-------------------------------------------------------------------------------------
    // Name: Serialize 
    // Desc: serialize BaseComponent
    //-------------------------------------------------------------------------------------
    bool Serialize(const BaseComponent& component, NamedValue* nameValue) 
    {
        if (nameValue != nullptr) {
            nameValue->Add("id", to_string(component.id));
            nameValue->Add("entityId", to_string(component.entityId)); 

            return true; 
        }

        return false; 
    }
    //-------------------------------------------------------------------------------------
    // Name: Deserialize 
    // Desc: Deserialize BaseComponent
    //-------------------------------------------------------------------------------------
    bool Deserialize(const NamedValue& nameValuePairs, BaseComponent* component)
    {
        if (component != nullptr) {
            component->id = stoi(nameValuePairs.GetNamedValue("id"));
            component->entityId = stoi(nameValuePairs.GetNamedValue("entityId")); 

            return true;
        }

        return false; 
    }
    //-------------------------------------------------------------------------------------
    // Name: Serialize 
    // Desc: Serialize TransformComponent
    //-------------------------------------------------------------------------------------
    bool Serialize(const TransformComponent& transformComponent, NamedValue* namedValue)
    {
        if (namedValue != nullptr) {
            if (Serialize(dynamic_cast<const BaseComponent&>(transformComponent), namedValue)) {
                namedValue->Add("position", transformComponent.position);
                namedValue->Add("orientation", transformComponent.orientation);
                namedValue->Add("scale", transformComponent.scale);

                return true;
            }    
        }        

        return false; 
    }
    //-------------------------------------------------------------------------------------
    // Name: Deserialize 
    // Desc: Deserialize TransformComponent
    //-------------------------------------------------------------------------------------
    bool Deserialize(const NamedValue& namedValue, TransformComponent* transformComponent)
    {
        if (transformComponent != nullptr) {
            if (Deserialize(namedValue, dynamic_cast<BaseComponent*>(transformComponent))) {
                auto positionValue = namedValue.Value("position");
                auto orientationValue = namedValue.Value("orientation"); 
                auto scaleValue = namedValue.Value("scale");

                transformComponent->position.x = stof(positionValue.GetNamedValue("x"));
                transformComponent->position.y = stof(positionValue.GetNamedValue("y"));

                transformComponent->orientation.x = stof(orientationValue.GetNamedValue("x"));
                transformComponent->orientation.y = stof(orientationValue.GetNamedValue("y"));

                transformComponent->scale.x = stof(scaleValue.GetNamedValue("x"));
                transformComponent->scale.y = stof(scaleValue.GetNamedValue("y"));

                return true;
            }
        }

        return false; 
    }
}

#endif // COMPONENT_H