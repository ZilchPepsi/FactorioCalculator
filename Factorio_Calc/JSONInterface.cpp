#include "JSONInterface.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cctype>

using namespace json;

/*
	imports a json file and puts it into a rapidjson::Document
*/
void JSONInterface::importJSON(const char* fileName)
{
	std::ifstream jsonFile;
	jsonFile.open(fileName, std::ifstream::in);

	std::string file;

	char a;
	while ((a = jsonFile.get()) != -1)
	{
			file += a;
	}

	jsonFile.close();

	doc = new rapidjson::Document();

	doc->Parse(file.c_str());
}

JSONInterface::JSONInterface()
{
}

void JSONInterface::init(const char* fileName)
{
	importJSON(fileName);
}

JSONInterface::~JSONInterface()
{
	delete doc;
}

const std::map<const char*, const char*>* JSONInterface::getTabs()
{
	std::map<const char*, const char*>* map = new std::map<const char*, const char*>;

	using namespace rapidjson;

	const Value& root = (*doc)["prototypes"];

	for (auto& protos : root.GetArray())
	{
		for (auto& thing : protos["items"].GetArray())
		{
			map->insert(std::pair<const char*, const char*>(thing["name"].GetString(), protos["prototype"].GetString()));
		}
	}

	return map;
}


const struct FactorioCalculations::Element* JSONInterface::getValue(const char* s)
{
	using namespace rapidjson;

	const Value& root = (*doc)["prototypes"];

	//cycle protos
	for (auto& protos : root.GetArray())
	{
		//cycle objects in proto
		for (auto& thing : protos["items"].GetArray())
		{
			if (!strcmp(thing["name"].GetString(), s))
			{
				switch (FactorioCalculations::getPrototype(protos["prototype"].GetString()))
				{
					using namespace FactorioCalculations;
				case Prototypes::RESOURCE:			return makeResource((rapidjson::Value&)thing);
				case Prototypes::ITEM:				return makeItem((rapidjson::Value&)thing);
				case Prototypes::MINING_DRILL:		return makeMiner((rapidjson::Value&)thing);
				case Prototypes::FURNACE:			return makeFurnace((rapidjson::Value&)thing);
				case Prototypes::ASSEMBLINGMACHINE: return makeAssemblingMachine((rapidjson::Value&)thing);
				case Prototypes::TOOL:				return makeTool((rapidjson::Value&)thing);
				}
				//if you got here, then the prototype is not recognized or the switch doesn't have that prototype yet
				assert(false);
				return NULL;
			}
		}
	}
	//if you got here then the item doesn't exist
	assert(false);
	return NULL;
}

const struct FactorioCalculations::Element* JSONInterface::getValueWithHint(const char* s, const char* proto)
{
	using namespace rapidjson;

	const Value& root = (*doc)["prototypes"];
	
	for (auto& prototype : root.GetArray())
	{
		if (!strcmp(prototype["prototype"].GetString(), proto))
		{
			for (auto& thing : prototype["items"].GetArray())
			{
				if (!strcmp(thing["name"].GetString(), s))
				{

					switch (FactorioCalculations::getPrototype(proto))
					{
						using namespace FactorioCalculations;
					case Prototypes::RESOURCE:			return makeResource((rapidjson::Value&)thing);
					case Prototypes::ITEM:				return makeItem((rapidjson::Value&)thing);
					case Prototypes::MINING_DRILL:		return makeMiner((rapidjson::Value&)thing);
					case Prototypes::FURNACE:			return makeFurnace((rapidjson::Value&)thing);
					case Prototypes::ASSEMBLINGMACHINE: return makeAssemblingMachine((rapidjson::Value&)thing);
					case Prototypes::TOOL:				return makeTool((rapidjson::Value&)thing);
						//TODO fill out this as above
					}
					//if you got here, then the prototype is not recognized
					assert(false);
					return NULL;
				}
			}
		}
	}
	//if you got here then the item doesn't exist
	assert(false);
	return NULL;
}

struct FactorioCalculations::Resource* JSONInterface::makeResource(rapidjson::Value& val)
{
	FactorioCalculations::Resource* r = new FactorioCalculations::Resource;
	r->prototype = FactorioCalculations::Prototypes::RESOURCE;
	r->name = val["name"].GetString();
	r->miningHardness = val["miningHardness"].GetDouble();
	r->miningTime = val["miningTime"].GetDouble();

	return r;
}

struct FactorioCalculations::Miner* JSONInterface::makeMiner(rapidjson::Value& val)
{
	FactorioCalculations::Miner* m = new FactorioCalculations::Miner;

	m->prototype = FactorioCalculations::Prototypes::MINING_DRILL;
	m->name = val["name"].GetString();
	m->energyConsumption = val["energyConsumption"].GetInt64();
	m->craftTime = val["craftTime"].GetFloat();
	m->miningPower = val["miningPower"].GetFloat();
	m->miningSpeed = val["miningSpeed"].GetFloat();

	return m;
}

struct FactorioCalculations::Item* JSONInterface::makeItem(rapidjson::Value& val)
{
	FactorioCalculations::Item* i = new FactorioCalculations::Item;

	i->prototype = FactorioCalculations::Prototypes::ITEM;
	i->name = val["name"].GetString();
	
	for (rapidjson::Value& v : val["ingredients"].GetArray())
	{
		FactorioCalculations::Ingredient* e = new FactorioCalculations::Ingredient;
		e->name = v["name"].GetString();
		e->prototype = v["prototype"].GetString();
		e->count = v["count"].GetInt();
		i->ingredients.push_back(e);
	}
	i->craftTime = val["craftTime"].GetDouble();
	if (val.HasMember("craftMethod"))
		i->craftMethod = FactorioCalculations::getCraftMethod(val["craftMethod"].GetString());
	else
		i->craftMethod = FactorioCalculations::CraftMethods::cCRAFT;

	return i;
}

struct FactorioCalculations::Furnace* JSONInterface::makeFurnace(rapidjson::Value& val)
{
	FactorioCalculations::Furnace* f = new FactorioCalculations::Furnace;

	f->prototype = FactorioCalculations::Prototypes::FURNACE;
	f->name = val["name"].GetString();

	for (rapidjson::Value& v : val["ingredients"].GetArray())
	{
		FactorioCalculations::Ingredient* e = new FactorioCalculations::Ingredient;
		e->name = v["name"].GetString();
		e->prototype = v["prototype"].GetString();
		e->count = v["count"].GetInt();
		f->ingredients.push_back(e);
	}

	f->craftTime = val["craftTime"].GetDouble();
	f->craftSpeed = val["craftSpeed"].GetDouble();
	f->pollution = val["pollution"].GetDouble();
	f->moduleSlots = val["moduleSlots"].GetInt();
	if (val.HasMember("craftMethod"))
		f->craftMethod = FactorioCalculations::getCraftMethod(val["craftMethod"].GetString());
	else
		f->craftMethod = FactorioCalculations::CraftMethods::cCRAFT;

	return f;
}

struct FactorioCalculations::Tool* JSONInterface::makeTool(rapidjson::Value& val)
{
	FactorioCalculations::Tool* t = new FactorioCalculations::Tool;

	t->prototype = FactorioCalculations::Prototypes::TOOL;
	t->name = val["name"].GetString();
	t->craftTime = val["craftTime"].GetDouble();
	for (rapidjson::Value& v : val["ingredients"].GetArray())
	{
		FactorioCalculations::Ingredient* e = new FactorioCalculations::Ingredient;
		e->name = v["name"].GetString();
		e->prototype = v["prototype"].GetString();
		e->count = v["count"].GetInt();
		t->ingredients.push_back(e);
	}
	if (val.HasMember("craftMethod"))
		t->craftMethod = FactorioCalculations::getCraftMethod(val["craftMethod"].GetString());
	else
		t->craftMethod = FactorioCalculations::CraftMethods::cCRAFT;

	return t;
}

struct FactorioCalculations::Assembler* JSONInterface::makeAssemblingMachine(rapidjson::Value& val)
{
	FactorioCalculations::Assembler* a = new FactorioCalculations::Assembler;

	a->prototype = FactorioCalculations::Prototypes::ASSEMBLINGMACHINE;
	a->name = val["name"].GetString();

	for (rapidjson::Value& v : val["ingredients"].GetArray())
	{
		FactorioCalculations::Ingredient* e = new FactorioCalculations::Ingredient;
		e->name = v["name"].GetString();
		e->prototype = v["prototype"].GetString();
		e->count = v["count"].GetInt();
		a->ingredients.push_back(e);
	}

	a->craftTime = val["craftTime"].GetDouble();
	a->craftSpeed = val["craftSpeed"].GetDouble();
	a->pollution = val["pollution"].GetDouble();
	a->energyConsumption = val["energyConsumption"].GetInt64();
	a->energyDrain = val["energyDrain"].GetInt64();
	a->moduleSlots = val["moduleSlots"].GetInt();
	if (val.HasMember("craftMethod"))
		a->craftMethod = FactorioCalculations::getCraftMethod(val["craftMethod"].GetString());
	else
		a->craftMethod = FactorioCalculations::CraftMethods::cCRAFT;

	return a;
}


bool JSONInterface::hasValue(const char* s) const
{
	using namespace rapidjson;

	const Value& root = (*doc)["prototypes"];

	for (auto& protos : root.GetArray())
	{
		for (auto& thing : protos["items"].GetArray())
		{
			if (strcmp(thing["name"].GetString(), s))
				return true;
		}
	}
	return false;
	
}