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

public:

	//----------------------------------------------------------------------------------------
	// Name: GameStateLoader
	// Desc:
	//----------------------------------------------------------------------------------------
	GameStateLoader(const string& directory, shared_ptr<ComponentRepository> componentRepository, shared_ptr<Graphics> graphics)
	{
		ComponentContainerFactory componentContainerFactory;

		if (componentRepository == nullptr) {
			return;
		}

		// find all the files with xml extension
		auto files = FileUtility::DirectoryContents(directory, "xml");
		auto currentEntityId = 0; 

		ParseContext parseContext(componentRepository, graphics); 

		for (auto file : files) {
			XmlDocument xmlDocument(file); 
			auto namedValues = SerialUtility::XmlDocumentToNamedValues(xmlDocument); 

			for (auto namedValue : namedValues) {
				this->ParseNamedValues(namedValue, parseContext);	
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
		auto componentRepository = parseContext.ComponentRepository(); 

		for (auto namedValuePair : topNamedValue.values) {
			auto namedValue = namedValuePair.second; 
			auto name = namedValue.Named();

			if (IsComponent(namedValue)) {

				// Create a component
				auto component = componentRepository->NewComponent(name); 
				component->entityId = parseContext.ParentEntityId(); 

				if (NamedValueToComponent(component, namedValue, parseContext)) {
					
				}

			} else if (IsEntity(namedValue)) {

			} else {

			}
		}
	}

	//----------------------------------------------------------------------------------------
	// Name: NamedValueToComponent
	// Desc:
	//----------------------------------------------------------------------------------------
	static bool NamedValueToComponent(BaseComponent* component, const SerialUtility::NamedValue& namedValue, ParseContext& parseContext)
	{	
		if (component == nullptr) {
			return false; 
		}

		auto name = namedValue.Named(); 

		if (name == "BaseComponent") {
			return Component::Deserialize(component, namedValue);
		}

		if (name == "TransformComponent") {

			TransformComponent* transformComponent = static_cast<TransformComponent*>(component);
			return Component::Deserialize(transformComponent, namedValue); 
		}

		if (name == "GraphicsComponent") {

			GraphicsComponent* graphicsComponent = static_cast<GraphicsComponent*>(component);
			return Component::Deserialize(graphicsComponent, namedValue, parseContext); 
		}
	}
};

#endif // GAME_STATE_LOADER_H