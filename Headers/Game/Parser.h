
//-------------------------------------------------------------------------
// Name: Parser
// Desc: 
//-------------------------------------------------------------------------
class Parser
{
	unordered_map<string, Parser> parsers; 

protected:

	weak_ptr<ParseState> parseStateWk; 

public:

	Parser(shared_ptr<ParseState> parseState) 
	{
		this->parseStateWk = parseState; 
	}

	AddParser(const string& name, Parser parser) 
	{
		this->parsers[name] = parser; 
	}

	void Parse(const list<NamedValue>& namedValues, ComponentRepository* componentRepository) 
	{
		for (auto namedValue : namedValues) {
			
			if (this->parsers.find(namedValue.Name()) != this->parsers.end()) {
				auto parser = this->parsers[namedValues];
				parser.Parse(namedValue); 
			}
		}
	} 

	virtual NamedValue Parse(const NamedValue& namedValue, ComponentRepository* componentRepository) = 0;
};

class EntityParser : public Parser 
{	
public:

	EntityParser(const list<string>& componentNames) 
	{
		for (auto componentName : componentNames)
		{
			this->AddParser(componentName, ComponentParser(componentName)); 
		}
	}

	virtual NamedValue Parse(const NamedValue& namedValue, ComponentRepository* componentRepository) 
	{

	}
};

class ComponentParser : public Parser
{
public:

	ComponentParser(const string& name)
	{
	}

	virtual NamedValue Parse(const NamedValue& namedValue, ComponentRepository* componentRepository) 
	{

	}
}