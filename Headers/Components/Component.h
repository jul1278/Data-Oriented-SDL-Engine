#ifndef COMPONENT_H
#define COMPONENT_H

#include "Components/BaseComponent.h"
#include "Components/TransformComponent.h"
#include "Utility/SerialUtility.h"
#include "Game/ParseContext.h"

#include <map>
#include <string>
#include <exception>
#include <sstream>
#include <cstdlib>

namespace Component 
{
    //-------------------------------------------------------------------------------------
    // Name: Serialize 
    // Desc: serialize BaseComponent
    //-------------------------------------------------------------------------------------
    bool Serialize(const struct BaseComponent& component, SerialUtility::NamedValue& nameValue) 
    {
        nameValue.AddAttribute("id", to_string(component.id));
        nameValue.AddAttribute("entityId", to_string(component.entityId));

        return true; 
    }

    //-------------------------------------------------------------------------------------
    // Name: Serialize 
    // Desc: Serialize TransformComponent
    //-------------------------------------------------------------------------------------
    bool Serialize(const struct TransformComponent& transformComponent, SerialUtility::NamedValue& namedValue)
    {
        if (Serialize(dynamic_cast<const struct BaseComponent&>(transformComponent), namedValue)) {
            namedValue.AddNamedValue("Position", transformComponent.position);
            namedValue.AddNamedValue("Orientation", transformComponent.orientation);
            namedValue.AddNamedValue("Scale", transformComponent.scale);

            return true;
        }    

        return false; 
    }

	//-------------------------------------------------------------------------------------
	// Name: Serialize 
	// Desc: Serialize GraphicsComponent
	//-------------------------------------------------------------------------------------
	bool Serialize(const struct GraphicsComponent& graphicsComponent, SerialUtility::NamedValue& namedValue)
	{
		// TODO: implement
		return false;
	}
	
	//-------------------------------------------------------------------------------------
	// Name: Deserialize 
	// Desc: Deserialize BaseComponent
	//-------------------------------------------------------------------------------------
	template<typename T>
	T* Deserialize(const struct SerialUtility::NamedValue& namedValue, ParseContext& parseContext)
	{
		// check if namedValue.name is a component
		if (IsComponent(namedValue.Name())) {

			auto name = namedValue.Name();

			if (name == "BaseComponent") {
				return (T*) Component::DeserializeAs<BaseComponent>(namedValue, parseContext);
			}

			if (name == "TransformComponent") {
				return (T*) Component::DeserializeAs<TransformComponent>(namedValue, parseContext);
			}

			//if (name == "GraphicsComponent") {

			//	GraphicsComponent* graphicsComponent = static_cast<GraphicsComponent*>(component);
			//	return Component::Deserialize(namedValue, parseContext);
			//}

		} else {
			return nullptr;
		}
	}

	//-------------------------------------------------------------------------------------
	// Name: Deserialize 
	// Desc: Deserialize BaseComponent
	//-------------------------------------------------------------------------------------
	template<typename T>
	T* DeserializeAs(const struct SerialUtility::NamedValue& namedValue, ParseContext& parseContext);

	//-------------------------------------------------------------------------------------
	// Name: Deserialize 
	// Desc: Deserialize BaseComponent
	//-------------------------------------------------------------------------------------
	template<>
	BaseComponent* DeserializeAs<BaseComponent>(const struct SerialUtility::NamedValue& nameValue, ParseContext& parseContext)
	{
		BaseComponent* baseComponent = parseContext.NewComponent<BaseComponent>();

		// check if we're even trying to get an entityId
		int entityId;

		if (baseComponent != nullptr) {

			// check if the entityId is specified
			if (parseContext.ParentEntityId() != 0) {
				baseComponent->entityId = parseContext.ParentEntityId();
			
			} else if (nameValue.TryGetAttribute("entityId", entityId)) {

				baseComponent->entityId = entityId;
			}
		}

		return baseComponent; 
	}

	//-------------------------------------------------------------------------------------
	// Name: Deserialize 
	// Desc: Deserialize TransformComponent
	//-------------------------------------------------------------------------------------
	template<>
	TransformComponent* DeserializeAs<TransformComponent>(const SerialUtility::NamedValue& namedValue, ParseContext& parseContext)
	{
		TransformComponent* transformComponent = static_cast<TransformComponent*>(Component::DeserializeAs<BaseComponent>(namedValue, parseContext)); 

		if (transformComponent != nullptr) {
			SerialUtility::NamedValue positionValue("Position"), orientationValue("Orientation"), scaleValue("Scale");

			if (!namedValue.TryGetNamedVectorValue("Position", transformComponent->position)) {
				transformComponent->position = Vector2D();
			}

			if (!namedValue.TryGetNamedVectorValue("Orientation", transformComponent->orientation)) {
				transformComponent->orientation = Vector2D();
			}

			if (!namedValue.TryGetNamedVectorValue("Scale", transformComponent->scale)) {
				transformComponent->scale = Vector2D();
			}

			return transformComponent;
		}
		
		return nullptr;
	}

	//-------------------------------------------------------------------------------------
	// Name: Deserialize 
	// Desc: Deserialize GraphicsComponent
	//-------------------------------------------------------------------------------------
	template<>
	GraphicsComponent* DeserializeAs<GraphicsComponent>(const SerialUtility::NamedValue& namedValue, ParseContext& parseContext)
	{
		// TODO: implement
		return parseContext.NewComponent<GraphicsComponent>();
	}

	//-------------------------------------------------------------------------------------
	// Name: IsComponent 
	// Desc: returns true if there is a component with the corresponding name
	//-------------------------------------------------------------------------------------
	bool IsComponent(const std::string& name)
	{
		// TODO: implement
		return true;
	}
}

#endif // COMPONENT_H