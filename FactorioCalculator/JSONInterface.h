#ifndef JSONINTERFACE
#define JSONINTERFACE

#include "document.h"
#include "Calculator.h"

namespace json {
	
	static const char* kTypeNames[] =
	{ "Null", "False", "True", "Object", "Array", "String", "Number" };



	class JSONInterface
	{
		void importJSON(const char*);
		rapidjson::Document* doc;

		struct FactorioCalculations::Resource*	makeResource(rapidjson::Value&);
		struct FactorioCalculations::Miner*		makeMiner(rapidjson::Value&);
		struct FactorioCalculations::Item*		makeItem(rapidjson::Value&);
		struct FactorioCalculations::Furnace*	makeFurnace(rapidjson::Value&);
		struct FactorioCalculations::Assembler* makeAssemblingMachine(rapidjson::Value&);
		struct FactorioCalculations::Tool*		makeTool(rapidjson::Value&);
		struct FactorioCalculations::Fluid*		makeFluid(rapidjson::Value&);
		struct FactorioCalculations::Process*	makeProcess(rapidjson::Value&);
		struct FactorioCalculations::Pipe*		makePipe(rapidjson::Value&);

	public:
		JSONInterface();
		~JSONInterface();

		/*
		gets the value represented by the string passed
		@param char* the variable name
		*/
		const struct FactorioCalculations::Element* getValue(const char*);
		const struct FactorioCalculations::Element* getValueWithHint(const char* name , const char* prototype);
		const std::map<const char*, FactorioCalculations::Tabs>* getTabs();
		const std::vector<std::pair<const char*, FactorioCalculations::Prototypes>> getTab(FactorioCalculations::Tabs);

		void init(const char*);

		/*
		checks if a given value exists
		@param char* the variable name
		*/
		bool hasValue(const char*) const;


	};
}
#endif