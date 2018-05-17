#ifndef CALCULATOR
#define CALCULATOR

#include <map>
#include <iostream>

/*
	This namespace contains utility functions for Factorio calculations
*/
namespace FactorioCalculations {


	/////////////////////////////////////////////////////////
	////prototypes
	/////////////////////////////////////////////////////////
	const int ProtoTypeCount = 6;

	enum Prototypes {
		RESOURCE,
		FLUID,
		ASSEMBLINGMACHINE,
		ITEM,
		MINING_DRILL,
		PROCESS
	};

	static const char* Prototype_strings[] = {
		"RESOURCE",
		"FLUID",
		"ASSEMBLINGMACHINE",
		"ITEM",
		"MINING_DRILL",
		"PROCESS"
	};

	/////////////////////////////////////////////////////////
	////END prototypes
	/////////////////////////////////////////////////////////

	struct Element {

		const char* name;
		Prototypes prototype;
		std::map<const char*, const char*> extras;
	};


	struct Resource : Element {
		
		double miningHardness;
		double miningTime;
	};
	
	struct Fluid : Element {

	};
	struct Miner : Element {
		
		long energyConsumption;
		float craftTime;
		float miningPower;
		float miningSpeed;

	};


	/*
		returns the  rate (resources/sec) at which a resource is mined using a miner
	*/
	static double getMiningSpeed(Miner* m, Resource* r)
	{
		return (m->miningPower - r->miningHardness) * (m->miningPower / r->miningTime);
	}

	static double getBuildSpeed(double craftingTime, double craftingSpeed)
	{
		return craftingTime / craftingSpeed;
	}
}

#endif