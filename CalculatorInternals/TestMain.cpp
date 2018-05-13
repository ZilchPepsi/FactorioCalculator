#include "JSONInterface.h"
#include <iostream>

int main()
{
	JSONInterface items("items.json");
	
	const rapidjson::Value& a = (*items.doc)["prototypes"];

	std::cout << a.IsNull() << std::endl;
	std::cout << a.IsArray() << std::endl;
	std::cout << a.Capacity() << std::endl;

	for (rapidjson::SizeType i = 0; i < a.Size(); i++)
		std::cout << a[i]["prototype"].GetString() << std::endl;
	
	return 0;
}