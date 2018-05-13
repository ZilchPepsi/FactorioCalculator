#include "JSONInterface.h"
#include <iostream>

int main()
{
	JSONInterface items("testFile.json");

	/*
	const rapidjson::value& a = (*items.doc)["prototypes"];

	for (rapidjson::sizetype i = 0; i < a.size(); i++)
		std::cout << a["prototype"].GetString() << std::endl;*/

	return 0;
}