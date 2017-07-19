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

#define STRING(s) #s

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

		// TODO: we should go through and find all the components/entities/resources first

		for (auto file : files) {
			XmlDocument xmlDocument(file); 
			
			for (auto& tag : xmlDocument.Tags()) {
				SerialUtility::NamedValue namedValue(tag); 
				
				this->ParseNamedValue(namedValue, parseContext);
			}
		}
	}
	//-----------------------------------------------------------------------------------------
	// Name: ParseNamedValue
	// Desc:
	//-----------------------------------------------------------------------------------------
	void ParseNamedValue(const SerialUtility::NamedValue& namedValue, ParseContext& parseContext)
	{
		if (IsComponent(namedValue)) {

		}
	}

	//-----------------------------------------------------------------------------------------
	// Name: IsEntity
	// Desc:
	//-----------------------------------------------------------------------------------------
	static bool IsEntity(const SerialUtility::NamedValue& namedValue)
	{
		return (namedValue.Name() == "Entity");
	} 

	//-----------------------------------------------------------------------------------------
	// Name: IsComponent
	// Desc:
	//-----------------------------------------------------------------------------------------
	static bool IsComponent(const SerialUtility::NamedValue& namedValue)
	{
		ComponentContainerFactory componentContainerFactory; 

		auto names = componentContainerFactory.ComponentNames(); 
		auto result = find(names.begin(), names.end(), namedValue.Name());

		return (result != names.end());
	}

	//----------------------------------------------------------------------------------------
	// Name: NamedValueToComponent
	// Desc:
	//----------------------------------------------------------------------------------------
	void ParseTag(const XmlTag& tag, ParseContext& parseContext)
	{
		//tag.
	}
	//----------------------------------------------------------------------------------------
	// Name: NamedValueToComponent
	// Desc:
	//----------------------------------------------------------------------------------------
	static bool NamedValueToComponent(const SerialUtility::NamedValue& namedValue, ParseContext& parseContext)
	{	

	}
};

#endif // GAME_STATE_LOADER_H