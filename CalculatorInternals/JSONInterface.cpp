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

	while (!jsonFile.eof())
	{
		file += jsonFile.get();
	}

	rapidjson::Document* docu = new rapidjson::Document();
	docu->Parse(file.c_str());
	doc = docu;
	std::cout << "doc is object? " << doc->IsObject() << std::endl;
}

JSONInterface::JSONInterface(const char* fileName)
{
	std::cout << "doc is null pointer? " << (doc == nullptr) << std::endl;
	importJSON(fileName);
	std::cout << "doc is null pointer? " <<(doc == nullptr) << std::endl;
}
JSONInterface::~JSONInterface() {}