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
            namedValue.AddNamedValue("position", transformComponent.position);
            namedValue.AddNamedValue("orientation", transformComponent.orientation);
            namedValue.AddNamedValue("scale", transformComponent.scale);

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
	BaseComponent* Deserialize(const struct SerialUtility::NamedValue& namedValue, ParseContext& parseContext)
	{
		// check if namedValue.name is a component
		if (IsComponent(namedValue.Name()) {

			auto name = namedValue.Name();

			if (name == STRING(BaseComponent)) {
				return Component::Deserialize<BaseComponent>(namedValue, parseContext);
			}

			if (name == STRING(TransformComponent)) {

				TransformComponent* transformComponent = static_cast<TransformComponent*>(component);
				return Component::Deserialize(namedValue, parseContext);
			}

			if (name == STRING(GraphicsComponent)) {

				GraphicsComponent* graphicsComponent = static_cast<GraphicsComponent*>(component);
				return Component::Deserialize(namedValue, parseContext);
			}

		} else {
			return nullptr;
		}
	}

	//-------------------------------------------------------------------------------------
	// Name: Deserialize 
	// Desc: Deserialize BaseComponent
	//-------------------------------------------------------------------------------------
	template<typename T, T = struct BaseComponent>
	BaseComponent* Deserialize(const struct SerialUtility::NamedValue& nameValue, ParseContext& parseContext)
	{
		BaseComponent* baseComponent = parseContext.NewComponent<BaseComponent>();

		// check if we're even trying to get an entityId
		std::string entityId;
		unsigned int id;

		if (nameValue.TryGetAttribute("entityId", entityId) && baseComponent != nullptr) {

			// check if the entityId is specified
			if (parseContext.ParentEntityId() == 0) {

				if (nameValue.TryGetAttribute("entityId", id)) {
					baseComponent->entityId = id;

				} else {

					baseComponent->entityId = parseContext.ParentEntityId();
				}
			}
		}

		return baseComponent; 
	}

	//-------------------------------------------------------------------------------------
	// Name: Deserialize 
	// Desc: Deserialize TransformComponent
	//-------------------------------------------------------------------------------------
	template<typename T, T = TransformComponent>
	BaseComponent* Deserialize(const SerialUtility::NamedValue& namedValue, ParseContext& parseContext)
	{
		TransformComponent* transformComponent = static_cast<TransformComponent*>(Deserialize<BaseComponent>(namedValue, parseContext)); 

		if (transformComponent != nullptr) {
			SerialUtility::NamedValue positionValue, orientationValue, scaleValue;

			if (!namedValue.TryGetNamedVectorValue("position", transformComponent->position)) {
				transformComponent->position = Vector2D();
			}

			if (!namedValue.TryGetNamedVectorValue("orientation", transformComponent->orientation)) {
				transformComponent->orientation = Vector2D();
			}

			if (!namedValue.TryGetNamedVectorValue("scale", transformComponent->scale)) {
				transformComponent->scale = Vector2D();
			}

			return true;
		}
		

		return false;
	}

	//-------------------------------------------------------------------------------------
	// Name: Deserialize 
	// Desc: Deserialize BaseComponent
	//-------------------------------------------------------------------------------------
	//bool Deserialize(struct BaseComponent* component, const struct SerialUtility::NamedValue& nameValuePairs, ParseContext& parseContext)
	//{
	//	if (component != nullptr) {

	//		// check if we're even trying to get an entityId
	//		std::string entityId;
	//		if (nameValuePairs.TryGetAttribute("entityId", entityId)) {

	//			// check if the entityId is specified
	//			if (parseContext.ParentEntityId() == 0) {
	//				int id;

	//				if (nameValuePairs.TryGetAttribute("entityId", id)) {
	//					component->entityId = id;
	//				}

	//			}
	//			else {

	//				component->entityId = parseContext.ParentEntityId();
	//			}
	//		}

	//		return true;
	//	}

	//	return false;
	//}



    //-------------------------------------------------------------------------------------
    // Name: Deserialize 
    // Desc: Deserialize GraphicsComponent
    //-------------------------------------------------------------------------------------
    bool Deserialize(struct GraphicsComponent* graphicsComponent, const SerialUtility::NamedValue& namedValue, ParseContext& parseContext)
    {
        if (graphicsComponent != nullptr) {

            if (Deserialize((BaseComponent*) graphicsComponent, namedValue, parseContext)) {
                
				std::string transformComponentName; 
				if (!namedValue.TryGetAttribute("name", transformComponentName)) {
					return false;
				}

                auto transformComponentId = parseContext.NamedId(transformComponentName); 
                graphicsComponent->transformComponentId = transformComponentId; 

				
				// we're looking for named value called resource
				SerialUtility::NamedValue resource; 
				if (namedValue.TryGetNamedValue("resource", resource)) {

					string path;
					string name;

					if (resource.TryGetAttribute("path", path)) {
						graphicsComponent->resourceId = parseContext.ResourceIdFromPath(path);
					
					} else if (resource.TryGetAttribute("name", name)) {

						graphicsComponent->resourceId = parseContext.ResourceIdFromName(name, resource);
					}
				}
            }
        }

        return false; 
    }
}

#endif // COMPONENT_H