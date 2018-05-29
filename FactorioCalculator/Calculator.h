#ifndef CALCULATOR
#define CALCULATOR

#include <map>
#include <iostream>
#include <vector>

/*
	This namespace contains utility functions for Factorio calculations
*/
namespace FactorioCalculations {


	/////////////////////////////////////////////////////////
	////prototypes
	/////////////////////////////////////////////////////////
	const int PrototypeCount = 8;
	const int CraftMethodCount = 6;

	enum Prototypes {
		RESOURCE,
		FLUID,
		ASSEMBLINGMACHINE,
		ITEM,
		MINING_DRILL,
		FURNACE,
		PROCESS,
		TOOL,
		PIPE
	};

	static const char* Prototype_strings[] = {
		"RESOURCE",
		"FLUID",
		"ASSEMBLINGMACHINE",
		"ITEM",
		"MINING_DRILL",
		"FURNACE",
		"PROCESS",
		"TOOL",
		"PIPE"
	};

	enum CraftMethods {
		cCRAFT,
		cFURNACE,
		cPROCESS,
		cGROUND,
		cOFFSHOREPUMP,
		cBOILER
	};

	static const char* CraftMethods_strings[] = {
		"cCRAFT",
		"cFURNACE",
		"cPROCESS",
		"cGROUND",
		"cOFFSHOREPUMP",
		"cBOILER"
	};

	enum Tabs {
		LOGISTICS,
		PRODUCTION,
		INTERMEDIATEPRODUCTS,
		COMBAT
	};

	static const char* Tabs_strings[] = {
		"LOGISTICS",
		"PRODUCTION",
		"INTERMEDIATEPRODUCTS",
		"COMBAT"
	};

	static Tabs getTab(const char* s)
	{
		for (int x = 0; x < 4; x++)
		{
			if (!strcmp(s, Tabs_strings[x]))
				return (Tabs)x;
		}
		//if you reach this then the tab doesn't exist
		assert(false);
		return Tabs::LOGISTICS;
	}


	/*	
		returns the enum equivalent of a const string
		@param const char* the string to check
	*/
	static CraftMethods getCraftMethod(const char * s)
	{
		for (int x = 0; x< CraftMethodCount; x++)
		{
			if (!strcmp(s, CraftMethods_strings[x]))
			{
				return (CraftMethods)x;
			}
		}
		//if you reach this then the craftMethod doesn't exist
		assert(false);
		return CraftMethods::cCRAFT;
	}
	static Prototypes getPrototype(const char * p)
	{
		for (int x = 0; x < PrototypeCount; x++)
		{
			if (!strcmp(p, Prototype_strings[x]))
			{
				return (Prototypes)x;
			}
		}
		//if you reach this then the prototype doesn't exist
		assert(false);
		return Prototypes::ITEM;
	}

	/////////////////////////////////////////////////////////
	////END prototypes
	/////////////////////////////////////////////////////////

	struct Ingredient {
		const char* name;
		const char* prototype;
		int count;
	};


	struct Element {

		const char* name;
		Prototypes prototype;
		CraftMethods craftMethod;
		std::map<const char*, const char*> extras;
	};

	struct Pipe : Element {
		int storageSize;
	};

	struct Process : Element {
		std::vector<Ingredient*> inputs;
		std::vector<Ingredient*> outputs;
		double craftTime;
	};


	struct Resource : Element {
		
		double miningHardness;
		double miningTime;
	};
	struct Item : Element {
		double craftTime;
		std::vector<Ingredient*> ingredients;

		~Item()
		{
			for (Ingredient* i : ingredients)
			{
				delete i;
			}
		}
	};
	
	struct Fluid : Element {

	};
	struct Miner : Element {
		
		int64_t energyConsumption;
		float craftTime;
		float miningPower;
		float miningSpeed;

	};
	struct Furnace : Item {

		int moduleSlots;
		double craftSpeed;
		double pollution;
	};
	struct Assembler : Item {

		int moduleSlots;
		double craftSpeed;
		double pollution;
		int64_t energyConsumption;
		int64_t energyDrain;
	};

	struct Tool : Item {

	};

	/*
		returns the  rate (resources/sec) at which a resource is mined using a miner
	*/
	static inline double getMiningSpeed(Miner* m, Resource* r)
	{
		return (m->miningPower - r->miningHardness) * (m->miningSpeed / r->miningTime);
	}


	/*
	returns the rate (res / sec) at which a resource is manufactured using an assembly machine or furnace
	*/
	static inline double getBuildSpeed(double craftingTime, double craftingSpeed)
	{
		return 1/(craftingTime / craftingSpeed);
	}
	static inline double getBuildSpeed(const Furnace* f, const Item* i)
	{
		return 1/(i->craftTime / f->craftSpeed);
	}
	static inline double getBuildSpeed(const Assembler* a, const Item* i)
	{
		return 1/(i->craftTime / a->craftSpeed);
	}
}


#endif