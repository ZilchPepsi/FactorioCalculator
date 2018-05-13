#include "JSONInterface.h"
#include <fstream>
#include <string>
#include <iostream>


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