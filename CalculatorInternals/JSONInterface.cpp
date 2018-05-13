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
		char a = jsonFile.get();
		
		if((int)a != -1)
			file += a;
	}

	jsonFile.close();

	rapidjson::Document* docu = new rapidjson::Document();

	docu->Parse(file.c_str());
	doc = docu;

	std::cout << "doc is null object? " << docu->IsNull() << std::endl;
	std::cout << "getting attribute of 'hello'..." << std::endl;
	rapidjson::Value& s = (*doc)["hello"];
	std::cout << s.GetString() << std::endl;
}

JSONInterface::JSONInterface(const char* fileName)
{
	importJSON(fileName);
}
JSONInterface::~JSONInterface() {}