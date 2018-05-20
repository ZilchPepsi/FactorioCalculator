#ifndef JSONINTERFACE
#define JSONINTERFACE

#include "C:\Users\McGiv\source\repos\FactorioCalculator\node_modules\rapidjson\include\rapidjson\document.h"
#include "Calculator.h"

namespace json {
	
	static const char* kTypeNames[] =
	{ "Null", "False", "True", "Object", "Array", "String", "Number" };



	class JSONInterface
	{
		void importJSON(const char*);
		rapidjson::Document* doc;

		struct FactorioCalculations::Resource* makeResource(rapidjson::Value&);
		struct FactorioCalculations::Miner* makeMiner(rapidjson::Value&);
		struct FactorioCalculations::Item* makeItem(rapidjson::Value&);
		struct FactorioCalculations::Furnace* makeFurnace(rapidjson::Value&);
		/*struct FactorioCalculations::Resource makeFluid(rapidjson::Value&);
		struct FactorioCalculations::Resource makeAssemblingMachine(rapidjson::Value&);
		struct FactorioCalculations::Resource makeProcess(rapidjson::Value&);*/

	public:
		JSONInterface(const char* fileName);
		~JSONInterface();

		/*
		gets the value represented by the string passed
		@param char* the variable name
		*/
		const struct FactorioCalculations::Element* getValue(const char*);

		const struct FactorioCalculations::Element* getValueWithHint(const char* name , const char* prototype);

		/*
		checks if a given value exists
		@param char* the variable name
		*/
		bool hasValue(const char*) const;


	};
}
#endif