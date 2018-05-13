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

	jsonFile.close();

	const char* f = "{\"hello\": \"world\",\"t\" : true,\"f\" : false,\"n\" : null,\"i\" : 123,\"pi\" : 3.1416,\"a\" : [1, 2, 3, 4]";

	rapidjson::Document* docu = new rapidjson::Document();
	rapidjson::Document* testDoc = new rapidjson::Document();

	//put the string 'file' into char sequence c
	char* c = new char[file.length()+1];
	for (int x = 0; x < file.length(); x++)
		c[x] = file[x];
	c[file.length()] = NULL;
	////////////////////////////////////////////


	std::cout << "printing file..." << std::endl;

	docu->Parse(c);
	doc = docu;

	std::cout << "doc is null object? " << docu->IsNull() << std::endl;
	std::cout << "getting attribute of 'hello'..." << std::endl;
	rapidjson::Value& s = (*doc)["hello"];
}

JSONInterface::JSONInterface(const char* fileName)
{
	importJSON(fileName);
}
JSONInterface::~JSONInterface() {}