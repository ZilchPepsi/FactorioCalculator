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

const struct FactorioCalculations::Element JSONInterface::getValue(const char* s)
{
	using namespace rapidjson;

	const Value& root = (*doc)["prototypes"];

	for (auto& protos : root.GetArray())
	{
		for (auto& thing : protos["items"].GetArray())
		{
			if (!strcmp(thing["name"].GetString(), s))
			{
				const char* proto = protos["prototype"].GetString();

				for (int x = 0; x < FactorioCalculations::ProtoTypeCount; x++)
				{
					
					if (!strcmp(proto, FactorioCalculations::ProtoType_strings[x]))
					{
						switch (x)
						{
						case 0: return makeResource((rapidjson::Value&)thing);
						}
					}
					assert(false);
					return FactorioCalculations::Element();
				}
			}
		}
	}
	assert(false);
	return FactorioCalculations::Element();
}

struct FactorioCalculations::Resource JSONInterface::makeResource(rapidjson::Value& val)
{
	FactorioCalculations::Resource r;
	r.prototype = FactorioCalculations::Prototypes::RESOURCE;
	r.name = val["name"].GetString();
	r.miningHardness = val["miningHardness"].GetDouble();
	r.miningTime = val["miningTime"].GetDouble();
	
	return r;
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