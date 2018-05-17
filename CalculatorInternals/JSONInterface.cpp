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

JSONInterface::JSONInterface(const char* fileName)
{
	importJSON(fileName);
}

JSONInterface::~JSONInterface()
{
	delete doc;
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
				const char* proto = protos["prototype"].GetString();

				for (int x = 0; x < FactorioCalculations::ProtoTypeCount; x++)
				{
					if (!strcmp(proto, FactorioCalculations::Prototype_strings[x]))
					{
						switch (x)
						{
						case 0: return makeResource((rapidjson::Value&)thing);
						case 4: return makeMiner((rapidjson::Value&)thing);
						}
					}
				}
				//if you got here, then the prototype is not recognized
				assert(false);
				return NULL;
			}
		}
	}
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
					for (int x = 0; x < FactorioCalculations::ProtoTypeCount; x++)
					{
						if (!strcmp(proto, FactorioCalculations::Prototype_strings[x]))
						{
							switch (x)
							{
							case 0: return makeResource((rapidjson::Value&)thing);
							case 4: return makeMiner((rapidjson::Value&)thing);
							//TODO fill out this switch like the function above
							}
						}
					}
					//if you got here, then the prototype is not recognized
					assert(false);
					return NULL;
				}
			}
		}
	}
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