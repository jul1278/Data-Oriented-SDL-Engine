#ifndef COMPONENT_H
#define COMPONENT_H

#include "Components/BaseComponent.h"
#include "Components/TransformComponent.h"
#include "Utility/SerialUtility.h"
#include "Game/ParseContext.h"

#include <map>
#include <exception>
#include <sstream>
#include <cstdlib>

using namespace std;
using namespace SerialUtility;

namespace Component 
{
    enum ComponentType
    {
        None,
        BaseComponent,
        TransformComponent,
        GraphicsComponent
    };

    //-------------------------------------------------------------------------------------
    // Name: Serialize 
    // Desc: serialize BaseComponent
    //-------------------------------------------------------------------------------------
    bool Serialize(const struct BaseComponent& component, NamedValue* nameValue) 
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
    bool Deserialize(const struct NamedValue& nameValuePairs, struct BaseComponent* component)
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
    bool Serialize(const struct TransformComponent& transformComponent, NamedValue* namedValue)
    {
        if (namedValue != nullptr) {
            if (Serialize(dynamic_cast<const struct BaseComponent&>(transformComponent), namedValue)) {
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
    bool Deserialize(const NamedValue& namedValue, struct TransformComponent* transformComponent)
    {
        if (transformComponent != nullptr) {
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

        return false; 
    }
    //-------------------------------------------------------------------------------------
    // Name: Serialize 
    // Desc: Serialize GraphicsComponent
    //-------------------------------------------------------------------------------------
    bool Serialize(const struct GraphicsComponent& graphicsComponent, NamedValue* namedValue)
    {
        // TODO: implement
        return false; 
    }
    //-------------------------------------------------------------------------------------
    // Name: Deserialize 
    // Desc: Deserialize GraphicsComponent
    //-------------------------------------------------------------------------------------
    bool Deserialize(const NamedValue& namedValue, struct GraphicsComponent* graphicsComponent, ParseContext& parseContext)
    {
        if (graphicsComponent != nullptr) {

            auto transformComponentName = namedValue.GetNamedValue("name");
            auto transformComponentId = parseContext.NamedId(transformComponentName); 

            graphicsComponent->transformComponentId = transformComponentId; 

            if (namedValue.HasValue("path")) {
                auto path = namedValue.GetNamedValue("path"); 
                graphicsComponent->resourceId = parseContext.ResourceIdFromPath(path);
            
            } else if (namedValue.HasValue("name")) {

                auto name = namedValue.GetNamedValue("name");
                graphicsComponent->resourceId = parseContext.ResourceIdFromName(name, namedValue); 
            }
        }

        return false; 
    }
}

#endif // COMPONENT_H