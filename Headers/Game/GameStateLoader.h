// GameStateLoader.h

#ifndef GAME_STATE_LOADER_H
#define GAME_STATE_LOADER_H

#include "Utility/FileUtility.h"
#include "Components/Repository/ComponentContainerFactory.h"
#include "Components/Repository/ComponentRepository.h"
#include "Graphics/Graphics.h"
#include "Components/Component.h"
#include "Game/ParseContext.h"

#include <list>
#include <string>
#include <exception>
#include <memory>

//-------------------------------------------------------------------------------
// Name: GameStateLoader
// Desc:
//-------------------------------------------------------------------------------
class GameStateLoader
{
	ParseContext parseContext; 

public:

	//----------------------------------------------------------------------------------------
	// Name: GameStateLoader
	// Desc:
	//----------------------------------------------------------------------------------------
	GameStateLoader(const string& directory, shared_ptr<ComponentRepository> componentRepository, shared_ptr<Graphics> graphics)
	: parseContext(ParseContext(componentRepository, graphics))
	{
		ComponentContainerFactory componentContainerFactory;

		if (componentRepository == nullptr) {
			return;
		}

		auto files = FileUtility::DirectoryContents(directory);
		auto currentEntityId = 0; 

		for (auto file : files) {

			if (IsXml(file)) {
				
				XmlDocument xmlDocument(file); 
				auto namedValues = SerialUtility::XmlDocumentToNamedValues(xmlDocument); 

				for (auto namedValue : namedValues) {

				}
			}
		}
	}

	//-----------------------------------------------------------------------------------------
	// Name: IsEntity
	// Desc:
	//-----------------------------------------------------------------------------------------
	static bool IsEntity(const SerialUtility::NamedValue& namedValue)
	{
		return (namedValue.Named() == "Entity");
	} 

	//-----------------------------------------------------------------------------------------
	// Name: IsComponent
	// Desc:
	//-----------------------------------------------------------------------------------------
	static bool IsComponent(const SerialUtility::NamedValue& namedValue)
	{
		ComponentContainerFactory componentContainerFactory; 

		auto names = componentContainerFactory.ComponentNames(); 
		auto result = find(names.begin(), names.end(), namedValue.Named());

		return (result != names.end());
	}

	//----------------------------------------------------------------------------------------
	// Name: NamedValueToComponent
	// Desc:
	//----------------------------------------------------------------------------------------
	void ParseNamedValues(const SerialUtility::NamedValue& topNamedValue, ParseContext parseContext) 
	{
		for (auto namedValuePair : topNamedValue.values) {
			// auto name = namedValue.Name();

			// if (IsComponent(namedValue)) {

			// 	// Create a component
			// 	auto component = componentRepository->NewComponent(name); 
			// 	component->entityId = parseContext.ParentEntityId(); 

			// 	if (NamedValueToComponent(component, namedValue)) {


			// 	} else {

			// 		componentRepository.Remove(component->entityId); 
			// 	}

			// } else if (IsEntity(namedValue)) {

			// } else {

			// }
		}
	}

	//----------------------------------------------------------------------------------------
	// Name: NamedValueToComponent
	// Desc:
	//----------------------------------------------------------------------------------------
	static bool NamedValueToComponent(BaseComponent* component, const SerialUtility::NamedValue& namedValue, const ParseContext& parseContext)
	{	
		if (component == nullptr) {
			return false; 
		}

		auto name = namedValue.Named(); 

		if (name == "BaseComponent") {
			return Component::Deserialize(component, namedValue);
		}

		if (name == "TransformComponent") {

			TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(component);
			return Component::Deserialize(transformComponent, namedValue); 
		}

		if (name == "GraphicsComponent") {

			GraphicsComponent* graphicsComponent = dynamic_cast<GraphicsComponent*>(component);
			return Component::Deserialize(graphicsComponent, namedValue, parseContext); 
		}
	}
};

#endif // GAME_STATE_LOADER_H