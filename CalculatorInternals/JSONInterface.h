#pragma once
#include "C:\Users\McGiv\source\repos\FactorioCalculator\node_modules\rapidjson\include\rapidjson\document.h"

class JSONInterface
{

	void importJSON(const char*);

public:
	rapidjson::Document* doc;
	JSONInterface(const char* fileName);
	~JSONInterface();
};

